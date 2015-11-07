//////////////////// Token.h
#ifndef __TOKEN__
#define __TOKEN__
#include <iostream>
#include <string>

// Class containing token information
class Token {
private:
	std::string _lexeme;
	std::string _type;

public:
	Token();
	Token(std::string lexeme, std::string type="");
	Token(const Token& other);	// copy constructor

	Token& operator=(const Token& t);	// assignment operator

	// getters
	const std::string lexeme();
	const std::string type();
	// setters
	void lexeme(const std::string& lexeme);
	void type(const std::string& type);

	friend std::ostream& operator<<(std::ostream& os, const Token& t);

private:
	void copy(const Token& other);
};
#endif // !__TOKEN__