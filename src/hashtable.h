#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <cstring>

#define HASHTAB_SIZE 71
#define HASHTAB_MUL  31

using namespace std;

struct listnode
{
    string key;//наименование id 
    int value; //хэш-ключ
    //enum Base_Type base_type;
    int base_type;//1var 2arr 3func
    //enum Type type;
    int type;//1int 2char
    int offset; //смещение в стеке
    int size; 
    int count_el; //кол-во эл-в. для массива
    struct listnode *hashkoll; //для решения коллизий
    struct listnode *next;  //переход к след узлу
};

struct Id_Table
{
    struct listnode *hashtab[HASHTAB_SIZE];
    struct Id_Table *next;
    int level;
    int sizeTable;
};

int hashtab_hash(string key);

void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, string key, int value, int base_type, int type);
void hashtab_delete(struct listnode **hashtab, string key);
void hashtab_setOffset(struct listnode **hashtab, string key, int offset);
void addSizeTable(struct Id_Table *table, string key);

struct listnode *hashtab_lookup(struct listnode **hashtab, string ey);
struct Id_Table *Id_Table_Init (int level);
struct listnode *Find_in_all_table(struct Id_Table *Table, string key);

void Add_Size_Table(struct Id_Table *table);

#endif
