#include <iostream>
#include <fstream>
#include <cstring>
#include "list.h"

using namespace std;

linkList::linkList(){
	first = NULL;
}
void linkList::additem(string d){
	link *newlink = new link;
	newlink->data = d;
	newlink->next = first;
	first = newlink;
}
void linkList::add(string d){
	if(first != NULL){
		link *current = first;
		while(current->next != NULL){
			current = current->next;
		}				
		link *newlink = new link;
		newlink->data = d;
		newlink->next = current->next;
		current->next = newlink;
	}
	if(first == NULL){
		additem(d);
	}
}
void linkList::display(){
	link *current = first;
	while(current){
		cout << current->data << endl;
		current = current->next;
	}
}
string linkList::get_item(int index){
	link *current = first;
	for(int i=0; i<index; i++){
		current = current->next;
	}
	return current->data;
}
linkList::~linkList(){
	link *current = first;
	while(current){
		link *tmp;
		tmp = current ;
		current = current->next;
		delete tmp;
	}
}
