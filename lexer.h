#ifndef LEXER_H
#define LEXER_H 

#include "list.h"
#include "listToken.h"
#include <cstring>

using namespace std;

class lexer{
	private:
		listToken token;
		linkList code;
		int size;
	public:
		void scan(char **argv);
		void identification_token();
		void lex(char **argv);
};


#endif
