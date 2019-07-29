#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "listToken.h"
#include "lexer.h"
#include "AST.h"

using namespace std;

class parser{
	private:
		linkToken* Token;
		linkToken* lookahead;
		int count;
		int tab;
		struct AST *root;
	public:
		AST* pars(linkToken* Token);
		void start();
		void StList(AST* StartNode);
		void print(AST *node);
		void printarg(AST *node);
		void commaid(AST* node);
		void headcommaid(AST* node);
		void tailcommaid(AST* node);
		void input1(AST* node);
		void input2(AST* node);
		void input3(AST* node);
		void input4(AST* node);
		void id1(AST* node);
		void id2(AST* node);
		void idequally(AST* node);
		void idfunc(AST* node);
		void arg(AST* node);
		void comma_arg(AST* node);
		void headcomma_arg(AST* node);
		void tailcomma_arg(AST* node);
		//void idmas(AST* node);
		void arithmetic(AST* node);
		void headarithmetic(AST* node);
		void tailarithmetic(AST* node);
		void if1(AST* node);
		void block(AST* node);
		void indent();
		void dedent();
		void nl();
		void while1(AST* node);
		void execution(AST* node);
		void usl(AST* node);
		void logic(AST* node);
		void logic1(AST* node);
		void logic2(AST* node);
		void func(AST* node);

		linkToken* nextToken();
		linkToken* getLookahead();
		void consume();
		void printErrorMessage(int row, int column, string x);
		void match(string x);
};


#endif
