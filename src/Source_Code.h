// File:		Source_Code.h
// Language:	C++17
// Purpose:		Stores source code from a file and runs the compiler.
// License:		At bottom of document.

#ifndef SOURCE_CODE_H
#define SOURCE_CODE_H

// STL
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Internal
#include "Scanner.h"


class Source_Code {
public:

	/**************************************************************************
	*
	*	Compiling functionality
	*
	*************************************************************************/

	// Loads an ascii file for compiling.
	Source_Code(const std::filesystem::path path);


	// Loads an ascii file for compiling.
	void load_code(const std::filesystem::path path);


	// Runs the scanner on the loaded code.
	void run_scanner();


	/**************************************************************************
	*
	*	IO
	*
	*************************************************************************/

	// Prints the code loaded from a file.
	void print_file() const;


	// Prints the time it took for various compiler components to run.
	void print_time() const;


	// Prints statistics from the compiler.
	void print_stats() const;


	// Prints the lexemes found by the scanner.
	void print_lexemes() const;


	// Prints the tokens produced by the scanner.
	void print_tokens() const;

private:
	std::vector<std::string> code{};
	Scanner_Results scannerOutput{};

	// Run time
	double time_loadFile = 0;
	double time_scanFile = 0;
};

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