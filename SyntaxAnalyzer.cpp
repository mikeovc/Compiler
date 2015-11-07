//#include "SyntaxAnalyzer.h"
//
//const int TERMINAL = 0, NONTERMINAL = 1;
//
//SyntaxAnalyzer::SyntaxAnalyzer(list<Token> t)
//: tokens(t) {
//	currentToken = tokens.front();
//	fillSymbols();
//	fillRuleSet();
//	constructParseTable();
//}
//
//void SyntaxAnalyzer::fillSymbols() {
//	symbols["Rat15F"] = NONTERMINAL;
//	symbols["Opt Function Definitions"] = NONTERMINAL;
//	symbols["Function Definitions"] = NONTERMINAL;
//	symbols["Function Definitions Prime"] = NONTERMINAL;
//	symbols["Function"] = NONTERMINAL;
//	symbols["Opt Parameter List"] = NONTERMINAL;
//	symbols["Parameter List"] = NONTERMINAL;
//	symbols["Parameter List Prime"] = NONTERMINAL;
//	symbols["Parameter"] = NONTERMINAL;
//	symbols["Qualifier"] = NONTERMINAL;
//	symbols["Body"] = NONTERMINAL;
//	symbols["Opt Declaration List"] = NONTERMINAL;
//	symbols["Declaration List"] = NONTERMINAL;
//	symbols["Declaration List Prime"] = NONTERMINAL;
//	symbols["Declaration"] = NONTERMINAL;
//	symbols["IDs"] = NONTERMINAL;
//	symbols["IDs Prime"] = NONTERMINAL;
//	symbols["Statement List"] = NONTERMINAL;
//	symbols["Statement List Prime"] = NONTERMINAL;
//	symbols["Statement"] = NONTERMINAL;
//	symbols["Compound"] = NONTERMINAL;
//	symbols["Assign"] = NONTERMINAL;
//	symbols["If"] = NONTERMINAL;
//	symbols["If Prime"] = NONTERMINAL;
//	symbols["Return"] = NONTERMINAL;
//	symbols["Return Prime"] = NONTERMINAL;
//	symbols["Write"] = NONTERMINAL;
//	symbols["Read"] = NONTERMINAL;
//	symbols["While"] = NONTERMINAL;
//	symbols["Condition"] = NONTERMINAL;
//	symbols["Relop"] = NONTERMINAL;
//	symbols["Expression"] = NONTERMINAL;
//	symbols["Expression Prime"] = NONTERMINAL;
//	symbols["Term"] = NONTERMINAL;
//	symbols["Term Prime"] = NONTERMINAL;
//	symbols["Factor"] = NONTERMINAL;
//	symbols["Primary"] = NONTERMINAL;
//	symbols["Primary Prime"] = NONTERMINAL;
//
//	symbols["identifier"] = TERMINAL;
//	symbols["real"] = TERMINAL;
//	symbols["integer"] = TERMINAL;
//	symbols["="] = TERMINAL;
//	symbols["!="] = TERMINAL;
//	symbols["<"] = TERMINAL;
//	symbols[">"] = TERMINAL;
//	symbols["=>"] = TERMINAL;
//	symbols["<="] = TERMINAL;
//	symbols["*"] = TERMINAL;
//	symbols["-"] = TERMINAL;
//	symbols["+"] = TERMINAL;
//	symbols["/"] = TERMINAL;
//	symbols[":="] = TERMINAL;
//	symbols["boolean"] = TERMINAL;
//	symbols["real"] = TERMINAL;
//	symbols["function"] = TERMINAL;
//	symbols["int"] = TERMINAL;
//	symbols["if"] = TERMINAL;
//	symbols["endif"] = TERMINAL;
//	symbols["else"] = TERMINAL;
//	symbols["return"] = TERMINAL;
//	symbols["write"] = TERMINAL;
//	symbols["read"] = TERMINAL;
//	symbols["while"] = TERMINAL;
//	symbols["do"] = TERMINAL;
//	symbols["true"] = TERMINAL;
//	symbols["false"] = TERMINAL;
//	symbols["@@"] = TERMINAL;
//	symbols["["] = TERMINAL;
//	symbols["]"] = TERMINAL;
//	symbols["("] = TERMINAL;
//	symbols[")"] = TERMINAL;
//	symbols["{"] = TERMINAL;
//	symbols["}"] = TERMINAL;
//	symbols[";"] = TERMINAL;
//	symbols[","] = TERMINAL;
//	symbols["Empty"] = TERMINAL;
//}
//
//void SyntaxAnalyzer::fillRuleSet() {
//	ruleSet["Rat15F"] = { { symbols["Opt Function Definitions"] }, { symbols["@@"] },
//							{ symbols["Opt Declaration List"], }, { symbols["Statement List"] } };
//	ruleSet["Opt Function Definitions"] = { { symbols["Function Definitions"] } };
//	ruleSet["Opt Function Definitions"] = { { symbols["Empty"] } };
//
//}
//
//void SyntaxAnalyzer::rat15F() {
//	optFunDefs();
//	if (currentToken.lexeme() == "@@") {
//		tokens.pop_front();
//		currentToken = tokens.front();
//
//	}
//}
//
////void SyntaxAnalyzer::fillNonTerminals() {
////	symbols["Rat15F"] = NONTERMINAL;
////	symbols["Opt Function Definitions"] = NONTERMINAL;
////	symbols["Function Definitions"] = NONTERMINAL;
////	symbols["Function"] = NONTERMINAL;
////	symbols["Opt Parameter List"] = NONTERMINAL;
////	symbols["Parameter List"] = NONTERMINAL;
////	symbols["Parameter"] = NONTERMINAL;
////	symbols["Qualifier"] = NONTERMINAL;
////	symbols["Body"] = NONTERMINAL;
////	symbols["Opt Declaration List"] = NONTERMINAL;
////	symbols["Declaration List"] = NONTERMINAL;
////	symbols["Declaration"] = NONTERMINAL;
////	symbols["IDs"] = NONTERMINAL;
////	symbols["Statement List"] = NONTERMINAL;
////	symbols["Statement"] = NONTERMINAL;
////	symbols["Compound"] = NONTERMINAL;
////	symbols["Assign"] = NONTERMINAL;
////	symbols["If"] = NONTERMINAL;
////	symbols["Return"] = NONTERMINAL;
////	symbols["Write"] = NONTERMINAL;
////	symbols["Read"] = NONTERMINAL;
////	symbols["While"] = NONTERMINAL;
////	symbols["Condition"] = NONTERMINAL;
////	symbols["Relop"] = NONTERMINAL;
////	symbols["Expression"] = NONTERMINAL;
////	symbols["Expression Prime"] = NONTERMINAL;
////	symbols["Term"] = NONTERMINAL;
////	symbols["Term Prime"] = NONTERMINAL;
////	symbols["Factor"] = NONTERMINAL;
////	symbols["Primary"] = NONTERMINAL;
////}
////
////void SyntaxAnalyzer::fillTerminals() {
////	symbols["identifier"] = NONTERMINAL;
////	symbols["real"] = NONTERMINAL;
////	symbols["integer"] = NONTERMINAL;
////	symbols["="] = NONTERMINAL;
////	symbols["!="] = NONTERMINAL;
////	symbols["<"] = NONTERMINAL;
////	symbols[">"] = NONTERMINAL;
////	symbols["=>"] = NONTERMINAL;
////	symbols["<="] = NONTERMINAL;
////	symbols["*"] = NONTERMINAL;
////	symbols["-"] = NONTERMINAL;
////	symbols["+"] = NONTERMINAL;
////	symbols["/"] = NONTERMINAL;
////	symbols[":="] = NONTERMINAL;
////	symbols["boolean"] = NONTERMINAL;
////	symbols["real"] = NONTERMINAL;
////	symbols["function"] = NONTERMINAL;
////	symbols["int"] = NONTERMINAL;
////	symbols["if"] = NONTERMINAL;
////	symbols["endif"] = NONTERMINAL;
////	symbols["else"] = NONTERMINAL;
////	symbols["return"] = NONTERMINAL;
////	symbols["write"] = NONTERMINAL;
////	symbols["read"] = NONTERMINAL;
////	symbols["while"] = NONTERMINAL;
////	symbols["do"] = NONTERMINAL;
////	symbols["true"] = NONTERMINAL;
////	symbols["false"] = NONTERMINAL;
////	symbols["@@"] = NONTERMINAL;
////	symbols["["] = NONTERMINAL;
////	symbols["]"] = NONTERMINAL;
////	symbols["("] = NONTERMINAL;
////	symbols[")"] = NONTERMINAL;
////	symbols["{"] = NONTERMINAL;
////	symbols["}"] = NONTERMINAL;
////	symbols[";"] = NONTERMINAL;
////	symbols[","] = NONTERMINAL;
////}