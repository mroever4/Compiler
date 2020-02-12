// File:		IO_Functions.h
// Language:	C++17
// Purpose:		Formatted IO functions.
// License:		At bottom of document.

#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

// STL
#include <iostream>
#include <string>

// Internal
#include "Scanner.h"


// Prints numbers with a fixed width. Numbers shorter than the length are padded.
// Numbers that exceed the length will have no pad. The result is printed to cout.
// Examples for a padding of 4: "3   ",  "1234", "42  "
template<typename T>
void print_number_pad(T num, size_t pad) {
	auto s = std::to_string(num);
	std::cout << s;
	if (s.length() < pad) {
		size_t spaces = pad - s.length();
		for (size_t i = 0; i < spaces; ++i) {
			std::cout << ' ';
		}
	}
}


// Prints a symbol multiple times.
void print_symbol(size_t count, char c);


// Prints a line and marks a specific lexeme.
// This is a marked example:
//           ^^^^^^
void print_marked_lexeme(const std::string& s, Lexeme lex);


/**************************************************************************
*
*	Ostreams
*
*************************************************************************/

// Enumerations
std::ostream& operator<<(std::ostream& os, Token_Type t);
std::ostream& operator<<(std::ostream& os, Keyword_Type t);
std::ostream& operator<<(std::ostream& os, Number_Type t);
std::ostream& operator<<(std::ostream& os, String_Type t);
std::ostream& operator<<(std::ostream& os, Operator_Type t);

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