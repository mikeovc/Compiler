///////////////////////// main.cpp
#include <iostream>
#include <fstream>
#include <list>
#include <iomanip>
#include "Token.h"
#include "Fsm.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

string getText();
void display(list<Token>& items);

int main() {
	string code = getText();
	list<Token> tokens;
	LexicalAnalyzer la(code);

	// Lines 18-28: tokenize the entire text, store in tokens list
	while (!la.analyzed()) {
		tokens.push_back(la.lexer());
	}
	la.initKnownTokenTypes(tokens);

	Fsm typeSetter;
	for (auto it = tokens.begin(); it != tokens.end(); ++it) {
		typeSetter.identify(*it);
	}
	if (tokens.back().lexeme() == "") { tokens.back().type("eof"); }
	else { tokens.push_back(Token("", "eof")); }
	
	SyntaxAnalyzer sa(tokens);
	sa.analyze();

	//display(tokens);

	system("pause");
	return 0;
}

// Ask user for text file from which to read Rat15 code,
// return the full code or text.
string getText() {
	string path;
	cout << "Enter text file path: ";
	getline(cin, path);

	ifstream f(path);
	string line;
	string fullText = "";

	if (f) {
		while (!f.eof()) {
			getline(f, line);
			fullText += line;
		}
	}
	else {
		cout << "File not found.\n";
	}
	f.close();

	return fullText;
}

// Display Tokens for Project 1
void display(list<Token>& items) {
	cout << "token                lexeme\n\n";
	for (auto it = items.begin(); it != items.end(); ++it) {
		cout << *it << endl;
	}
	cout << endl;
}