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
		struct AST *root;
	public:
		AST* pars(linkToken* Token);
		void start();
		void StList(AST* StartNode);
		void print1(AST *node);
		void print2(AST *node);
		void print3(AST *node);
		void print4(AST *node);
		void commaid(AST* node);
		void headcommaid(AST* node);
		void tailcommaid(AST* node);
		void input1(AST* node);
		void input2(AST* node);
		void input3(AST* node);
		void input4(AST* node);
		void id1(AST* node);
		void id2(AST* node);
		void id3(AST* node);
		void arithmetic(AST* node);
		void headarithmetic(AST* node);
		void tailarithmetic(AST* node);
		void if1(AST* node);
		void while1(AST* node);
		void execution(AST* node);
		void colon(AST* node);
		void tab(AST* node);
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
