// File:		Scanner.h
// Language:	C++17
// Purpose:		Scans input text. Produces lexemes and tokens.
// License:		At bottom of document.

#ifndef SCANNER_H
#define SCANNER_H

// STL
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>


// Position of a lexical element in the source code.
struct Lexeme {
	uint32_t begin = 0;
	uint32_t end = 0;
};


// Current recognized tokens; will increase with time.
enum class Token_Type : uint32_t {
	EOL,		// End of Line - no text
	KEYWORD,
	NUMBER,
	OPERATOR,
	STRING,
	WORD
};


// Keywords
enum class Keyword_Type : uint32_t {
	// Types
	I8,
	I16,
	I32,
	I64,
	U8,
	U16,
	U32,
	U64,
	F16,
	F32,
	F64,

	// Data
	CLASS,
	LET,
	SELF,
	STRUCT,
	VAR,

	// Functional
	CREF,
	FN,
	MOVE,
	REF,
	RETURN,

	// Other
	NAMESPACE
};


// Numeric constants
enum class Number_Type : uint32_t {
	BINARY,
	DECIMAL,
	HEX,
	INTEGER
};


// String literals
enum class String_Type : uint32_t {
	DOUBLE,						// "
	SINGLE						// '
};


// Operators
enum class Operator_Type : uint32_t {
	ACCESSOR,					// .
	ARROW,						// ->
	ASTERISK,					// *
	BACK_SLASH,					// \ 
	BITWISE_AND,				// &
	BITWISE_AND_EQUAL,			// &=
	BITWISE_NOT,				// ~
	BITWISE_OR,					// |
	BITWISE_OR_EQUAL,			// |=
	BITWISE_XOR,				// ^
	BITWISE_XOR_EQUAL,			// ^=
	CLOSED_ATTRIBUTE,			// ]]
	CLOSED_CURLY,				// }
	CLOSED_PAREN,				// )
	CLOSED_SQUARE,				// ]
	COLON,						// :
	COMMA,						// ,
	DECREMENT,					// --
	DIVIDE,						// /
	DIVIDE_EQUALS,				// /=
	EQUALS,						// =
	EQUALS_TO,					// ==
	GREATER,					// >
	GREATER_EQUAL,				// >=
	INCREMENT,					// ++
	LEFT_SHIFT,					// <<
	LEFT_SHIFT_EQUAL,			// <<=
	LESS,						// <
	LESS_EQUAL,					// <=
	LOGICAL_AND,				// &&
	LOGICAL_NOT,				// !
	LOGICAL_OR,					// ||
	LOGICAL_XOR,				// ^^
	MACRO,						// #
	MATCH_CASE,					// =>
	MINUS,						// -
	MINUS_EQUAL,				// -=
	MODULO,						// %
	MODULO_EQUAL,				// %=
	MULTIPLY_EQUAL,				// *=
	NOT_EQUAL,					// !=
	OPEN_ATTRIBUTE,				// [[
	OPEN_CURLY,					// {
	OPEN_PAREN,					// (
	OPEN_SQUARE,				// [
	PLUS,						// +
	PLUS_EQUAL,					// +=
	RIGHT_SHIFT,				// >>
	RIGHT_SHIFT_EQUAL,			// >>=
	SCOPE,						// ::
	SEMICOLON,					// ;
	TERNARY,					// ?
	THREE_WAY_COMP,				// <=>
	UNSUPPORTED_OPERATOR,		// Any operator that does not match a pattern
};


// Text with contextual meaning.
struct Token {
	uint32_t lineNumber = 0;
	uint32_t lexeme = 0;
	Token_Type type;
	union {
		uint32_t hash = 0;
		Keyword_Type key;
		Number_Type num;
		Operator_Type op;
		String_Type str;
	} subtype;
};


// Line of code from a file.
struct Line {
	std::string text{};
	std::vector<Lexeme> lexemes{};
};


// Output of the scanner.
struct Scanner_Results {
	std::vector<Line> lines{};
	std::vector<std::vector<Token>> tokens{};
};


// Scans input text to produce lexemes and tokens.
Scanner_Results scan(const std::vector<std::string>& code);

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