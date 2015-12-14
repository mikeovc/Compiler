//////////////////////// InstrTable.cpp

#include "InstrTable.h"
#include <iomanip>

InstrTable::InstrTable() : _instAdress(1) {}

int InstrTable::instrAddress() { return _instAdress; }

void InstrTable::genInstr(std::string op, int oprnd) {
	_table.push_back(Instruction(_instAdress, op, oprnd));
	_instAdress++;
}

void InstrTable::backPatch(int jumpAddr) {
	int addr = _jumpStack.top();
	_jumpStack.pop();
	_table[addr].oprnd = jumpAddr;
}

void InstrTable::backPatch() {
	int addr = _jumpStack.top();
	_jumpStack.pop();
	_table[--addr].oprnd = _instAdress;
}

void InstrTable::pushJumpStack(int instrAddress) {
	_jumpStack.push(instrAddress);
}

void InstrTable::pushJumpStack() {
	_jumpStack.push(_instAdress);
}

std::ostream& operator<<(std::ostream& os, const InstrTable& tbl) {
	os << std::left << std::setw(9) << "Adress";
	os << std::left << std::setw(9) << "Op";
	os << std::left << std::setw(9) << "Oprnd";
	os << std::endl;

	for (auto it = tbl._table.begin(); it != tbl._table.end(); ++it) {
		os << std::left << std::setw(9) << it->address;
		os << std::left << std::setw(9) << it->op;
		if (it->oprnd == NIL) {
			os << std::left << std::setw(9) << "nil";
		}
		else {
			os << std::left << std::setw(9) << it->oprnd;
		}
		os << std::endl;
	}

	return os;
}