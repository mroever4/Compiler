// File:		Scanner_Support.cpp
// Language:	C++17
// Purpose:		Scanner sub-functions. Produces lexemes and tokens.
// License:		At bottom of document.

// Header
#include "Scanner_Support.h"


// Treat all low value ASCII characters as whitespace (space == 32).
bool is_whitespace(char c) {
	return c <= 32;
}


// Checks if the character is a binary number (0, 1).
bool is_binary_number(char c) {
	return c == '0' || c == '1';
}


// Checks if the character is a decimal number (0-9).
bool is_decimal_number(char c) {
	return c >= '0' && c <= '9';
}


// Checks if the character is a hexadecimal number (0-9), (a-f), (A-F).
bool is_hex_number(char c) {
	return is_decimal_number(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}


// Scans for whitespace. Returns the stopping index (if the result is the same
// as index then no whitespace was found).
uint32_t scan_whitespace(const std::string& s, uint32_t index) {
	for (uint32_t i = index; i < s.length(); ++i) {
		if (!is_whitespace(s[i])) {
			return i;
		}
	}
	return (uint32_t)s.length();
}


// Scans for binary constants 0b(0,1)*.
uint32_t scan_binary(const std::string& s, uint32_t index) {
	// Verify first value is a binary value.
	if (!is_binary_number(s[index])) {
		return index;
	}
	else index += 1;

	// Loop until end of the lexeme is found or no more characters present
	for (uint32_t i = index; i < s.length(); ++i) {
		// Binary number
		if (is_binary_number(s[i])) {
			continue;
		}

		// Seperator
		else if (s[i] == '_') {
			// Must be a 0 or 1 next
			if (++i < s.length()) {
				if (!is_binary_number(s[i])) {
					return i - 1;
				}
			}
		}
		// Non-binary character
		else {
			return i;
		}
	}
	return (uint32_t)s.length();
}


// Scans for hex constants 0x(0-9, a-f, A-F)*.
uint32_t scan_hex(const std::string& s, uint32_t index) {
	// Verify first value is a hex value.
	if (!is_hex_number(s[index])) {
		return index;
	}
	else index += 1;

	// Loop until end of the lexeme is found or no more characters present
	for (uint32_t i = index; i < s.length(); ++i) {
		// Hex number
		if (is_hex_number(s[i])) {
			continue;
		}

		// Seperator
		else if (s[i] == '_') {
			// Must be a hex next
			if (++i < s.length()) {
				if (!is_hex_number(s[i])) {
					return i - 1;
				}
			}
		}
		// Non-hex character
		else {
			return i;
		}
	}
	return (uint32_t)s.length();
}


// Scans for integer constants (0-9)*.
uint32_t scan_integer(const std::string& s, uint32_t index) {
	// Loop until end of the lexeme is found or no more characters present
	for (uint32_t i = index; i < s.length(); ++i) {
		// Decimal number
		if (is_decimal_number(s[i])) {
			continue;
		}

		// Seperator
		else if (s[i] == '_') {
			// Must be a decimal next
			if (++i < s.length()) {
				if (!is_decimal_number(s[i])) {
					return i - 1;
				}
			}
		}
		// Non-decimal character
		else {
			return i;
		}
	}
	return (uint32_t)s.length();
}


// Scans for decimal constants (0-9)*.(0-9)*(e, E)(+, -)(0-9)*.
uint32_t scan_decimal(const std::string& s, uint32_t index) {
	// Get numbers after a decimal place
	uint32_t newIndex = scan_integer(s, index);

	// Check for (e, E)
	if ((newIndex + 1) != s.length()) {
		if (s[newIndex] == 'e' || s[newIndex] == 'E') {
			if (s[newIndex + 1] == '+' || s[newIndex + 1] == '-') {
				uint32_t nextIndex = scan_integer(s, newIndex + 2);
				if (newIndex + 2 != nextIndex) {
					return nextIndex;
				}
				else {
					return newIndex;
				}
			}
			else {
				uint32_t nextIndex = scan_integer(s, newIndex + 1);
				if (newIndex + 1 != nextIndex) {
					return nextIndex;
				}
				else {
					return newIndex;
				}
			}
		}
	}

	// Fallback
	return newIndex;
}


// Scans for numeric constants.
uint32_t scan_number(const std::string& s, uint32_t index, Number_Type& type) {
	// Check for number
	if (!is_decimal_number(s[index])) {
		return index;
	}

	// Binary or hexadecimal numbers
	if (s[index] == '0') {
		if (index + 2 < s.length()) {
			// Binary constant
			if (s[index + 1] == 'b') {
				uint32_t newIndex = scan_binary(s, index + 2);
				if (newIndex != index + 2) {
					type = Number_Type::BINARY;
					return newIndex;
				}
			}
			// Hexadecimal constant
			else if (s[index + 1] == 'x') {
				uint32_t newIndex = scan_hex(s, index + 2);
				if (newIndex != index + 2) {
					type = Number_Type::HEX;
					return newIndex;
				}
			}
		}
	}

	// Decmial number
	uint32_t newIndex = scan_integer(s, index + 1);
	if (newIndex < s.length()) {
		if (s[newIndex] == '.') {
			type = Number_Type::DECIMAL;
			return scan_decimal(s, newIndex + 1);
		}
	}
	type = Number_Type::INTEGER;
	return newIndex;
}


// Scans for comments.
uint32_t scan_comment(const std::string& s, uint32_t index, Comment_Case& cc) {
	// Check for start of a comment
	if (s[index] != '/') {
		return index;
	}

	// Check for comment
	if ((index + 1) < s.length()) {
		// Single line comment
		if (s[index + 1] == '/') {
			// Check for line continuation
			if (s.back() == '\\') {
				cc = Comment_Case::SINGLE_LINE_CONTINUATION;
			}
			return (uint32_t)s.length();
		}
		// Multiline comment
		else if (s[index + 1] == '*') {
			size_t findPos = s.find("*/", index + 2);
			if (findPos == std::string::npos) {
				cc = Comment_Case::MULTILINE;
				return (uint32_t)s.length();
			}
			else {
				return (uint32_t)findPos + 2;
			}
		}
		// Divide equals
		else if (s[index + 1] == '=') {
			cc = Comment_Case::DIVISION_EQUALS;
			return index + 2;
		}
	}

	// Single slash found
	cc = Comment_Case::DIVISION;
	return index + 1;
}


// Scans for double quote string literal, does not validate quote correctness.
uint32_t scan_string_double_quote(const std::string& s, uint32_t index, bool& nextLine) {
	if (s[index] == '"') {
		for (uint32_t i = index + 1; i < s.length(); ++i) {
			if (s[i] == '"') {
				if (s[i - 1] != '\\') {
					return i + 1;
				}
			}
		}
		nextLine = s.back() == '\\';
		return (uint32_t)s.length();
	}
	return index;
}


// Scans for single quote string literal, does not validate quote correctness.
uint32_t scan_string_single_quote(const std::string& s, uint32_t index, bool& nextLine) {
	if (s[index] == '\'') {
		for (uint32_t i = index + 1; i < s.length(); ++i) {
			if (s[i] == '\'') {
				if (s[i - 1] != '\\') {
					return i + 1;
				}
			}
		}
		nextLine = s.back() == '\\';
		return (uint32_t)s.length();
	}
	return index;
}


// Scans for the end of a quote when a line continuation mark was detected.
uint32_t scan_string_end_quote(const std::string& s, char q, bool& nextLine) {
	for (uint32_t i = 0; i < s.length(); ++i) {
		if (s[i] == q) {
			if (i != 0) {
				if (s[i - 1] != '\\') {
					nextLine = false;
					return i;
				}
			}
		}
	}
	nextLine = s.back() == '\\';
	return (uint32_t)s.length();
}


// Creates the operator hierarchy for scanning. Later versions can be converted
// to a finite automata instead of using pointers. This version allows new
// operators to be added easily.
std::vector<Operator> build_operator_hierarchy() {
	return std::vector<Operator>{
		{ Operator_Type::ACCESSOR, '.', {} },
		{ Operator_Type::ASTERISK, '*', {
			{ Operator_Type::MULTIPLY_EQUAL, '=', {} },
		} },
		{ Operator_Type::BACK_SLASH, '\\', {} },
		{ Operator_Type::BITWISE_AND, '&', {
			{ Operator_Type::BITWISE_AND_EQUAL, '=', {} },
			{ Operator_Type::LOGICAL_AND, '&', {} }
		} },
		{ Operator_Type::BITWISE_NOT, '~', {} },
		{ Operator_Type::BITWISE_OR, '|', {
			{ Operator_Type::BITWISE_OR_EQUAL, '=', {} },
			{ Operator_Type::LOGICAL_OR, '|', {} }
		} },
		{ Operator_Type::BITWISE_XOR, '^', {
			{ Operator_Type::BITWISE_XOR_EQUAL, '=', {} },
			{ Operator_Type::LOGICAL_XOR, '^', {} }
		} },
		{ Operator_Type::CLOSED_CURLY, '}', {} },
		{ Operator_Type::CLOSED_PAREN, ')', {} },
		{ Operator_Type::CLOSED_SQUARE, ']', {
			{ Operator_Type::CLOSED_ATTRIBUTE, ']', {} }
		} },
		{ Operator_Type::COLON, ':', {
			{ Operator_Type::SCOPE, ':', {} }
		} },
		{ Operator_Type::COMMA, ',', {} },
		{ Operator_Type::EQUALS, '=', {
			{ Operator_Type::EQUALS_TO, '=', {} },
			{ Operator_Type::MATCH_CASE, '>', {} }
		} },
		{ Operator_Type::GREATER, '>', {
			{ Operator_Type::GREATER_EQUAL, '=', {} },
			{ Operator_Type::RIGHT_SHIFT, '>', {
				{ Operator_Type::RIGHT_SHIFT_EQUAL, '=', {} }
			} }
		} },
		{ Operator_Type::LESS, '<', {
			{ Operator_Type::LESS_EQUAL, '=', {
				{ Operator_Type::THREE_WAY_COMP, '>', {} }
			} },
			{ Operator_Type::LEFT_SHIFT, '<', {
					{ Operator_Type::LEFT_SHIFT_EQUAL, '=', {} }
			} }
		} },
		{ Operator_Type::LOGICAL_NOT, '!', {
			{ Operator_Type::NOT_EQUAL, '=', {} }
		} },
		{ Operator_Type::MACRO, '#', {} },
		{ Operator_Type::MINUS, '-', {
			{ Operator_Type::ARROW, '>', {} },
			{ Operator_Type::DECREMENT, '-', {} },
			{ Operator_Type::MINUS_EQUAL, '=', {} }
		} },
		{ Operator_Type::MODULO, '%', {
			{ Operator_Type::MODULO_EQUAL, '=', {} }
		} },
		{ Operator_Type::OPEN_CURLY, '{', {} },
		{ Operator_Type::OPEN_PAREN, '(', {} },
		{ Operator_Type::OPEN_SQUARE, '[', {
			{ Operator_Type::OPEN_ATTRIBUTE, '[', {} }
		} },
		{ Operator_Type::PLUS, '+', {
			{ Operator_Type::INCREMENT, '+', {} },
			{ Operator_Type::PLUS_EQUAL, '=', {} }
		} },
		{ Operator_Type::SEMICOLON, ';', {} },
		{ Operator_Type::TERNARY, '?', {} },

		// Operators that are not yet supported
		{ Operator_Type::UNSUPPORTED_OPERATOR, '`', {} },
		{ Operator_Type::UNSUPPORTED_OPERATOR, '@', {} }
	};
}


// Scans for operators.
uint32_t scan_operator(const std::string& s, uint32_t index, const std::vector<Operator>& ops, Operator_Type& type) {
	for (const auto& op : ops) {
		if (op.symbol == s[index]) {
			type = op.type;
			uint32_t newIndex = index + 1;
			if (op.ops.size() && newIndex < s.length()) {
				return scan_operator(s, newIndex, op.ops, type);
			}
			else {
				return newIndex;
			}
		}
	}
	return index;
}


// Scans for words, stops when an illegal word symbol is detected or no more characters.
uint32_t scan_word(const std::string& s, uint32_t index) {
	for (uint32_t i = index; i < s.length(); ++i) {
		if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 95)
			|| s[i] == 96 || (s[i] > 122 && s[i] < 127)) {
			return i;
		}
	}
	return (uint32_t)s.length();
}


// Computes the hash of a lexeme. The lexeme must be from the input string.
uint32_t hash_text(const std::string& s, Lexeme l) {
	uint32_t crc = 0;
	for (uint32_t i = l.begin; i < l.end; ++i) {
		crc = _mm_crc32_u8(crc, (uint8_t)s[i]);
	}
	return crc;
}


// Comptues the hash of an entire string.
uint32_t hash_text(const char* s) {
	uint32_t crc = 0;
	int64_t i = 0;
	while (s[i] != '\0') {
		crc = _mm_crc32_u8(crc, (uint8_t)s[i++]);
	}
	return crc;
}


// Matches a word to the text of a lexeme.
bool match_text(const std::string txt, Lexeme l, const std::string word) {
	// Must be the same length
	if ((l.end - l.begin) != word.length()) {
		return false;
	}
	// Match text
	else {
		return 0 == std::memcmp(txt.data() + l.begin, word.data(), word.length());
	}
}


// Creates the set of all supported keywords for scanning. Designed for easy
// addition of new keywords.
std::map<uint32_t, Keyword> build_keywords() {
	return std::map<uint32_t, Keyword>{
		// Types
		{ hash_text("i8"), { "i8", Keyword_Type::I8 } },
		{ hash_text("i16"), { "i16", Keyword_Type::I16 } },
		{ hash_text("i32"), { "i32", Keyword_Type::I32 } },
		{ hash_text("i64"), { "i64", Keyword_Type::I64 } },
		{ hash_text("u8"), { "u8", Keyword_Type::U8 } },
		{ hash_text("u16"), { "u16", Keyword_Type::U16 } },
		{ hash_text("u32"), { "u32", Keyword_Type::U32 } },
		{ hash_text("u64"), { "u64", Keyword_Type::U64 } },
		{ hash_text("f16"), { "f16", Keyword_Type::F16 } },
		{ hash_text("f32"), { "f32", Keyword_Type::F32 } },
		{ hash_text("f64"), { "f64", Keyword_Type::F64 } },

		// Data
		{ hash_text("class"), { "class", Keyword_Type::CLASS } },
		{ hash_text("let"), { "let", Keyword_Type::LET } },
		{ hash_text("self"), { "self", Keyword_Type::SELF } },
		{ hash_text("struct"), { "struct", Keyword_Type::STRUCT } },
		{ hash_text("var"), { "var", Keyword_Type::VAR } },

		// Functional
		{ hash_text("cref"), { "cref", Keyword_Type::CREF } },
		{ hash_text("fn"), { "fn", Keyword_Type::FN } },
		{ hash_text("move"), { "move", Keyword_Type::MOVE } },
		{ hash_text("ref"), { "ref", Keyword_Type::REF } },
		{ hash_text("return"), { "return", Keyword_Type::RETURN } },

		// Other
		{ hash_text("namespace"), { "namespace", Keyword_Type::NAMESPACE } }
	};
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