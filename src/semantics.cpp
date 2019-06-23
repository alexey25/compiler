#include "semantics.h"

void init_semantic(struct AST *root) {
	root->table = idTable_init(0);
	travel_tree(root->table, root);
}

void travel_tree(struct idTable *table, struct AST *node) {
	struct idTable* currTable = table;
	if (node->Stroka == "id"){
		struct ListChild* Children = node->ListChildren;
		while (Children != NULL) {
			string name = Children->Node->Token->type;

			struct listnode *foundNode = hashtab_lookup(table->hashtab, name);

			if (foundNode == NULL) {
				int value = hashtab_hash(name);
	
				int baseType;

				if(Children->Node->Stroka == "var"){
					baseType = 1;
				} else if (Children->Node->Stroka == "arr"){
					baseType = 2;
				} 

				int type;

				if (Children->Node->type == 1) {
					type = 1;
				} else if (Children->Node->type == 2) {
					type = 2;
				}

				hashtab_add(currTable->hashtab, name, value, baseType, type);
				addSizeTable(currTable);
				hashtab_setOffset(currTable->hashtab, name, table->sizeTable);
			} else {
				redeclMessage(Children->Node);
			}
			Children = Children->next;
		}
		return;
	} else if ((node->Stroka == "if") || (node->Stroka == "while")|| (node->Stroka == "def")){
		int lvl = currTable->level + 1;
		node->table = idTable_init(lvl);

		node->table->next = currTable;

		currTable = node->table;    
	/*}else if (node->Stroka == "def") {
		string name = node->Token->type;

		struct listnode *foundNode = hashtab_lookup(table->hashtab, name);

		if (foundNode == NULL) {
			int value = hashtab_hash(name);

			hashtab_add(currTable->hashtab, name, value, 3, 0);

			int lvl = currTable->level + 1;
			node->table = idTable_init(lvl);

			node->table->next = currTable;

			currTable = node->table;
		} else {
			redeclMessage(node);
		}*/
	} else if ((node->Stroka == "id")){
		string name = node->Token->type;
		struct listnode *foundNode = findInAllTable(currTable, name);

		if (foundNode == NULL) {
			notdeclMessage(node);
		}
	}

	struct ListChild* Children = node->ListChildren;
	while (Children != NULL) {
		travel_tree(currTable, Children->Node);
		Children = Children->next;
	}
}

void redeclMessage(struct AST *node)
{
	cout << node->Token->y << ":" <<  node->Token->x <<"error: redeclorte " << node->Token->type << endl;
}

void notdeclMessage(struct AST *node)
{
	cout << node->Token->y << ":" <<  node->Token->x <<"error: notdeclorate " << node->Token->type << endl;
}

void print_table(struct AST *node) {
	if (node->table != NULL) {
		printf("level = %d\n", node->table->level);
		for (int i=0; i < HASHTAB_SIZE; i++) {
			struct listnode *hashnode = node->table->hashtab[i];
			if (hashnode != NULL) {
				cout << "id= " <<  hashnode->key <<  "	" << "baseType= " << hashnode->baseType << "	" << "type= " << hashnode->type << "	" << "offset= " << 					hashnode->offset << endl;
			}
		}
	}
	struct ListChild* Children = node->ListChildren;
	while (Children != NULL) {
		print_table(Children->Node);
		Children = Children->next;
	}
}
