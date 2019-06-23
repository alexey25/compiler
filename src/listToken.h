#ifndef LISTTOKEN_H
#define LISTTOKEN_H

#include <cstring>

using namespace std;

struct linkToken{
	string name;
	string type;
	int x;
	int y;
	char FileName;
	linkToken *next;
};

class listToken{
	private:
		linkToken *first;
	public:
		listToken();
		void additem(string n, string t, int x, int y);
		void add(string n, string t, int x, int y);
		void display(char **argv);
		linkToken* token();		
		~listToken();
};



#endif
