//#ifndef __SYNTAX_ANALYZER__
//#define __SYNTAX_ANALYZER__
//#include <iostream>
//#include <list>
//#include <unordered_map>
//#include "Token.h"
//
//using namespace std;
//class SyntaxAnalyzer {
//private:
//	unordered_map<string, int> symbols;
//	list<string> nonTerminals;
//	list<string> terminals;
//	unordered_map<string, list<int>> ruleSet;
//	// 2 dimensional map for parse table:
//	unordered_map<string, unordered_map<string, list<string>>> parseTable;
//	list<Token> tokens;
//	Token currentToken;
//
//public:
//	SyntaxAnalyzer(list<Token> t);
//
//private:
//	void fillSymbols();
//	void fillRuleSet();
//	void constructParseTable();
//
//	// Grammatical procedures:
//	void rat15F();
//	void optFunDefs();	// fun = function; defs = definitions
//	void funDefs();
//	void fun();
//	void optParamList();
//	void paramList();
//	void param();
//	void qualifier();
//	void body();
//	void optDeclList();
//	void declList();
//	void decl();
//	void ids();
//};
//
//#endif // !__SYNTAX_ANALYZER__