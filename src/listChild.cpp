#include "listChild.h"

struct ListChild *chinit(){
    struct ListChild *ListChildren;
    ListChildren = (struct ListChild*)malloc(sizeof(struct ListChild));
    ListChildren->next = NULL;
    ListChildren->Node = NULL;
    return ListChildren;
}

struct ListChild *addChild(struct ListChild *List, struct AST *Node){
    if (List->Node == NULL){
        List->Node = Node;
        return List;
    } else {
        struct ListChild *List2;
        List2 = (struct ListChild*)malloc(sizeof(struct ListChild));
        List->next = List2;
        List->Node = Node;
        List2->next = NULL;
        return List2;
    }
    return NULL;
}
