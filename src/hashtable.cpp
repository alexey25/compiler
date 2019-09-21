#include "hashtable.h"

int hashtab_hash(string key) {
	string p = key;
    int h = p.length();
    return h % HASHTAB_SIZE;
}

void hashtab_init(listnode **hashtab) {
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++) {
        hashtab[i] = NULL;
    }
}

struct Id_Table *Id_Table_Init (int level)
{
    struct Id_Table *Table = (struct Id_Table*) calloc (1, sizeof (struct Id_Table));
    Table->level = level;
    Table->next = NULL;
    Table->sizeTable = 0;
    hashtab_init(Table->hashtab);
    return Table;
}

void Add_Size_Table(struct Id_Table *table)
{
    table->sizeTable +=8;
}

void hashtab_add(listnode **hashtab, string key, int value, int baseType, int type) {
    listnode *node = new listnode;

    int index = hashtab_hash(key);

    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->size = 8;
        node->offset = 0;
        node->base_type = baseType;
        node->type = type;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *Find_in_all_table(struct Id_Table *table, string key)
{
    listnode **currHashTab = table->hashtab;

    listnode *node = hashtab_lookup(currHashTab, key);

    if (node == NULL && table->next != NULL) {
        node = Find_in_all_table(table->next, key);
    }

    return node;
}

struct listnode *hashtab_lookup(listnode **hashtab, string key) {
    int index;
    listnode *node;

    index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (node->key == key){
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(listnode **hashtab, string key) {
    int index;
    listnode *p, *prev = NULL;

    index = hashtab_hash(key);
    for (p = hashtab[index]; p != NULL; p = p->next) {
        if (p->key == key){
            if (prev == NULL) {
                hashtab[index] = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            return;
        }
        prev = p;
    }
}

void hashtab_setOffset(listnode **hashtab, string key, int offset)
{
    listnode *node = hashtab_lookup(hashtab, key);
    node->offset = offset;    
}
