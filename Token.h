//////////////////// Token.h
#ifndef __TOKEN__
#define __TOKEN__
#include <iostream>

// Class containing token information
class Token {
private:
	std::string _lexeme;
	std::string _type;

public:
	Token(std::string lexeme, std::string type="");
	// getters
	const std::string lexeme();
	const std::string type();
	// setters
	void lexeme(const std::string& lexeme);
	void type(const std::string& type);
};
#endif // !__TOKEN__