# ifndef __SYMBOL_HANDLER__
# define __SYMBOL_HANDLER__
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

struct Symbol {
	Symbol(std::string id = "", std::string type = "")
		: _id(id), _type(type) {}
	std::string _id;
	std::string _type;
};

class SymbolHandler {
public:
	int _address;
	std::map<int, Symbol> _table;
	std::unordered_map<std::string, int> _knownIds;

public:
	SymbolHandler();

	void add(const std::string& id, const std::string& type);
	bool has(const std::string& id);
	int getAddress(const std::string& id);

	friend std::ostream& operator<<(std::ostream& os, const SymbolHandler& sh);
};

# endif // !__SYMBOL_HANDLER__