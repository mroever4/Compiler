// File:		Scanner.cpp
// Language:	C++17
// Purpose:		Scans input text. Produces lexemes and tokens.
// License:		At bottom of document.

// Header
#include "Scanner.h"

// Internal
#include "Scanner_Support.h"


// Scans input text to produce lexemes and tokens.
Scanner_Results scan(const std::vector<std::string>& code) {
	Scanner_Results results{};
	results.lines.resize(code.size());
	results.tokens.reserve(code.size());
	std::vector<Token> toks{};
	auto operators = build_operator_hierarchy();
	auto keywords = build_keywords();

	// Process each line
	for (size_t i = 0; i < code.size(); ++i) {
		results.lines[i].text = code[i];

		// Process each line of code
		uint32_t index = 0;
		uint32_t newIndex = 0;
		Token tok;
		while (index < code[i].length()) {
			// Check for whitespace
			newIndex = scan_whitespace(code[i], index);
			if (newIndex != index) {
				results.lines[i].lexemes.push_back({ index, newIndex });
				index = newIndex;
				continue;
			}

			// Check for numbers
			newIndex = scan_number(code[i], index, tok.subtype.num);
			if (newIndex != index) {
				tok.lexeme = (uint32_t)results.lines[i].lexemes.size();
				tok.lineNumber = (uint32_t)i;
				tok.type = Token_Type::NUMBER;
				toks.push_back(tok);
				results.lines[i].lexemes.push_back({ index, newIndex });
				index = newIndex;
				continue;
			}

			// Check for comments
			Comment_Case cc = Comment_Case::NONE;
			newIndex = scan_comment(code[i], index, cc);
			if (newIndex != index) {
				// Comment was contained to the line
				if (cc == Comment_Case::NONE) {
					results.lines[i].lexemes.push_back({ index, newIndex });
					index = newIndex;
					continue;
				}
				// Division operator found
				else if (cc == Comment_Case::DIVISION) {
					tok.lexeme = (uint32_t)results.lines[i].lexemes.size();
					tok.lineNumber = (uint32_t)i;
					tok.type = Token_Type::OPERATOR;
					tok.subtype.op = Operator_Type::DIVIDE;
					toks.push_back(tok);
					results.lines[i].lexemes.push_back({ index, newIndex });
					index = newIndex;
					continue;
				}
				// Division equals operator found
				else if (cc == Comment_Case::DIVISION_EQUALS) {
					tok.lexeme = (uint32_t)results.lines[i].lexemes.size();
					tok.lineNumber = (uint32_t)i;
					tok.type = Token_Type::OPERATOR;
					tok.subtype.op = Operator_Type::DIVIDE_EQUALS;
					toks.push_back(tok);
					results.lines[i].lexemes.push_back({ index, newIndex });
					index = newIndex;
					continue;
				}
				// Multiline comment found
				else if (cc == Comment_Case::MULTILINE) {
					results.lines[i].lexemes.push_back({ index, newIndex });

					// Process each line until the end of the MLC is found
					i += 1;
					for (; i < code.size(); ++i) {
						if (code[i].length() == 0) continue;
						results.lines[i].text = code[i];
						size_t pos = code[i].find("*/");
						if (pos == std::string::npos) {
							results.lines[i].lexemes.push_back({ 0, (uint32_t)code[i].length() });
						}
						else {
							index = (uint32_t)pos + 2;
							results.lines[i].lexemes.push_back({ 0, index });
							break;
						}
					}
					continue;
				}
				// Single line comment with a line continuation found
				else {
					results.lines[i].lexemes.push_back({ index, newIndex });
					i += 1;
					for (; i < code.size(); ++i) {
						if (code[i].length() == 0) continue;
						results.lines[i].text = code[i];
						results.lines[i].lexemes.push_back({ 0, (uint32_t)code[i].length() });
						if (code[i].back() != '\\') break;
					}
					break;
				}
			}

			// Check for double quote string literal
			bool nextLine = false;
			newIndex = scan_string_double_quote(code[i], index, nextLine);
			if (newIndex != index) {
				tok.lexeme = (uint32_t)results.lines[i].lexemes.size();
				tok.lineNumber = (uint32_t)i;
				tok.type = Token_Type::STRING;
				tok.subtype.str = String_Type::DOUBLE;
				toks.push_back(tok);
				results.lines[i].lexemes.push_back({ index, newIndex });
				index = newIndex;

				// Check for line continuations
				if (nextLine) {
					i += 1;
					for (; i < code.size(); ++i) {
						if (code[i].length() == 0) {
							index = 0;
							break;
						}
						results.lines[i].text = code[i];
						index = scan_string_end_quote(code[i], '"', nextLine);
						tok.lexeme = 0;
						tok.lineNumber = (uint32_t)i;
						toks.push_back(tok);
						results.lines[i].lexemes.push_back({ 0, index });
						if (!nextLine) break;
					}
				}
				continue;
			}

			// Check for single quote string literal
			newIndex = scan_string_single_quote(code[i], index, nextLine);
			if (newIndex != index) {
				tok.lexeme = (uint32_t)results.lines[i].lexemes.size();
				tok.lineNumber = (uint32_t)i;
				tok.type = Token_Type::STRING;
				tok.subtype.str = String_Type::SINGLE;
				toks.push_back(tok);
				results.lines[i].lexemes.push_back({ index, newIndex });
				index = newIndex;

				// Check for line continuations
				if (nextLine) {
					i += 1;
					for (; i < code.size(); ++i) {
						if (code[i].length() == 0) {
							index = 0;
							break;
						}
						results.lines[i].text = code[i];
						index = scan_string_end_quote(code[i], '\'', nextLine);
						tok.lexeme = 0;
						tok.lineNumber = (uint32_t)i;
						toks.push_back(tok);
						results.lines[i].lexemes.push_back({ 0, index });
						if (!nextLine) break;
					}
				}
				continue;
			}

			// Check for operators
			newIndex = scan_operator(code[i], index, operators, tok.subtype.op);
			if (newIndex != index) {
				tok.lexeme = (uint32_t)results.lines[i].lexemes.size();
				tok.lineNumber = (uint32_t)i;
				tok.type = Token_Type::OPERATOR;
				toks.push_back(tok);
				results.lines[i].lexemes.push_back({ index, newIndex });
				index = newIndex;
				continue;
			}


			// Check for a word
			newIndex = scan_word(code[i], index);
			if (newIndex != index) {
				tok.lexeme = (uint32_t)results.lines[i].lexemes.size();
				tok.lineNumber = (uint32_t)i;
				Lexeme lex{ index,newIndex };
				tok.subtype.hash = hash_text(code[i], lex);
				auto key = keywords.find(tok.subtype.hash);
				if (key != keywords.end()) {
					if (match_text(code[i], lex, key->second.text)) {
						tok.type = Token_Type::KEYWORD;
						tok.subtype.key = key->second.type;
					}
					else {
						tok.type = Token_Type::WORD;
					}
				}
				else {
					tok.type = Token_Type::WORD;
				}
				toks.push_back(tok);
				results.lines[i].lexemes.push_back(lex);
				index = newIndex;
				continue;
			}

			// Should never be reached.
			throw std::runtime_error("Scanner failed.");
			system("pause");
		}

		// Mark end of line
		if (toks.size()) {
			auto& lastTok = toks.back();

			// If a backslash is the last token and last lexeme (line continuation
			// mark), remove the token and do not place a EOL token
			if (lastTok.type == Token_Type::OPERATOR &&
				lastTok.subtype.op == Operator_Type::BACK_SLASH &&
				(lastTok.lexeme + 1) == results.lines[i].lexemes.size()) {
				toks.pop_back();
			}
			// Mark the end of the line (equivalent to a ; in C++)
			else if (lastTok.type != Token_Type::EOL) {
				toks.push_back({ (uint32_t)i, 0, Token_Type::EOL, 0 });
				results.tokens.push_back(std::move(toks));
			}
		}
	}

	// Check for unpushed line
	if (toks.size() != 0) {
		toks.push_back({ (uint32_t)results.lines.size(), 0, Token_Type::EOL, 0 });
		results.tokens.push_back(std::move(toks));
	}
	return results;
}


/******************************************************************************

This software is provided under two licenses. Choose whichever you prefer.


============================= Apache License V2.0 =============================

Copyright 2020 Matthew Roever

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


================================= MIT License =================================

Copyright (c) 2020 Matthew Roever

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************/