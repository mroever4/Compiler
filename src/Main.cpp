// File:		Main.cpp
// Language:	C++17
// Purpose:		Command Line Interface.
// License:		At bottom of document.

// STL
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Internal
#include "Source_Code.h"
#include "Timer.h"


/******************************************************************************
*
* === CLI Arguments ===
*
*	-path <file_address>
*		Specified the file path to the that will be compiled.
*	-print_all
*		Enables all print options.
*	-print_timing
*		Prints wall clock timing information for compiler steps (not a rigorous
*		benchmark, but it will give rough times).
*	-print_stats
*		Prints compiler statistics.
*	-print_file
*		Print the imported file with line numbers.
*	-print_lexemes
*		Prints all lexemes identified by the compiler.
*	-print_tokens
*		Prints all tokens identified by the compiler.
//
//	NOT YET SUPPORTED.
//
//*	-print_symbol_table
//*		Prints all information determined during parsing. This will print lots
//*		of information.
//*	-print_ast
//*		Prints the abstract syntax trees generated during parsing. This will
//*		print lots of information.
*
******************************************************************************/


// Supported CLI Arguments.
struct Arguments {
	std::filesystem::path filePath{};
	bool printTiming = false;
	bool printStats = false;
	bool printFile = false;
	bool printLexemes = false;
	bool printTokens = false;
	//bool printSymbolTable = false;
	//bool printAST = false;
};


// Process CLI
Arguments process_CLI(const std::vector<std::string>& cli) {
	Arguments args{};
	for (size_t i = 0; i < cli.size(); ++i) {
		// File path
		if (cli[i] == "-path") {
			i += 1;
			args.filePath = cli.at(i);
			if (!std::filesystem::exists(args.filePath)) {
				throw std::runtime_error(args.filePath.filename().generic_string() + " could not be found.");
			}
		}
		// Print all
		else if (cli[i] == "-print_all") {
			args.printTiming = true;
			args.printStats = true;
			args.printFile = true;
			args.printLexemes = true;
			args.printTokens = true;
			//args.printSymbolTable = true;
			//args.printAST = true;
		}
		// Print timing info
		else if (cli[i] == "-print_timing") {
			args.printTiming = true;
		}
		// Print timing info
		else if (cli[i] == "-print_stats") {
			args.printStats = true;
		}
		// Print file
		else if (cli[i] == "-print_file") {
			args.printFile = true;
		}
		// Print lexemes
		else if (cli[i] == "-print_lexemes") {
			args.printLexemes = true;
		}
		// Print tokens
		else if (cli[i] == "-print_tokens") {
			args.printTokens = true;
		}
		//// Print the symbol table
		//else if (cli[i] == "-print_symbol_table") {
		//	args.printSymbolTable = true;
		//}
		//// Print all ASTs
		//else if (cli[i] == "-print_ast") {
		//	args.printAST = true;
		//}
		// Error
		else {
			throw std::runtime_error("Invalid CLI argument: " + cli[i]);
		}
	}
	return args;
}


// Primary function.
int main(int argc, char** argv) {
	std::cout << "==================== Preliminary Compiler ====================\n";

	// Build command line arguments
	Arguments cmds{};
	try {
		std::vector<std::string> args{};
		args.reserve(argc);
		for (int i = 1; i < argc; ++i) {
			args.push_back(argv[i]);
		}
		cmds = process_CLI(args);
	}
	catch (const std::exception& err) {
		std::cout << "CLI Error: " << err.what() << "\n";
		std::cout << "Program will exit: ";
		system("pause");
		return EXIT_FAILURE;
	}

	// Run compiler
	try {
		Source_Code code{ cmds.filePath };
		code.run_scanner();

		// Output
		if (cmds.printTiming) {
			code.print_time();
		}
		if (cmds.printStats) {
			code.print_stats();
		}
		if (cmds.printFile) {
			code.print_file();
		}
		if (cmds.printLexemes) {
			code.print_lexemes();
		}
		if (cmds.printTokens) {
			code.print_tokens();
		}
		//if (cmds.printSymbolTable) {
		//
		//}
		//if (cmds.printAST) {
		//
		//}
	}
	catch (const std::exception& err) {
		std::cout << "Error: " << err.what() << "\n";
	}

	// Exit
	std::cout << "Exiting: ";
	system("pause");
	return EXIT_SUCCESS;
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