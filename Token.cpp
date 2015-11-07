///////////////////// Token.cpp
#include "Token.h"
#include <iomanip>

Token::Token() : _type(""), _lexeme("") {}

Token::Token(std::string lexeme, std::string type)
: _type(type), _lexeme(lexeme) {}

Token::Token(const Token& other) {
	copy(other);
}

Token& Token::operator=(const Token& t) {
	if (this != &t) { copy(t); }
	return *this;
}

void Token::copy(const Token& other) {
	_lexeme = other._lexeme;
	_type = other._type;
}

// getters
const std::string Token::type() { return _type; }
const std::string Token::lexeme() { return _lexeme; }

// setters
void Token::lexeme(const std::string& lexeme) { _lexeme = lexeme; }
void Token::type(const std::string& type) { _type = type; }

std::ostream& operator<<(std::ostream& os, const Token& t) {
	os << std::left << "Token: " << std::setw(15) << t._type
		<< "Lexeme: " << t._lexeme;
	return os;
}