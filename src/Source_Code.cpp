// File:		Source_Code.cpp
// Language:	C++17
// Purpose:		Stores source code from a file and runs the compiler.
// License:		At bottom of document.


// Header
#include "Source_Code.h"

// Internal
#include "IO_Functions.h"
#include "Timer.h"


/**************************************************************************
*
*	Compiling functionality
*
*************************************************************************/

// Loads an ascii file for compiling.
Source_Code::Source_Code(const std::filesystem::path path) {
	load_code(path);
}


// Loads an ascii file for compiling.
void Source_Code::load_code(const std::filesystem::path path) {
	Timer t{};
	t.start();

	// Open file
	std::ifstream iFile{ path };
	if (!iFile.is_open()) {
		throw std::runtime_error("Could not open file: " + path.filename().generic_string());
	}

	// Load lines individually.
	std::string line{};
	while (!iFile.eof()) {
		std::getline(iFile, line);
		code.push_back(std::move(line));
	}

	t.stop();
	time_loadFile = static_cast<double>(t.duration()) / 1'000'000;
}


// Runs the scanner on the loaded code.
void Source_Code::run_scanner() {
	Timer t{};
	t.start();
	scannerOutput = scan(code);
	t.stop();
	time_scanFile = static_cast<double>(t.duration()) / 1'000'000;
}


/**************************************************************************
*
*	IO
*
*************************************************************************/

// Prints the code loaded from a file.
void Source_Code::print_file() const {
	std::cout << "==================== Source Code ====================\n";
	size_t numPad = std::to_string(code.size()).length();
	for (size_t i = 0; i < code.size(); ++i) {
		print_number_pad(i + 1, numPad);
		std::cout << ": " << code[i] << "\n";
	}
	std::cout << "\n";
}


// Prints the time it took for various compiler components to run.
void Source_Code::print_time() const {
	std::cout << "==================== Compiler Timing ====================\n";
	std::cout << "Load file (ms): " << time_loadFile << "\n";
	std::cout << "Scan file (ms): " << time_scanFile << "\n";
	std::cout << "\n";
}


// Prints statistics from the compiler.
void Source_Code::print_stats() const {
	std::cout << "==================== Compiler Stats ====================\n";
	std::cout << "Lines scanned: " << scannerOutput.lines.size() << "\n";
	size_t lexemes = 0;
	for (const auto& l : scannerOutput.lines) {
		lexemes += l.lexemes.size();
	}
	std::cout << "Lexmes: " << lexemes << "\n";
	size_t tokens = 0;
	for (const auto& t : scannerOutput.tokens) {
		tokens += t.size();
	}
	std::cout << "Tokens: " << tokens << "\n";
	std::cout << "\n";
}


// Prints the lexemes found by the scanner.
void Source_Code::print_lexemes() const {
	std::cout << "==================== Scanner Lexemes ====================\n";
	size_t numPad = std::to_string(code.size()).length();
	size_t linePad = 11 - numPad;
	for (size_t i = 0; i < scannerOutput.lines.size(); ++i) {
		print_number_pad(i + 1, numPad);
		std::cout << ":";
		print_symbol(linePad, '-');
		std::cout << " " << scannerOutput.lines[i].text << "\n";
		for (const auto& l : scannerOutput.lines[i].lexemes) {
			std::cout << " [ ";
			print_number_pad(l.begin, 3);
			std::cout << ", ";
			print_number_pad(l.end, 3);
			std::cout << ") " << scannerOutput.lines[i].text.substr(l.begin, l.end - l.begin) << "\n";
		}
	}
	std::cout << "\n";
}


// Prints the tokens produced by the scanner.
void Source_Code::print_tokens() const {
	std::cout << "==================== Scanner Tokens ====================\n";
	size_t count = 0;
	for (const auto& toks : scannerOutput.tokens) {
		count += toks.size();
	}
	size_t numPad = std::to_string(count).length();
	count = 0;
	for (const auto& toks : scannerOutput.tokens) {
		for (const auto& tok : toks) {
			print_number_pad(count++, numPad);
			std::cout << ": " << tok.type;

			// Subtype
			switch (tok.type) {
			case Token_Type::KEYWORD: std::cout << tok.subtype.key; break;
			case Token_Type::NUMBER: {
				std::cout << tok.subtype.num << " ";
				Lexeme lex = scannerOutput.lines[tok.lineNumber].lexemes.at(tok.lexeme);
				std::cout << scannerOutput.lines[tok.lineNumber].text.substr(lex.begin, lex.end - lex.begin);
			} break;
			case Token_Type::OPERATOR: std::cout << tok.subtype.op; break;
			case Token_Type::STRING: {
				std::cout << tok.subtype.str << " ";
				Lexeme lex = scannerOutput.lines[tok.lineNumber].lexemes.at(tok.lexeme);
				std::cout << scannerOutput.lines[tok.lineNumber].text.substr(lex.begin, lex.end - lex.begin);
			} break;
			case Token_Type::WORD: {
				Lexeme lex = scannerOutput.lines[tok.lineNumber].lexemes.at(tok.lexeme);
				std::cout << scannerOutput.lines[tok.lineNumber].text.substr(lex.begin, lex.end - lex.begin);
			} break;
			}
			std::cout << "\n";
		}
	}
	std::cout << "\n";
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