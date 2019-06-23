#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <cstring>

#define HASHTAB_SIZE 71
#define HASHTAB_MUL 31

using namespace std;

struct listnode {
    string key;  //название идентиф
    int value;  //хэш-ключ
    int size;
    int offset;
    int baseType; //1 - переменная, 2 - массив, 3 - функция
    int type; //1 - инт, 2 - стринг
    int countElem;  //для массивов
    listnode *koll;  //для решения коллизий
    listnode *next;
};

struct idTable {
    listnode *hashtab[HASHTAB_SIZE];
    idTable *next;
    int level;
    int sizeTable;
};

int hashtab_hash(string key);
void hashtab_init(listnode **hashtab);
void hashtab_add(listnode **hashtab, string key, int value, int baseType, int type);
listnode *hashtab_lookup(listnode **hashtab, string key);
void hashtab_delete(listnode **hashtab, string key);
void hashtab_setOffset(listnode **hashtab, string key, int offset);

idTable *idTable_init(int level);
listnode *findInAllTable(idTable *table, string key);
void addSizeTable(idTable *table);

#endif
