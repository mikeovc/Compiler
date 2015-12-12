/////////////////////SyntaxAnalyzer.h

#ifndef __SYNTAX_ANALYZER__
#define __SYNTAX_ANALYZER__
#include <iostream>
#include <list>
#include <unordered_map>
#include "Token.h"
#include "SymbolHandler.h"

using namespace std;
class SyntaxAnalyzer {
private:
	list<Token> tokens;
	Token currentToken;
	SymbolHandler table;

public:
	SyntaxAnalyzer(list<Token> t);

	void analyze();

private:
	void newToken();
	void errorMessage(const string& expected);
	void addToTable(const string& id, const string& type);

	// Grammatical procedures:
	void rat15F();
	void optFunDefs();	// fun = function; defs = definitions
	void funDefs();
	void funDefsPrime();
	void fun();
	void optParamList();
	void paramList();
	void paramListPrime();
	void param();
	void qualifier();
	void body();
	void optDeclList();
	void declList();
	void declListPrime();
	void decl();
	void ids(const string& type = "");
	void idsPrime(const string& type = "");
	void statementList();
	void stateListPrime();
	void statement();
	void compound();
	void assign();
	void ifProcedure();
	void ifProcPrime();
	void returnProcedure();
	void returnProcPrime();
	void write();
	void read();
	void whileProcedure();
	void condition();
	void relop();
	void expression();
	void expressionPrime();
	void term();
	void termPrime();
	void factor();
	void primary();
	void primaryPrime();
};

#endif // !__SYNTAX_ANALYZER__