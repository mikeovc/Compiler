///////////////////////// main.cpp
#include <iostream>
#include <fstream>
#include <list>
#include <iomanip>
#include "Token.h"
#include "Fsm.h"
#include "LexicalAnalyzer.h"

string getText();
void display(list<Token>& items);

int main() {
	string code = getText();
	list<Token> tokens;
	LexicalAnalyzer la(code);

	while (!la.analyzed()) {
		tokens.push_back(la.lexer());
	}
	la.initKnownTokenTypes(tokens);

	Fsm typeSetter;
	for (auto it = tokens.begin(); it != tokens.end(); ++it) {
		typeSetter.identify(*it);
	}

	display(tokens);

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

void display(list<Token>& items) {
	cout << "token                lexeme\n\n";
	for (auto it = items.begin(); it != items.end(); ++it) {
		cout << left << setw(21) << it->type() << setw(20) << it->lexeme() << endl;
	}
	cout << endl;
}
