# Compiler

Work in progress programming language and compiler. For more details see my [Medium series](https://medium.com/@mroever4) documenting how compilers work and code examples from this project.

# Command Line Interface

The compiler is operated entirely by the command line interface. The only required command is -path. Which specifies the file that the compiler should operate on. The compiler can only be run on a single file currently.

	-path <file_address>
		Specified the file path to the that will be compiled.

	-print_all
		Enables all print options.

	-print_timing
		Prints wall clock timing information for compiler steps (not a rigorous
		benchmark, but it will give rough times).

	-print_stats
		Prints compiler statistics.

	-print_file
		Print the imported file with line numbers.

	-print_lexemes
		Prints all lexemes identified by the compiler.

	-print_tokens
		Prints all tokens identified by the compiler.
    
# Next Components

1. Basic symbol table
2. Abstract syntax tree
3. Parser support for functions
4. Type inference
5. Static Single Assignment IR
