///////////////////// Token.cpp
#include "Token.h"

Token::Token(std::string lexeme, std::string type)
: _type(type), _lexeme(lexeme) {}

// getters
const std::string Token::type() { return _type; }
const std::string Token::lexeme() { return _lexeme; }

// setters
void Token::lexeme(const std::string& lexeme) { _lexeme = lexeme; }
void Token::type(const std::string& type) { _type = type; }
