#ifndef LISTCHILD_H
#define LISTCHILD_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "AST.h"

struct ListChild {
    struct AST *Node;
    struct ListChild *next;
};

struct ListChild *chinit();
struct ListChild *addChild(struct ListChild *List, struct AST *Node);

// void ListPrint(ListTokens *head);

#endif
