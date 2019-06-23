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

idTable *idTable_init(int level) {
    idTable *table = new idTable;
    table->level = level;
    table->next = NULL;
    table->sizeTable = 0;
    hashtab_init(table->hashtab);
    return table;
}

void addSizeTable(idTable *table)
{
    table->sizeTable += 8;
}

void hashtab_add(listnode **hashtab, string key, int value, int baseType, int type) {
    listnode *node = new listnode;

    int index = hashtab_hash(key);

    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->size = 8;
        node->offset = 0;
        node->baseType = baseType;
        node->type = type;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

listnode *findInAllTable(idTable *table, string key)
{
    listnode **currHashTab = table->hashtab;

    listnode *node = hashtab_lookup(currHashTab, key);

    if (node == NULL && table->next != NULL) {
        node = findInAllTable(table->next, key);
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
