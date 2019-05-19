#include <iostream>
#include <fstream>
#include <cstring>
#include "lexer.h"

using namespace std;


int main(int argc, char **argv){
	lexer l;
	l.lex(argv);

	return 0;
}

