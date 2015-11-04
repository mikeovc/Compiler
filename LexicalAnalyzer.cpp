///////////////////// LexicalAnalyzer.cpp
#include "LexicalAnalyzer.h"
const int OPERATOR = 1, KEYWORD = 2, SEPERATOR = 3;

LexicalAnalyzer::LexicalAnalyzer(string t) :
lexicalUnits({ { "=", OPERATOR }, { "!=", OPERATOR }, { ">", OPERATOR },
				{ "<", OPERATOR }, { "=>", OPERATOR }, { "<=", OPERATOR },
				{ "*", OPERATOR }, { "-", OPERATOR }, { "+", OPERATOR },
				{ "/", OPERATOR }, {":=", OPERATOR }, { "function", KEYWORD }, 
				{ "int", KEYWORD }, { "boolean", KEYWORD }, { "real", KEYWORD }, 
				{ "if", KEYWORD }, { "endif", KEYWORD }, { "else", KEYWORD }, 
				{ "return", KEYWORD }, { "write", KEYWORD }, { "read", KEYWORD }, 
				{ "while", KEYWORD }, { "do", KEYWORD }, { "true", KEYWORD }, 
				{ "false", KEYWORD }, { "@@", SEPERATOR }, { "[", SEPERATOR }, 
				{ "]", SEPERATOR }, { "(", SEPERATOR }, { ")", SEPERATOR }, 
				{ "{", SEPERATOR }, { "}", SEPERATOR }, { ";", SEPERATOR }, 
				{ ",", SEPERATOR } }),
text(t) {}

void LexicalAnalyzer::newText(const string& t) { text = t; }

// Lexer() analyzes the full input text and returns the first token it finds
Token LexicalAnalyzer::lexer() {
	size_t i = 0;
	while (i < text.size()) {
		// skip all whitespace
		if (isWhiteSpace(i)) { i++; }

		// ignore comment ( /* ... */ ) sections
		else if (i < text.size() - 1 && text[i] == '/' && text[i + 1] == '*') {
			i = text.find("*/");
			i = (i == string::npos) ? text.size() : i += 2;
		}

		// tokenize seperators and operators with more than one character
		else if (isSpecialCase(i)) {
			string specCase = text.substr(i, 2);
			text.erase(0, i + 2);
			return Token(specCase);
		}

		// add all other operators and seperators to token list
		else if (isOpOrSep(string(1, text[i]))) {
			string t(1, text[i]);
			text.erase(0, i + 1);
			return Token(t);
		}

		else {		// not a seperator or identifier
			string token = "";
			while (i < text.size() && !isWhiteSpace(i) &&
				!isOpOrSep(string(1, text[i]))) {
					token += text[i];
					i++;
			}
			text.erase(0, i);
			return Token(token);
		}
	}
}

// Return true if character is white space
bool LexicalAnalyzer::isWhiteSpace(const size_t i) {
	if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n') {
		return true;
	}
	return false;
}

// Return true if any operator or seperator with more than 1 character appears:
bool LexicalAnalyzer::isSpecialCase(const size_t i) {
	if (i < text.size() - 1 && 
		((text[i] == '@' && text[i + 1] == '@') ||
		(text[i] == '<' && text[i + 1] == '=') || 
		(text[i] == '=' && text[i + 1] == '>') ||
		(text[i] == '!' && text[i + 1] == '=') ||
		(text[i] == ':' && text[i + 1] == '='))) {
			return true;
	}
	return false;
}

// Return true if input char is a known operator or a separator:
bool LexicalAnalyzer::isOpOrSep(string c) {
	if (lexicalUnits[c] == OPERATOR || lexicalUnits[c] == SEPERATOR) {
		return true;
	}
	return false;
}

// Initialize keyword, operator, and seperator lexemes 
// to their appropriate types in the tokens list:
void LexicalAnalyzer::initKnownTokenTypes(list<Token>& tokes) {
	for (auto it = tokes.begin(); it != tokes.end(); ++it) {
		if (lexicalUnits[it->lexeme()] == OPERATOR) { it->type("operator"); }
		else if (lexicalUnits[it->lexeme()] == KEYWORD) { it->type("keyword"); }
		else if (lexicalUnits[it->lexeme()] == SEPERATOR) { it->type("seperator"); }
	}
}

// Return true if no text remaining:
bool LexicalAnalyzer::analyzed() {
	if (text.empty() || text.find_first_not_of(" \t\n") == string::npos) {
		return true;
	}
	return false;
}