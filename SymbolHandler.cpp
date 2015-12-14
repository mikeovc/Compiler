//////////////// SymbolHandler.cpp

#include "SymbolHandler.h"
#include <iomanip>

SymbolHandler::SymbolHandler()
	: _address(3000) {}

void SymbolHandler::add(const std::string& id, const std::string& type) {
	_table[_address] = Symbol(id, type);
	_knownIds[id] = _address;
	_address++;
}

bool SymbolHandler::has(const std::string& id) {
	return !(_knownIds.find(id) == _knownIds.end());
}

int SymbolHandler::getAddress(const std::string& id) {
	return _knownIds[id];
}

std::ostream& operator<<(std::ostream& os, const SymbolHandler& sh) {
	os << std::left << std::setw(15) << "Identifier";
	os << std::left << std::setw(17) << "MemoryLocation";
	os << std::left << std::setw(10) << "Type";
	os << std::endl;

	for (auto it = sh._table.begin(); it != sh._table.end(); ++it) {
		os << std::left << std::setw(15) << it->second._id;
		os << std::left << std::setw(17) << it->first;
		os << std::left << std::setw(10) << it->second._type;
		os << std::endl;
	}

	return os;
}