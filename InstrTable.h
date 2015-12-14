/////////////////////// InstrTable.h

#ifndef __INSTR_TABLE__
#define __INSTR_TABLE__
#include <iostream>
#include <vector>
#include <stack>
#include <string>

const int NIL = -7777777;

struct Instruction {
	Instruction(int ad = NIL, std::string operatr = "", int operand = NIL)
		: address(ad), op(operatr), oprnd(operand) {}
	std::string op;
	int oprnd;
	int address;
};

class InstrTable {
private:
	std::vector<Instruction> _table;
	int _instAdress;
	std::stack<int> _jumpStack;

public:
	InstrTable();

	int instrAddress();

	void genInstr(std::string op, int oprnd);
	void backPatch(int jumpAddr);
	void backPatch();
	void pushJumpStack(int instrAddress);
	void pushJumpStack();

	friend std::ostream& operator<<(std::ostream& os, const InstrTable& tbl);
};

#endif // !__INSTR_TABLE 