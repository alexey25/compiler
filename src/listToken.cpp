#include <iostream>
#include <fstream>
#include <cstring>
#include "listToken.h"

using namespace std;

listToken::listToken(){
	first = NULL;
}

void listToken::additem(string n, string t, int x, int y){
	linkToken *newlink = new linkToken;
	newlink->name = n;
	newlink->type = t;
	newlink->x = x;
	newlink->y = y;
	newlink->next = first;
	first = newlink;
}

void listToken::add(string n, string t, int x, int y){
	if(first != NULL){
		linkToken *current = first;
		while(current->next != NULL){
			current = current->next;
		}				
		linkToken *newlink = new linkToken;
		newlink->name = n;
		newlink->type = t;
		newlink->x = x;
		newlink->y = y;
		newlink->next = current->next;
		current->next = newlink;
	}
	if(first == NULL){
		additem(n, t, x, y);
	}
}

linkToken* listToken::token(){
	linkToken *current = first;			
	return current;
}
	
void listToken::display(char **argv){
	linkToken *current = first;
	while(current){
		cout << current->type << " '" << current->name << "' " << "Loc=<" << argv[1] << ":" << current->y << ":" << current->x << ">" << endl;
		current = current->next;
	}
}

listToken::~listToken(){
	linkToken *current = first;
	while(current){
		linkToken *tmp;
		tmp = current ;
		current = current->next;
		delete tmp;
	}
}
