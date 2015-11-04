////////////////////// LexicalAnalyzer.h
#ifndef __LEXICAL_ANALYZER__
#define __LEXICAL_ANALYZER__
#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <string>
#include "Token.h"
using namespace std;

// This really simple LexicalAnalyzer class seperates each token of
// Rat15 source code and identifies the knwon types, including:
// Operators, keywords, and seperators
class LexicalAnalyzer {
private:
	unordered_map<string, int> lexicalUnits;	// key for known types
	string text;

public:
	LexicalAnalyzer(string t);

	// setter:
	void newText(const string& t);

	Token lexer();
	void initKnownTokenTypes(list<Token>& tokes);
	bool analyzed();

private:
	bool isWhiteSpace(const size_t i);
	bool isSpecialCase(const size_t i);
	bool isOpOrSep(string c);
	
};

#endif // !__LEXICAL_ANALYZER__
