#ifndef LIST_H
#define LIST_H

#include <cstring>

using namespace std;

struct link{
	string data;
	link *next;
};

class linkList{
	private:
		link *first;
	public:
		linkList();
		void additem(string d);
		void add(string d);
		void display();
		string get_item(int index);
		~linkList();
};



#endif
