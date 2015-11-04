////////////////////// Fsm.h
#ifndef __FSM__
#define __FSM__
#include <iostream>
#include "Token.h"

// This Finite State Machine class contains 3 finite state machines:
// idFSM, realFSM, and intFSM, which represent deterministic FSMs
// within a 2d array. Identifiers, integers, and real numbers are
// pushed through these FSMs and are identified based on the output state
class Fsm {
private:
	int idFSM[5][2];
	int realFSM[5][2];
	int intFSM[3][1];

	int currentState;
public:
	Fsm();
	void identify(Token& t);

private:
	bool isIdentifier(const std::string& lexeme);
	bool isRealNumber(const std::string& lexeme);
	bool isInteger(const std::string& lexeme);
};

#endif // !__FSM__