#include <string>
#include <iostream>

using namespace std;

//lexer basically returns token to standardize stuff ig
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
	if (LastChar == '/') {
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

int main() {
	while(true) {
		int tok = gettok();
		cout << "got token: " << tok << endl;
	}
}










