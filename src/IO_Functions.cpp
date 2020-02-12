// File:		IO_Functions.h
// Language:	C++17
// Purpose:		Formatted IO functions.
// License:		At bottom of document.

// Header
#include "IO_Functions.h"

// STL
#include <algorithm>


// Prints a symbol multiple times.
void print_symbol(size_t count, char c) {
	for (size_t i = 0; i < count; ++i) {
		std::cout << c;
	}
}


// Prints a line and marks a specific lexeme.
// This is a marked example:
//           ^^^^^^
void print_marked_lexeme(const std::string& s, Lexeme lex) {
	std::cout << s << "\n";
	print_symbol(lex.begin, ' ');
	print_symbol(lex.end - lex.begin, '^');
	std::cout << "\n";
}


/**************************************************************************
*
*	Ostreams
*
*************************************************************************/

// Enumerations
std::ostream& operator<<(std::ostream& os, Token_Type t) {
	switch (t) {
	case Token_Type::EOL: os << "EOL"; break;
	case Token_Type::KEYWORD: os << "KEYWORD   "; break;
	case Token_Type::NUMBER: os << "NUMBER    "; break;
	case Token_Type::OPERATOR: os << "OPERATOR  "; break;
	case Token_Type::STRING: os << "STRING    "; break;
	case Token_Type::WORD: os << "WORD      "; break;
	default: os << "UNKNOWN  "; break;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, Keyword_Type t) {
	switch (t) {
	case Keyword_Type::I8: os << "I8"; break;
	case Keyword_Type::I16: os << "I16"; break;
	case Keyword_Type::I32: os << "I32"; break;
	case Keyword_Type::I64: os << "I64"; break;
	case Keyword_Type::U8: os << "U8"; break;
	case Keyword_Type::U16: os << "U16"; break;
	case Keyword_Type::U32: os << "U32"; break;
	case Keyword_Type::U64: os << "U64"; break;
	case Keyword_Type::F16: os << "F16"; break;
	case Keyword_Type::F32: os << "F32"; break;
	case Keyword_Type::F64: os << "F64"; break;
	case Keyword_Type::CLASS: os << "CLASS"; break;
	case Keyword_Type::LET: os << "LET"; break;
	case Keyword_Type::SELF: os << "SELF"; break;
	case Keyword_Type::STRUCT: os << "STRUCT"; break;
	case Keyword_Type::VAR: os << "VAR"; break;
	case Keyword_Type::CREF: os << "CREF"; break;
	case Keyword_Type::FN: os << "FN"; break;
	case Keyword_Type::MOVE: os << "MOVE"; break;
	case Keyword_Type::REF: os << "REF"; break;
	case Keyword_Type::RETURN: os << "RETURN"; break;
	case Keyword_Type::NAMESPACE: os << "NAMESPACE"; break;
	default: os << "UNKNOWN"; break;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, Number_Type t) {
	switch (t) {
	case Number_Type::BINARY: os << "BINARY"; break;
	case Number_Type::DECIMAL: os << "DECIMAL"; break;
	case Number_Type::HEX: os << "HEX"; break;
	case Number_Type::INTEGER: os << "INTEGER"; break;
	default: os << "UNKNOWN"; break;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, String_Type t) {
	switch (t) {
	case String_Type::DOUBLE: os << "DOUBLE"; break;
	case String_Type::SINGLE: os << "SINGLE"; break;
	default: os << "UNKNOWN"; break;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, Operator_Type t) {
	switch (t) {
	case Operator_Type::ACCESSOR: os << "."; break;
	case Operator_Type::ARROW: os << "->"; break;
	case Operator_Type::ASTERISK: os << "*"; break;
	case Operator_Type::BACK_SLASH: os << "\\"; break;
	case Operator_Type::BITWISE_AND: os << "&"; break;
	case Operator_Type::BITWISE_AND_EQUAL: os << "&="; break;
	case Operator_Type::BITWISE_NOT: os << "~"; break;
	case Operator_Type::BITWISE_OR: os << "|"; break;
	case Operator_Type::BITWISE_OR_EQUAL: os << "|="; break;
	case Operator_Type::BITWISE_XOR: os << "^"; break;
	case Operator_Type::BITWISE_XOR_EQUAL: os << "^="; break;
	case Operator_Type::CLOSED_ATTRIBUTE: os << "]]"; break;
	case Operator_Type::CLOSED_CURLY: os << "}"; break;
	case Operator_Type::CLOSED_PAREN: os << ")"; break;
	case Operator_Type::CLOSED_SQUARE: os << "]"; break;
	case Operator_Type::COLON: os << ":"; break;
	case Operator_Type::COMMA: os << ","; break;
	case Operator_Type::DECREMENT: os << "--"; break;
	case Operator_Type::DIVIDE: os << "/"; break;
	case Operator_Type::DIVIDE_EQUALS: os << "/="; break;
	case Operator_Type::EQUALS: os << "="; break;
	case Operator_Type::EQUALS_TO: os << "=="; break;
	case Operator_Type::GREATER: os << ">"; break;
	case Operator_Type::GREATER_EQUAL: os << ">="; break;
	case Operator_Type::INCREMENT: os << "++"; break;
	case Operator_Type::LEFT_SHIFT: os << "<<"; break;
	case Operator_Type::LEFT_SHIFT_EQUAL: os << "<<="; break;
	case Operator_Type::LESS: os << "<"; break;
	case Operator_Type::LESS_EQUAL: os << "<="; break;
	case Operator_Type::LOGICAL_AND: os << "&&"; break;
	case Operator_Type::LOGICAL_NOT: os << "!"; break;
	case Operator_Type::LOGICAL_OR: os << "||"; break;
	case Operator_Type::LOGICAL_XOR: os << "^^"; break;
	case Operator_Type::MACRO: os << "#"; break;
	case Operator_Type::MATCH_CASE: os << "=>"; break;
	case Operator_Type::MINUS: os << "-"; break;
	case Operator_Type::MINUS_EQUAL: os << "-="; break;
	case Operator_Type::MODULO: os << "%"; break;
	case Operator_Type::MODULO_EQUAL: os << "%="; break;
	case Operator_Type::MULTIPLY_EQUAL: os << "*="; break;
	case Operator_Type::NOT_EQUAL: os << "!="; break;
	case Operator_Type::OPEN_ATTRIBUTE: os << "[["; break;
	case Operator_Type::OPEN_CURLY: os << "{"; break;
	case Operator_Type::OPEN_PAREN: os << "("; break;
	case Operator_Type::OPEN_SQUARE: os << "["; break;
	case Operator_Type::PLUS: os << "+"; break;
	case Operator_Type::PLUS_EQUAL: os << "+="; break;
	case Operator_Type::RIGHT_SHIFT: os << ">>"; break;
	case Operator_Type::RIGHT_SHIFT_EQUAL: os << ">>="; break;
	case Operator_Type::SCOPE: os << "::"; break;
	case Operator_Type::SEMICOLON: os << ";"; break;
	case Operator_Type::TERNARY: os << "?"; break;
	case Operator_Type::THREE_WAY_COMP: os << "<=>"; break;
	case Operator_Type::UNSUPPORTED_OPERATOR: os << "UNSUPPORTED_OPERATOR"; break;
	default: os << "UKNOWN_OPERATOR"; break;
	}
	return os;
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