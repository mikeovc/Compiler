# ifndef __SYMBOL_HANDLER__
# define __SYMBOL_HANDLER__
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Symbol {
	Symbol(std::string type="", int location=0)
		: _type(type), _location(location) {}
	std::string _type;
	int _location;
};

class SymbolHandler {
public:
	std::unordered_map<std::string, Symbol> _table;
	int _address;
	std::vector<std::string> _insertOrder;

public:
	SymbolHandler();

	void add(const std::string& id, const std::string& type);
	bool has(const std::string& id);

	friend std::ostream& operator<<(std::ostream& os, const SymbolHandler& sh);
};

# endif // !__SYMBOL_HANDLER__