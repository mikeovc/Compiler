# ifndef __SYMBOL_HANDLER__
# define __SYMBOL_HANDLER__
#include <iostream>
#include <string>
#include <map>

struct Symbol {
	Symbol(std::string type="", int location=0)
		: _type(type), _location(location) {}
	std::string _type;
	int _location;
};

class SymbolHandler {
private:
	std::map<std::string, Symbol> _table;
	int _address;

public:
	SymbolHandler();

	void add(const std::string& id, const std::string& type);
	bool has(const std::string& id);

	friend std::ostream& operator<<(std::ostream& os, const SymbolHandler& sh);
};

# endif // !__SYMBOL_HANDLER__