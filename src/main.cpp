#include <iostream>
#include <fstream>
#include <cstring>
#include "lexer.h"
#include "parser.h"
#include "semantics.h"

using namespace std;


int main(int argc, char **argv){	
	lexer l;
	linkToken* token = l.lex(argv);

	parser p;
    AST* root = p.pars(token);
	createTree(root);

	init_semantic(root);
	print_table(root);
	return 0;
}

