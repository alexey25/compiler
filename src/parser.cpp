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
	 if (lookahead->type == "print"|| 
        lookahead->type == "if"||
        lookahead->type == "while"||
        lookahead->type == "id"||
        lookahead->type == "return")
    {
        Anuthing(StartNode);
        StList(StartNode);
    }else
        if (lookahead->type == "comma" ||
		lookahead->type == "less_or_equal" || 
        lookahead->type == "more_or_equal" || 
        lookahead->type == "not_equal"||
        lookahead->type == "less" ||
        lookahead->type == "more" ||
        lookahead->type == "l_paren" ||
        lookahead->type == "r_paren" ||
        lookahead->type == "l_braket" ||
        lookahead->type == "r_braket" ||
        lookahead->type == "equally" ||
        lookahead->type == "semicolon")
    {
		printErrorMessage(lookahead->y,lookahead->x, "Stetement list");
        exit(1);
    }

}
void parser::Anuthing(AST* StartNode){
	if (lookahead->type == "print") {
		AST* printNode = initASTNode();
		setStroka(printNode, "print");
		add_child(printNode, StartNode);
		
		print(printNode);
	}else if (lookahead->type =="id"){
		id1(StartNode);
	} else if (lookahead->type == "if"){
		If(StartNode);
	} else if (lookahead->type == "while"){
		While(StartNode);
	} else if (lookahead->type == "def"){
		func(StartNode);
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
void parser::If(struct AST* StetementNode)
{
    struct AST* IfNode = initASTNode();
    setStroka(IfNode, "if");
    add_child(IfNode, StetementNode);

    match("if");

    Expr(IfNode);
    
    match("colon");
    match("l_brace");

    struct AST* StatNode = initASTNode();
    setStroka(StatNode, "StatementList");
    add_child(StatNode, IfNode);

    StList(StatNode); 
    match("r_brace");
    Else(IfNode);
}
/*
<else> -> else <else`> | E
*/
void parser::Else(struct AST* IfNode)
{
    if (lookahead->type == "else")
    {
        match("else");
        Else_T(IfNode);
    }
	if (lookahead->type == "elif")
    {
        match("elif");
        Elif_T(IfNode);
    }
}
/*
<else_t> -> { <statementList> } | <if> 
*/
void parser::Else_T(struct AST* IfNode)
{
    if (lookahead->type == "colon")
    {
        match("colon");
		match("l_brace");

        struct AST* StatNode = initASTNode();
        setStroka(StatNode, "StatementList");
        add_child(StatNode, IfNode);

        StList(StatNode);

	    match("r_brace");
    	Else(IfNode);	
    } 
}
void parser::Elif_T(struct AST* IfNode)
{
    Expr(IfNode);
    
    match("colon");
    match("l_brace");

    struct AST* StatNode = initASTNode();
    setStroka(StatNode, "StatementList");
    add_child(StatNode, IfNode);

    StList(StatNode); 
    match("r_brace");
    Else(IfNode);
}
/*
<while> -> while (<expr>) { <statementList> }
*/
void parser::While(struct AST* StetementNode)
{
    struct AST* WhileNode = initASTNode();
    setStroka(WhileNode, "while");
    add_child(WhileNode, StetementNode);
    
    match("while");

    Expr(WhileNode);

    match("colon");
    match("l_brace");

    struct AST* StatNode = initASTNode();
    setStroka(StatNode, "StatementList");
    add_child(StatNode, WhileNode);

    StList(StatNode);

    match("r_brace");
}
/*
<expr> -> numeric | id <compar>
*/
void parser::Expr(struct AST* Node)
{
    struct AST* ExprNode = initASTNode();
    setStroka(ExprNode, "Expresion");
    add_child(ExprNode, Node);

    if (lookahead->type == "numeric")
    {
        struct AST* NumericNode = initASTNode();
        setStroka(NumericNode, "numeric");
        setToken(NumericNode,  getLookahead());
        add_child(NumericNode, ExprNode);

        match("numeric");
    }else if (lookahead->type == "id")
    {
        struct AST* IdNode = initASTNode();
        setStroka(IdNode, "var");
        setToken(IdNode,  getLookahead());
        add_child(IdNode, ExprNode);
        

        match("id");
        Compar(ExprNode);
    }else{
		printErrorMessage(lookahead->y,lookahead->x, "Expresion");
        exit(1);
    }
}
/*
<copmar> -> <comparison> <id_or_num> | E
*/
void parser::Compar(struct AST* ExprNode){
    if (lookahead->type =="less_or_equal" || 
        lookahead->type =="no_compare" ||
        lookahead->type =="less" ||
        lookahead->type =="more" || 
        lookahead->type =="more_or_equal")
    {
        struct AST* ComparNode = initASTNode();
        setStroka(ComparNode, lookahead->type);
        swapChild(ExprNode, ComparNode);
        //add_child(ComparNode, ExprNode);

        Comparison(ExprNode);
       	Id_or_Num(ComparNode);
    }
}
/*
<comparison> -> == | != | < | <= | > | >=
*/
void parser::Comparison(struct AST* ExprNode)
{
    //struct AST* ComparNode = Init_Node_AST();
    if(lookahead->type =="less_or_equal")
    {
        match("less_or_equal");
    } else if (lookahead->type =="no_compare")
    {
        match("no_compare");
    } else if (lookahead->type =="less") 
    {
        match("less");
    } else if (lookahead->type =="more")
    {
        match("more");
    } else if (lookahead->type =="more_or_equal")
    {
        match("more_or_equal");
    }else{
		printErrorMessage(lookahead->y,lookahead->x, "comparison");
    	exit(1);
    }
}
/*
<or_and> -> || | && 
*/
void parser::Or_And()
{
    if (lookahead->type == "or")
    {
        match("or");
    }else if (lookahead->type == "and")
    {
        match("and");
    }else{
		printErrorMessage(lookahead->y,lookahead->x, "or_and");
        exit(1);
    }
}

void parser::Id_or_Num(struct AST* ComparNode)
{
    if (lookahead->type == "id")
    {
        struct AST* IdNode = initASTNode();
        setStroka(IdNode, "var");
        setToken(IdNode,  getLookahead());
       	add_child(IdNode, ComparNode);


        match("id");
    } else if (lookahead->type == "minus" ||
                lookahead->type == "plus" ||
                lookahead->type == "numeric")
    {
        Neg_Sings(ComparNode);

        if (lookahead->type != "numeric"){
			printErrorMessage(lookahead->y,lookahead->x, "numeric");
            exit(1);
        }
        struct AST* NumericNode = initASTNode();
        setStroka(NumericNode, "numeric");
        setToken(NumericNode, getLookahead());
        //Set_Token(IdNode,  parser->knots);
        add_child(NumericNode, ComparNode);

        match("numeric");
    }else
    {
        if (lookahead->type != "minus" ||
            lookahead->type != "plus" ||
            lookahead->type != "numeric" ||
            lookahead->type != "id") 
        {
			printErrorMessage(lookahead->y,lookahead->x, "calc");		
            exit(1);
        }
    }
}

void parser::Neg_Sings(AST* node)
{
    if (lookahead->type == "plus")
    {
        match("plus");
    }else if (lookahead->type == "minus")
    {
        match("minus");
    }
}
void parser::id1(AST *node) {
	AST* idNode = initASTNode();
	setStroka(idNode, "var");
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
