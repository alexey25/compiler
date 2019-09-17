#include "AST.h"

int countNode = 1;

struct AST* initASTNode(){
	struct AST* ast;
	ast = (struct AST*) calloc(1, sizeof(struct AST));
	ast->Token = NULL;
	ast->ListChildren = NULL;
	ast->idNode = countNode;
	countNode++;
	ast->type = 0;
	ast->table = NULL;

	return ast;
}

void add_child(struct AST* Node, struct AST* parent){
	struct ListChild* child;
	child = (struct ListChild*) calloc(1, sizeof(struct ListChild));
	child->next = NULL;
	child->Node = Node;
	struct ListChild* pnode = parent->ListChildren;  
	if (pnode == NULL) {
		parent->ListChildren = child;
	} else {
		while (pnode->next != NULL)
		{
			pnode = pnode->next;
		}
		pnode->next = child;
	}
}

void setStroka(struct AST *node, string str){
	node->Stroka = str;
}

void setToken(struct AST *node, linkToken *token){
	node->Token = token;
}

struct ListChild* searchLastChild(struct AST* node){
	struct ListChild* listChild = node->ListChildren;
	while (listChild->next != NULL)
		listChild = listChild->next;
	return listChild;
}

struct AST* getLastChilde(struct AST* node){
	return searchLastChild(node)->Node;
}

void deleteLastChild(struct AST *node){
	struct ListChild* listChild = searchLastChild(node);
	listChild->Node = NULL;
}

void addNewChild(struct AST *parent, struct AST *newChild){
	struct ListChild *listChild = searchLastChild(parent);
	listChild->Node = newChild;
}

void swapChild(struct AST *parent, struct AST *newChild){
	struct AST *oldChild = getLastChilde(parent);
	deleteLastChild(parent);
	addNewChild(parent, newChild);
	add_child(oldChild, newChild);
}

void createTree(struct AST* Node) {
	FILE *graph;
	if ((graph = fopen("graph.gv", "w")) == NULL) {
		printf ("Cannot open file.\n");
		exit(1); 
	}
	fprintf(graph, "digraph {\n");
	createConnect(graph, Node);
	fprintf(graph, "}\n");
}

void createConnect(FILE *graph, struct AST* Node) {
	createBox(graph, Node);
	struct ListChild* child = Node->ListChildren;
	while (child != NULL) {
		fprintf(graph, "\t");
		toGvNode(graph, Node);
		fprintf(graph, " -> ");
		toGvNode(graph, child->Node);
		fprintf(graph, "\n");
		createConnect(graph, child->Node);
		child = child->next;
	}
}

void createBox(FILE *graph, struct AST* Node) {
	fprintf(graph,"\t\"node%d\"[label=%s]\n", Node->idNode, Node->Stroka.c_str());
}

void toGvNode(FILE *graph, struct AST* Node) {
	fprintf(graph, "\"node%d\"", Node->idNode);
}
