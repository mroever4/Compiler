// File:		Scanner_Support.h
// Language:	C++17
// Purpose:		Scanner sub-functions. Produces lexemes and tokens.
// License:		At bottom of document.

#ifndef SCANNER_SUPPORT_H
#define SCANNER_SUPPORT_H

// STL
#include <intrin.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Internal
#include "Scanner.h"


// Treat all low value ASCII characters as whitespace (space == 32).
inline bool is_whitespace(char c);


// Checks if the character is a hexadecimal number (0-9), (a-f), (A-F).
inline bool is_hex_number(char c);


// Checks if the character is a decimal number (0-9).
inline bool is_decimal_number(char c);


// Checks if the character is a binary number (0, 1).
inline bool is_binary_number(char c);


// Scans for whitespace. Returns the stopping index (if the result is the same
// as index then no whitespace was found).
uint32_t scan_whitespace(const std::string& s, uint32_t index);


// Scans for binary constants 0b(0,1)*.
uint32_t scan_binary(const std::string& s, uint32_t index);


// Scans for hex constants 0x(0-9, a-f, A-F)*.
uint32_t scan_hex(const std::string& s, uint32_t index);


// Scans for integer constants (0-9)*.
uint32_t scan_integer(const std::string& s, uint32_t index);


// Scans for decimal constants (0-9)*.(0-9)*(e, E)(+, -)(0-9)*.
uint32_t scan_decimal(const std::string& s, uint32_t index);


// Scans for numeric constants.
uint32_t scan_number(const std::string& s, uint32_t index, Number_Type& tok);


// Defines the multiline comment cases that may occur, or if division is found.
enum class Comment_Case {
	NONE,
	DIVISION,
	DIVISION_EQUALS,
	MULTILINE,
	SINGLE_LINE_CONTINUATION
};


// Scans for comments.
uint32_t scan_comment(const std::string& s, uint32_t index, Comment_Case& cc);


// Scans for double quote string literal, does not validate quote correctness.
uint32_t scan_string_double_quote(const std::string& s, uint32_t index, bool& nextLine);


// Scans for single quote string literal, does not validate quote correctness.
uint32_t scan_string_single_quote(const std::string& s, uint32_t index, bool& nextLine);


// Scans for the end of a quote when a line continuation mark was detected.
uint32_t scan_string_end_quote(const std::string& s, char q, bool& nextLine);


// Defines an operator and dependent operators.
//
// Fields:
//	+ type: The operator type if a dependent operator is not found.
//	+ symbol: The character to match on.
//	+ ops: Dependent operators that contain this operator. Ex. += containts +.
struct Operator {
	Operator_Type type;
	char symbol = '\0';
	std::vector<Operator> ops{};
};


// Creates the operator hierarchy for scanning. Later versions can be converted
// to a finite automata instead of using pointers. This version allows new
// operators to be added easily.
std::vector<Operator> build_operator_hierarchy();


// Scans for operators.
uint32_t scan_operator(const std::string& s, uint32_t index, const std::vector<Operator>& ops, Operator_Type& type);


// Scans for words, stops when an illegal word symbol is detected or no more characters.
uint32_t scan_word(const std::string& s, uint32_t index);


// Computes the hash of a lexeme. The lexeme must be from the input string.
uint32_t hash_text(const std::string& s, Lexeme l);


// Comptues the hash of an entire string.
uint32_t hash_text(const char* s);


// Matches a word to the text of a lexeme.
bool match_text(const std::string txt, Lexeme l, const std::string word);


// Defines a keyword for word comparison.
struct Keyword {
	std::string text{};
	Keyword_Type type;
};


// Creates the set of all supported keywords for scanning. Designed for easy
// addition of new keywords.
std::map<uint32_t, Keyword> build_keywords();

#endif


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