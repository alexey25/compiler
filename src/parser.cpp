#include "parser.h"

AST* parser::pars(linkToken* Token){
	Token = Token;
	count = 0;
	tab = 0;
	lookahead = Token;
	root = NULL;
	start();
	printf("End parsing\n");
	return root;

}

void parser::start(){
	AST* StartNode = initASTNode();
	setStroka(StartNode, "start");
	root = StartNode;
	
	StList(StartNode);
}

void parser::StList(AST* StartNode){
	if (lookahead->type == "print") {
		AST* printNode = initASTNode();
		setStroka(printNode, "print");
		add_child(printNode, StartNode);
		
		print(printNode);
		StList(StartNode);
	}else if (lookahead->type =="id"){
		id1(StartNode);
		StList(StartNode);
	} else if (lookahead->type == "if"){
		if1(StartNode);
		StList(StartNode);
	} else if (lookahead->type == "while"){
		while1(StartNode);
		StList(StartNode);
	} else if (lookahead->type == "def"){
		func(StartNode);
		StList(StartNode);
	}
}
void parser::print(AST *node) {
	match("print");
	match("l_paren");
	printarg(node);
	match("r_paren");
}
void parser::printarg(struct AST *node) {
	if (lookahead->type == "id"){
		commaid(node);
	} else if (lookahead->type == "literal"){
		commaid(node);
	} else {
		printErrorMessage(lookahead->y,lookahead->x, "id or literal");
		exit(1);
	}  
}
void parser::commaid(AST* node){
	headcommaid(node);
	tailcommaid(node);
}

void parser::headcommaid(AST* node){
	if (lookahead->type == "id"){
		AST* idNode = initASTNode();
		setStroka(idNode, "var");
		setToken(idNode, getLookahead());
	
		add_child(idNode, node);
		match("id");
	}
	if (lookahead->type == "literal"){
		AST* literalNode = initASTNode();
		setStroka(literalNode, "literal");
		setToken(literalNode, getLookahead());

		add_child(literalNode, node);
		match("literal");
	}
}

void parser::tailcommaid(AST* node) {
	if (lookahead->type == "comma"){
		match("comma");
		if (lookahead->type == "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
	
			add_child(idNode, node);
			match("id");
			tailcommaid(node);
		}else if (lookahead->type == "literal"){
			AST* literalNode = initASTNode();
			setStroka(literalNode, "literal");
			setToken(literalNode, getLookahead());

			add_child(literalNode, node);
			match("literal");
			tailcommaid(node);
		}else{
			printErrorMessage(lookahead->y,lookahead->x, "id or literal");
			exit(1);		
		}
	}
}
void parser::id1(AST *node) {
	AST* idNode = initASTNode();
	setStroka(idNode, "id");
	setToken(idNode, getLookahead());
	add_child(idNode, node);
	match("id");
	id2(node);
}

void parser::id2(AST *node) {
	if(lookahead->type ==  "equally"){
	AST* equallyNode = initASTNode();
	setStroka(equallyNode, "equally");
	setToken(equallyNode, getLookahead());
	
	add_child(equallyNode, node);
	match("equally");
	idequally(node);
	}else if(lookahead->type ==  "l_paren"){
		idfunc(node);
	}/*else if(lookahead->type ==  "l_braket"){
		idmas(node);
	}*/
}

void parser::idequally(AST *node) {
	if(lookahead->type ==  "input"){
		AST* InputNode = initASTNode();
		setStroka(InputNode, "input");
		add_child(InputNode, node);
		input1(node);	
	}else if(lookahead->type ==  "id"){
		arithmetic(node);
	}else if(lookahead->type ==  "numeric_constant"){
		arithmetic(node);
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "id or numeric_constant");
		exit(1);
	}	
}
void parser::arithmetic(AST* node){
	headarithmetic(node);
	tailarithmetic(node);
}

void parser::headarithmetic(AST* node){
	if(lookahead->type ==  "id"){
		AST* idNode = initASTNode();
		setStroka(idNode, "var");
		setToken(idNode, getLookahead());
		add_child(idNode, node);
		match("id");
	
	}else if(lookahead->type ==  "numeric_constant"){
		AST* constNode = initASTNode();
		setStroka(constNode, "const");
		setToken(constNode, getLookahead());
	
		add_child(constNode, node);	
		match("numeric_constant");
	}
}

void parser::tailarithmetic(AST* node) {
	if (lookahead->type == "minus"){
		AST* minusNode = initASTNode();
		setStroka(minusNode, "minus");
		setToken(minusNode, getLookahead());
		add_child(minusNode, node);
		match("minus");
		if(lookahead->type ==  "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
			add_child(idNode, node);
			match("id");
			tailarithmetic(node);
	
		}else if(lookahead->type ==  "numeric_constant"){
			AST* constNode = initASTNode();
			setStroka(constNode, "const");
			setToken(constNode, getLookahead());
	
			add_child(constNode, node);	
			match("numeric_constant");
			tailarithmetic(node);
		}
	}else if (lookahead->type == "plus"){
		AST* plusNode = initASTNode();
		setStroka(plusNode, "plus");
		setToken(plusNode, getLookahead());
		add_child(plusNode, node);
		match("plus");
		if(lookahead->type ==  "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
			add_child(idNode, node);
			match("id");
			tailarithmetic(node);
	
		}else if(lookahead->type ==  "numeric_constant"){
			AST* constNode = initASTNode();
			setStroka(constNode, "const");
			setToken(constNode, getLookahead());
	
			add_child(constNode, node);	
			match("numeric_constant");
			tailarithmetic(node);
		}
	}else if (lookahead->type == "multiply"){
		AST* multiplyNode = initASTNode();
		setStroka(multiplyNode, "multiply");
		setToken(multiplyNode, getLookahead());
		add_child(multiplyNode, node);
		match("multiply");
		if(lookahead->type ==  "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
			add_child(idNode, node);
			match("id");
			tailarithmetic(node);
	
		}else if(lookahead->type ==  "numeric_constant"){
			AST* constNode = initASTNode();
			setStroka(constNode, "const");
			setToken(constNode, getLookahead());
	
			add_child(constNode, node);	
			match("numeric_constant");
			tailarithmetic(node);
		}
	}else if (lookahead->type == "div"){
		AST* divNode = initASTNode();
		setStroka(divNode, "div");
		setToken(divNode, getLookahead());
		add_child(divNode, node);
		match("div");
		if(lookahead->type ==  "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
			add_child(idNode, node);
			match("id");
			tailarithmetic(node);
	
		}else if(lookahead->type ==  "numeric_constant"){
			AST* constNode = initASTNode();
			setStroka(constNode, "const");
			setToken(constNode, getLookahead());
	
			add_child(constNode, node);	
			match("numeric_constant");
			tailarithmetic(node);
		}
	}else if (lookahead->type == "mod"){
		AST* modNode = initASTNode();
		setStroka(modNode, "mod");
		setToken(modNode, getLookahead());
		add_child(modNode, node);
		match("mod");
		if(lookahead->type ==  "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
			add_child(idNode, node);
			match("id");
			tailarithmetic(node);
	
		}else if(lookahead->type ==  "numeric_constant"){
			AST* constNode = initASTNode();
			setStroka(constNode, "const");
			setToken(constNode, getLookahead());
	
			add_child(constNode, node);	
			match("numeric_constant");
			tailarithmetic(node);
		}
	}else if (lookahead->type == "l_paren"){
		AST* l_parenNode = initASTNode();
		setStroka(l_parenNode, "l_paren");
		setToken(l_parenNode, getLookahead());
		add_child(l_parenNode, node);
		match("l_paren");
		if(lookahead->type ==  "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
			add_child(idNode, node);
			match("id");
			tailarithmetic(node);
	
		}else if(lookahead->type ==  "numeric_constant"){
			AST* constNode = initASTNode();
			setStroka(constNode, "const");
			setToken(constNode, getLookahead());
	
			add_child(constNode, node);	
			match("numeric_constant");
			tailarithmetic(node);
		}
	}else if (lookahead->type == "r_paren"){
		AST* r_parenNode = initASTNode();
		setStroka(r_parenNode, "r_paren");
		setToken(r_parenNode, getLookahead());
		add_child(r_parenNode, node);
		match("r_paren");
		if(lookahead->type ==  "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
			add_child(idNode, node);
			match("id");
			tailarithmetic(node);
	
		}else if(lookahead->type ==  "numeric_constant"){
			AST* constNode = initASTNode();
			setStroka(constNode, "const");
			setToken(constNode, getLookahead());
	
			add_child(constNode, node);	
			match("numeric_constant");
			tailarithmetic(node);
		}
	}		
}
void parser::idfunc(AST *node){
	match("l_paren");
	arg(node);
	match("r_paren");

}

void parser::arg(AST *node){
	if (lookahead->type == "id"){
		comma_arg(node);
	} else if (lookahead->type == "numeric_constant"){
		comma_arg(node);
	} 
}

void parser::comma_arg(AST* node){
	headcomma_arg(node);
	tailcomma_arg(node);
}

void parser::headcomma_arg(AST* node){
	if (lookahead->type == "id"){
		AST* idNode = initASTNode();
		setStroka(idNode, "var");
		setToken(idNode, getLookahead());
	
		add_child(idNode, node);
		match("id");
	}
	if (lookahead->type == "numeric_constant"){
		AST* numeric_constantNode = initASTNode();
		setStroka(numeric_constantNode, "numeric_constant");
		setToken(numeric_constantNode, getLookahead());

		add_child(numeric_constantNode, node);
		match("numeric_constant");
	}
}

void parser::tailcomma_arg(AST* node) {
	if (lookahead->type == "comma"){
		match("comma");
		if (lookahead->type == "id"){
			AST* idNode = initASTNode();
			setStroka(idNode, "var");
			setToken(idNode, getLookahead());
	
			add_child(idNode, node);
			match("id");
			tailcomma_arg(node);
		}else if (lookahead->type == "numeric_constant"){
			AST* numeric_constantNode = initASTNode();
			setStroka(numeric_constantNode, "numeric_constant");
			setToken(numeric_constantNode, getLookahead());

			add_child(numeric_constantNode, node);
			match("numeric_constant");
			tailcomma_arg(node);
		}else{
			printErrorMessage(lookahead->y,lookahead->x, "id or numeric_constant");
			exit(1);		
		}
	}
}

/*void parser::idmas(AST *node){

}*/

void parser::if1(AST *node){
	AST* ifNode = initASTNode();
	setStroka(ifNode, "if");
	setToken(ifNode, getLookahead());
	add_child(ifNode, node);
	match("if");
	usl(node);
	match("colon");
	block(node);
	while(lookahead->type ==  "else"){
		match("else");
		match("colon");
		block(node);
	}
}

void parser::block(AST *node){
	indent();
	nl();
	execution(node);
	dedent();
}

void parser::indent(){
	tab++;
}

void parser::dedent(){
	tab--;
}

void parser::nl(){
	int n = tab;
	while(n != 0){
		match("tab");
		n--;
	}
}

void parser::while1(AST *node){
	AST* whileNode = initASTNode();
	setStroka(whileNode, "while");
	setToken(whileNode, getLookahead());
	add_child(whileNode, node);
	match("while");
	usl(node);
	match("colon");
	block(node);
}
void parser::usl(AST *node) {
	if(lookahead->type ==  "id"){
		logic(node);
	}else if(lookahead->type ==  "numeric_constant"){
		logic(node);
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "id or numeric_constant");
		exit(1);
	}	
}
void parser::logic(AST* node){
	logic1(node);
	logic2(node);
	logic1(node);
}

void parser::logic1(AST* node){
	if(lookahead->type ==  "id"){
		AST* idNode = initASTNode();
		setStroka(idNode, "var");
		setToken(idNode, getLookahead());
		add_child(idNode, node);
		match("id");
	
	}else if(lookahead->type ==  "numeric_constant"){
		AST* constNode = initASTNode();
		setStroka(constNode, "const");
		setToken(constNode, getLookahead());
	
		add_child(constNode, node);	
		match("numeric_constant");
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "id or numeric_constant");
		exit(1);
	}
}

void parser::logic2(AST* node) {
	if (lookahead->type == "less"){
		AST* lessNode = initASTNode();
		setStroka(lessNode, "less");
		setToken(lessNode, getLookahead());
		add_child(lessNode, node);
		match("less");
	}else if (lookahead->type == "more"){
		AST* moreNode = initASTNode();
		setStroka(moreNode, "more");
		setToken(moreNode, getLookahead());
		add_child(moreNode, node);
		match("more");
	}else if (lookahead->type == "compare"){
		AST* compareNode = initASTNode();
		setStroka(compareNode, "compare");
		setToken(compareNode, getLookahead());
		add_child(compareNode, node);
		match("compare");
	}else if (lookahead->type == "more_or_equal"){
		AST* more_or_equalNode = initASTNode();
		setStroka(more_or_equalNode, "more_or_equal");
		setToken(more_or_equalNode, getLookahead());
		add_child(more_or_equalNode, node);
		match("more_or_equal");
	}else if (lookahead->type == "no_compare"){
		AST* no_compareNode = initASTNode();
		setStroka(no_compareNode, "no_compare");
		setToken(no_compareNode, getLookahead());
		add_child(no_compareNode, node);
		match("no_compare");
	}else if (lookahead->type == "less_or_equal"){
		AST* less_or_equalNode = initASTNode();
		setStroka(less_or_equalNode, "less_or_equal");
		setToken(less_or_equalNode, getLookahead());
		add_child(less_or_equalNode, node);
		match("less_or_equal");
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "logic");
		exit(1);
	}
}

void parser::execution(AST *node){
	if (lookahead->type == "print") {
		AST* printNode = initASTNode();
		setStroka(printNode, "print");
		add_child(printNode, node);
		
		print(printNode);
	}else if (lookahead->type =="id"){
		id1(node);
	} else if (lookahead->type == "if"){
		if1(node);
	}else if (lookahead->type == "while"){
		while1(node);
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "usl");
		exit(1);
	}

}
void parser::input1(AST* node) {
	match("input");
	input2(node);
}

void parser::input2(AST* node) {
	if (lookahead->type == "l_paren"){
		match("l_paren");
		input3(node);
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "l_paren");
		exit(1);
	}   
}

void parser::input3(AST* node) {
	if (lookahead->type == "literal"){
		AST* literalNode = initASTNode();
		setStroka(literalNode, "literal");
		add_child(literalNode, node);

		match("literal");
		input4(literalNode);
	} else 	if(lookahead->type == "r_paren"){
		match("r_paren");
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "r_paren or literal");
		exit(1);
	}
}
void parser::input4(AST* node) {
	if (lookahead->type == "r_paren"){
		match("r_paren");
	}else{
		printErrorMessage(lookahead->y,lookahead->x, "r_paren");
		exit(1);
	}   
}

void parser::func(AST* StartNode) {
	struct AST* FuncNode = initASTNode();
	setStroka(FuncNode, "def");
	add_child(FuncNode, StartNode);

	match("def");
	match("id");
	match("l_paren");
	struct AST *argListNode = initASTNode();
	setStroka(argListNode, "argList");
	add_child(argListNode, FuncNode);

	commaid(argListNode);
	match("r_paren");
	match("colon");
	
}

void parser::consume(){
	lookahead = nextToken(); 
}

linkToken* parser::nextToken(){
	count++;
	return lookahead->next;
}

linkToken* parser::getLookahead(){
	return lookahead;
}
void parser::match(string x) {
	if(lookahead->type == x){
		consume();
	} else {
		printErrorMessage(lookahead->y,lookahead->x, x);
		exit(1);
	}
}

void parser::printErrorMessage(int row, int column, string x) {
	cout << row << ":" << column << " error: expecting: " << x << " find " << endl;
}
