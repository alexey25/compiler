#ifndef AST_H
#define AST_H

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "listToken.h"
#include "listChild.h"
#include "hashtable.h"

using namespace std;

struct AST {
    string Stroka;
    linkToken* Token;
    struct ListChild* ListChildren;
    int idNode;
    int type;
	idTable* table;
};

struct AST* initASTNode();

void add_child(struct AST* Node, struct AST* parent);

void setStroka(struct AST* node, string str);
void setToken(struct AST* node, linkToken *token);

struct ListChild* searchLastChild(struct AST* node);
struct AST* getLastChilde(struct AST* node);
void deleteLastChild(struct AST *node);
void addNewChild(struct AST *parent, struct AST *newChild);
void swapChild(struct AST *parent, struct AST *newChild);


#endif
