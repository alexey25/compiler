#include <iostream>
#include <fstream>
#include <cstring>
#include "list.h"
#include "listToken.h"
#include "lexer.h"

using namespace std;

void lexer::scan(char **argv){
	size = 0;
	string str;
	ifstream f;
	f.open(argv[1], ios::in);
	while(!f.eof()){
		getline(f, str);
		if(str != ""){
			code.add(str);
			size += 1;
		}
	}
}
void lexer::identification_token(){	
	string str, type;
	string lexema = "";
	int x,y;
	for(int i = 0; i < size; i++){
		y = i + 1;
		x = 1;		
		str = code.get_item(i);
		int n = str.length();
		for(int j = 0; j < n; j++){	
			if(str[j] == 34){
				x = j + 1;
				for(int j2 = j; j2 < n; j2++){
					lexema = lexema + str[j2];
					if(str[j2+1] == 34){
						lexema = lexema + str[j2+1];
						type = "string_iteral";
						token.add(lexema, type, x, y);							
						j = j2+2;
						lexema = "";
						break;
					}
				}
			}
			if(str[j] == 32){
				continue;
			}
			if(str[j] == 61 && str[j+1] == 61){
				lexema = str[j];
				lexema = lexema + str[j+1];
				type = "compare";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				j = j + 1;
				continue;
			}	
			if(str[j] == 33 && str[j+1] == 61){
				lexema = str[j];
				lexema = lexema + str[j+1];
				type = "compare";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				j = j + 1;
				continue;
			}		
			if(str[j] == 60 && str[j+1] == 61){
				lexema = str[j];
				lexema = lexema + str[j+1];
				type = "less_or_equal";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				j = j + 1;
				continue;
			}
			if(str[j] == 61 && str[j+1] == 62){
				lexema = str[j];
				lexema = lexema + str[j+1];
				type = "more_or_equal";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				j = j + 1;
				continue;
			}
			if(str[j] == 40){
				lexema = str[j];
				type = "l_paren";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 41){
				lexema = str[j];
				type = "r_paren";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 42){
				lexema = str[j];
				type = "multiply";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 43){
				lexema = str[j];
				type = "plus";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 44){
				lexema = str[j];
				type = "comma";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 45){
				lexema = str[j];
				type = "minus";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 46){
				lexema = str[j];
				type = "point";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 47){
				lexema = str[j];
				type = "div";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 37){
				lexema = str[j];
				type = "mod";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 61){
				lexema = str[j];
				type = "equally";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 60){
				lexema = str[j];
				type = "less";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 62){
				lexema = str[j];
				type = "more";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 9){
				lexema = str[j];
				type = "tab";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 91){
				lexema = str[j];
				type = "l_braket";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			if(str[j] == 93){
				lexema = str[j];
				type = "p_braket";
				x = j + 1;
				token.add(lexema, type, x, y);
				lexema = "";
				continue;
			}
			
			lexema = lexema + str[j];
			if((str[j+1] > 31 && str[j+1] < 35) || (str[j+1] > 59 && str[j+1] < 63) || ( str[j+1] > 39 && str[j+1] < 48)|| str[j+1] == 37 || str[j+1] == 91 || str[j+1] 			== 93 || j == (n-1)){ 
				if(lexema == "print" || lexema == "while" || lexema == "if" || lexema == "else" || lexema == "input"){
					x = j - lexema.length() + 2;
					type = "identifier";
					token.add(lexema, type, x, y);
					lexema = "";
					continue;
				}
				if(lexema == "int"){
					x = j - lexema.length() + 2;
					type = "int";
					token.add(lexema, type, x, y);
					lexema = "";
					continue;
				}	
				if(lexema == "float"){
					x = j - lexema.length() + 2;
					type = "float";
					token.add(lexema, type, x, y);
					lexema = "";
					continue;
				}
				if(lexema == "char"){
					x = j - lexema.length() + 2;
					type = "char";
					token.add(lexema, type, x, y);
					lexema = "";
					continue;
				}
				int lex_size = lexema.length();
				bool tmp = false;
				for(int k = 0; k < lex_size; k++){
					if(((lexema[k] < 64 && lexema[k] > 91) || (lexema[k] < 97 && lexema[k] > 122) || (lexema[k] < 47 && lexema[k] > 58)  || lexema[k] != 95) 						&& (lexema[0] > 47 && lexema[0] < 58)){
						tmp = false;						
						break;	
					}
					tmp = true;
				}				
				if(tmp){
					x = j - lexema.length() + 2;
					type = "id";
					token.add(lexema, type, x, y);
					lexema = "";
					continue;
				}
				for(int k = 0; k < lex_size; k++){
					if(lexema[k] < 47 && lexema[k] > 58){
						tmp = false;						
						break;
					}
						tmp = true;
				}
				if(tmp){
					x = j - lexema.length() + 2;
					type = "numeric_constant";
					token.add(lexema, type, x, y);
					lexema = "";
					continue;
				}
			}
		}
	}
	x = str.length() + 1;
	token.add("", "eof", x , size);
}

void lexer::lex(char **argv){
	scan(argv);
	identification_token();
	token.display(argv);
}
