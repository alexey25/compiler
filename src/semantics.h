#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "AST.h"
#include "hashtable.h"

void init_semantic(struct AST *root);
void travel_tree(struct idTable *table, struct AST *node);
void print_table(struct AST *node);
void checkArgList();

void redeclMessage(struct AST *node);
void notdeclMessage(struct AST *node);
#endif
