/////////////////////SyntaxAnalyzer.h

#ifndef __SYNTAX_ANALYZER__
#define __SYNTAX_ANALYZER__
#include <iostream>
#include <list>
#include <unordered_map>
#include "Token.h"
#include "SymbolHandler.h"
#include "InstrTable.h"

using namespace std;
class SyntaxAnalyzer {
private:
	list<Token> tokens;
	Token currentToken;
	SymbolHandler table;
	InstrTable instTable;

public:
	SyntaxAnalyzer(list<Token> t);

	void analyze();

private:
	void newToken();
	void errorMessage(const string& expected);
	void addToTable(const string& id, const string& type);
	void checkIdExistence(const string& id);

	// Grammatical procedures:
	void rat15F();
	void qualifier();
	void body();
	void optDeclList();
	void declList();
	void declListPrime();
	void decl();
	void ids(const string& type = "", bool fromRead = false);
	void idsPrime(const string& type = "", bool fromRead = false);
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
	void primary(bool isNegative = false);
	void primaryPrime();
};

#endif // !__SYNTAX_ANALYZER__