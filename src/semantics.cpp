#include "semantics.h"

void Init_semantic(struct AST *root){
	root->table = Id_Table_Init(0);
	Tree_traversal(root->table, root);
}
void Tree_traversal(struct Id_Table *table, struct AST *node)
{
	struct Id_Table* currTable = table;
	if(node->Stroka == "var" || node->Stroka =="Array")
	{
		struct listnode *Found_Node = hashtab_lookup(currTable->hashtab, node->Token->name);
		if(Found_Node == NULL)
		{
			if (node->type == 1 || node->type == 3)
			{
				string name = node->Token->name;
				int value = hashtab_hash(name);
				int base_type;
				if(node->Stroka == "var") 
				{
					base_type = 1;
				}else if(node->Stroka == "Array")
				{
					base_type = 2;
				}
				hashtab_add(currTable->hashtab, name, value, base_type, node->type);
				Add_Size_Table(currTable);
			    hashtab_setOffset(currTable->hashtab, name, currTable->sizeTable);
			}else{
				Not_Declar_Message(node);
				exit(1);
			}
		}
		return;
	}else if (node->Stroka == "if" ||
			node->Stroka == "def" ||
			node->Stroka == "while" )
	{
		int lvl = currTable->level + 1;
		node->table = Id_Table_Init(lvl);

		node->table->next = currTable;
		currTable = node->table;

	}else if(node->Stroka == "Function")
	{
		struct listnode *Found_Node = hashtab_lookup(currTable->hashtab, node->Token->name);

		if (Found_Node == NULL)
		{
			string name = node->Token->name;			
			int value = hashtab_hash(name);
			hashtab_add(currTable->hashtab, name, value, 3, 0); 

			
		}
	}
	struct ListChild* Children = node->ListChildren;
	while (Children != NULL)
	{
		Tree_traversal(currTable,Children->Node);
		Children = Children->next;
	}
}
void Redecl_Message(struct AST *node)
{
	cout  << node->Token->y<< " : " << node->Token->x << " error: redeclorte " << node->Token->name << endl;
}
void Not_Declar_Message(struct AST *node)
{
	cout  << node->Token->y << " : " <<  node->Token->x << " error: notdeclorate " << node->Token->type << endl;
}

void print_table(struct AST *node)
{
	if (node->table != NULL)
	{
		cout << "level =  " <<  node->table->level << endl;
		for (int i = 0; i < HASHTAB_SIZE; i++)
		{
			struct listnode *hash_node = node->table->hashtab[i] ;
			if (hash_node != NULL)
			{
				cout << "id= " << hash_node->key << "		" << "baseType= " << hash_node->base_type << "	" << "type= " << hash_node->type << "	"<< "offset= " << 						hash_node->offset << endl;
			}
		}
		printf("SIZE TABLE: %d\n", node->table->sizeTable);
		
	}
	struct ListChild* Children = node->ListChildren;
	while (Children != NULL)
	{
		print_table(Children->Node);
		Children = Children->next;
	}
	//printf("!!!!! \n");
}

