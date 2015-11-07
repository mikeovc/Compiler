#ifndef __SYNTAX_ANALYZER__
#define __SYNTAX_ANALYZER__
#include <iostream>
#include <list>
#include <unordered_map>
#include "Token.h"

using namespace std;
class SyntaxAnalyzer {
private:
	unordered_map<string, int> symbols;
	list<string> nonTerminals;
	list<string> terminals;
	unordered_map<string, list<int>> ruleSet;
	// 2 dimensional map for parse table:
	unordered_map<string, unordered_map<string, list<string>>> parseTable;
	list<Token> tokens;
	Token currentToken;

public:
	SyntaxAnalyzer(list<Token> t);

	void analyze();

private:
	void newToken();
	void errorMessage(const string& expected);

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
	void ids();
	void idsPrime();
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