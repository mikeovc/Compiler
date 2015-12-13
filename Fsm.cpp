//////////////////////////// Fsm.cpp
#include "Fsm.h"

const int LETTER = 0, UNDERSCORE = 1, DIGIT = 0, PERIOD = 1;

Fsm::Fsm()
: idFSM{ { 1, 4 }, { 2, 3 }, { 2, 3 }, { 2, 3 }, { 4, 4 } },
realFSM{ { 1, 2 }, { 1, 2 }, { 3, 4 }, { 3, 4 }, { 4, 4 } },
intFSM{ { 1 }, { 1 }, { 2 } }, currentState(0) {}

void Fsm::identify(Token& t) {
	if (t.type() == "") {
		if (isIdentifier(t.lexeme())) { t.type("identifier"); }
		else if (isRealNumber(t.lexeme())) { t.type("real"); }
		else if (isInteger(t.lexeme())) { t.type("integer"); }
		else { t.type("unknown"); }
	}
}

// isIdentifier uses the idFSM key to navigate between states and 
// return true if it ends on an accepting state, or false otherwise.
bool Fsm::isIdentifier(const std::string& lexeme) {
	currentState = 0;
	for (size_t i = 0; i < lexeme.size(); i++) {
		if (isalpha(lexeme[i])) {
			currentState = idFSM[currentState][LETTER];
		}
		else if (lexeme[i] == '_') {
			currentState = idFSM[currentState][UNDERSCORE];
		}
		else {	// char not a letter or an underscore
			currentState = 4;	// rejected state for identifier FSM
		}
	}
	if (currentState == 1 || currentState == 2) { return true; }
	else { return false; }
}

// isRealNumber uses teh realFSM key to navigate between states and
// return true if it ends on an accepting state, or false otherwise.
bool Fsm::isRealNumber(const std::string& lexeme) {
	currentState = 0;
	for (size_t i = 0; i < lexeme.size(); i++) {
		if (isdigit(lexeme[i])) {
			currentState = realFSM[currentState][DIGIT];
		}
		else if (lexeme[i] == '.') {
			currentState = realFSM[currentState][PERIOD];
		}
		else {
			currentState = 4;	// rejected state for real number FSM
		}
	}
	if (currentState == 3) { return true; }
	else { return false; }
}

// isInteger uses teh intFSM key to navigate between states and
// return true if it ends on an accepting state, or false otherwise.
bool Fsm::isInteger(const std::string& lexeme) {
	currentState = 0;
	for (size_t i = 0; i < lexeme.size(); i++) {
		if (isdigit(lexeme[i])) {
			currentState = intFSM[currentState][DIGIT];
		}
		else {
			currentState = 2;	// rejected state for int FSM
		}
	}
	if (currentState == 1) { return true; }
	else { return false; }
}