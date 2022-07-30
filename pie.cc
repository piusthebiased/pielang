#include <string>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

//part 1, create a laxer
//lexer basically returns token to standardize stuff ig
//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

//tokenize enumeration
enum Token {
	tok_eof = -1,				//end of file
	tok_void = -2,				//function
	tok_extern = -3,			//external library
	tok_identifier = -4,		//identifier/var name
	tok_number = -5				//identify number
};

static std::string IdentifierStr; //fill if a tok_identifier is identified
static double NumVal; //filled when a number is identified
//static bool FloatHandling;  // will do when i understand llvm more.

//return next token from stdin
static int gettok() {
	//placeholder
	static int LastChar = ' ';

	//skips whitespaces, i.e. a tab, should implenet later lol
	while(isspace(LastChar)) LastChar = getchar();
	
	//this identifies types and names
	if(isalpha(LastChar)) {
		IdentifierStr = LastChar;

		//while the next char is alphanumeric, read the next char.
		while(isalnum((LastChar = getchar()))) IdentifierStr += LastChar;

		//if the identifier is one of these two, return the token.
		if(IdentifierStr == "void") return tok_void;
		if(IdentifierStr == "extern") return tok_extern;

		//else, return the identifier, i.e. "help(me)"
		return tok_identifier;
	}
	
	//if the next character is a number, follow these procedures.
	//only handles f64
	if(isdigit(LastChar) || LastChar == '.') {
		std::string NumStr;
		do {
			NumStr += LastChar;
			LastChar = getchar();
		} while (isdigit(LastChar) || LastChar == '.');

		NumVal = strtod(NumStr.c_str(), 0);
		return tok_number;
	}

	//handle commenting
	if (LastChar == '#') { // figure out how to do double comment later
		//comments until the newline char.
		do LastChar = getchar();
		while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

		if (LastChar != EOF) return gettok();
	}

	//check for end of file
	if(LastChar == EOF) return tok_eof;

	//otherwise return the char as its given thing.
	int ThisChar = LastChar;
	LastChar = getchar();
	return ThisChar;
}

//part 2, the abstract syntax tree(ast)
//so the ast basically models a language (kinda?) idk this is gonna be fun!
//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//

namespace {

//base class for all
class ExprAST {
public:
	virtual ~ExprAST() {} //virtual meaning a subclass can override this implentation
};

//abstract syntax tree for numeric values
class NumberExprAST : public ExprAST {
	double Val;

public:
	//initializer list, assigns variable to class.  think getters & setters
	NumberExprAST(double Val)
		: Val(Val) {}
};

//syntax tree for variables
class VariableExprAST : public ExprAST {
	std::string Name;

public:
	VariableExprAST(const std::string &Name)
		: Name(Name) {}
};

//syntax tree for binary
class BinaryExprAST : public ExprAST {
	char Op;
	std::unique_ptr<ExprAST> LHS, RHS;

public:
	BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
		: Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

//function calls syntax tree
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAST>> Args)
	: Callee(Callee), Args(std::move(Args)) {}
};

//prototype function syntax tree, captures the name and the arguments
//basically represents the function, as a prototype.
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &Name, std::vector<std::string> Args)
	: Name(Name), Args(std::move(Args)) {}

  const std::string &getName() const { return Name; }
};

//function syntax tree
//this represents the function itself.
class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

} //end anon namespace

//placeholder for compilation
int main(){
	cout << "Hello world!" << endl;
}






















