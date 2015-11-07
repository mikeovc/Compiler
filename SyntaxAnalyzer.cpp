#include "SyntaxAnalyzer.h"

const int TERMINAL = 0, NONTERMINAL = 1, NEW_PRODUCTION = 2;

SyntaxAnalyzer::SyntaxAnalyzer(list<Token> t)
: tokens(t) {
	currentToken = tokens.front();
	fillSymbols();
}

void SyntaxAnalyzer::fillSymbols() {
	symbols["<Rat15F>"] = NONTERMINAL;
	symbols["<Opt Function Definitions>"] = NONTERMINAL;
	symbols["<Function Definitions>"] = NONTERMINAL;
	symbols["<Function Definitions Prime>"] = NONTERMINAL;
	symbols["<Function>"] = NONTERMINAL;
	symbols["<Opt Parameter List>"] = NONTERMINAL;
	symbols["<Parameter List>"] = NONTERMINAL;
	symbols["<Parameter List Prime>"] = NONTERMINAL;
	symbols["<Parameter>"] = NONTERMINAL;
	symbols["<Qualifier>"] = NONTERMINAL;
	symbols["<Body>"] = NONTERMINAL;
	symbols["<Opt Declaration List>"] = NONTERMINAL;
	symbols["<Declaration List>"] = NONTERMINAL;
	symbols["<Declaration List Prime>"] = NONTERMINAL;
	symbols["<Declaration>"] = NONTERMINAL;
	symbols["<IDs>"] = NONTERMINAL;
	symbols["<IDs Prime>"] = NONTERMINAL;
	symbols["<Statement List>"] = NONTERMINAL;
	symbols["<Statement List Prime>"] = NONTERMINAL;
	symbols["<Statement>"] = NONTERMINAL;
	symbols["<Compound>"] = NONTERMINAL;
	symbols["<Assign>"] = NONTERMINAL;
	symbols["<If>"] = NONTERMINAL;
	symbols["<If Prime>"] = NONTERMINAL;
	symbols["<Return>"] = NONTERMINAL;
	symbols["<Return Prime>"] = NONTERMINAL;
	symbols["<Write>"] = NONTERMINAL;
	symbols["<Read>"] = NONTERMINAL;
	symbols["<While>"] = NONTERMINAL;
	symbols["<Condition>"] = NONTERMINAL;
	symbols["<Relop>"] = NONTERMINAL;
	symbols["<Expression>"] = NONTERMINAL;
	symbols["<Expression Prime>"] = NONTERMINAL;
	symbols["<Term>"] = NONTERMINAL;
	symbols["<Term Prime>"] = NONTERMINAL;
	symbols["<Factor>"] = NONTERMINAL;
	symbols["<Primary>"] = NONTERMINAL;
	symbols["<Primary Prime>"] = NONTERMINAL;

	symbols["identifier"] = TERMINAL;
	symbols["real"] = TERMINAL;
	symbols["integer"] = TERMINAL;
	symbols["="] = TERMINAL;
	symbols["!="] = TERMINAL;
	symbols["<"] = TERMINAL;
	symbols[">"] = TERMINAL;
	symbols["=>"] = TERMINAL;
	symbols["<="] = TERMINAL;
	symbols["*"] = TERMINAL;
	symbols["-"] = TERMINAL;
	symbols["+"] = TERMINAL;
	symbols["/"] = TERMINAL;
	symbols[":="] = TERMINAL;
	symbols["boolean"] = TERMINAL;
	symbols["real"] = TERMINAL;
	symbols["function"] = TERMINAL;
	symbols["int"] = TERMINAL;
	symbols["if"] = TERMINAL;
	symbols["endif"] = TERMINAL;
	symbols["else"] = TERMINAL;
	symbols["return"] = TERMINAL;
	symbols["write"] = TERMINAL;
	symbols["read"] = TERMINAL;
	symbols["while"] = TERMINAL;
	symbols["do"] = TERMINAL;
	symbols["true"] = TERMINAL;
	symbols["false"] = TERMINAL;
	symbols["@@"] = TERMINAL;
	symbols["["] = TERMINAL;
	symbols["]"] = TERMINAL;
	symbols["("] = TERMINAL;
	symbols[")"] = TERMINAL;
	symbols["{"] = TERMINAL;
	symbols["}"] = TERMINAL;
	symbols[";"] = TERMINAL;
	symbols[","] = TERMINAL;
	symbols["Empty"] = TERMINAL;

	symbols["|"] = NEW_PRODUCTION;
}

//void SyntaxAnalyzer::fillRuleSet() {
//	ruleSet["<Rat15F>"] = { symbols["<Opt Function Definitions>"], symbols["@@"], 
//						  symbols["<Opt Declaration List>"], symbols["<Statement List>"] };
//	ruleSet["<Opt Function Definitions>"] = { symbols["<Function Definitions>"], symbols["|"],
//											symbols["Empty"] };
//	ruleSet["<Function Definitions>"] = { symbols["<Function>"], symbols["|"],
//										symbols["<Function Definitions Prime>"] };
//	ruleSet["<Function Definitions Prime>"] = { symbols["<Function>"], symbols["<Function Definitions>"] };
//	ruleSet["<Function>"] = { symbols["function"] };
//}

//void SyntaxAnalyzer::fillRuleSet() {
//	ruleSet["<Rat15F>"] = 
//}

void SyntaxAnalyzer::newToken() {
	tokens.pop_front();
	currentToken = tokens.front();
}

void SyntaxAnalyzer::errorMessage(const string& expected) {
	cout << "Error after token \"" << currentToken.lexeme() 
		<< "\". First of \"" << expected << "\" expected.";
	system("pause");
}

void SyntaxAnalyzer::rat15F() {
	cout << "<Rat15F> -> <Opt Function Definitions> \n@@ <Opt Declaration List> \n"
		<< "\t@@ <Statement List>" << endl;
	optFunDefs();

	if (currentToken.lexeme() == "@@") {
		newToken();
		cout << currentToken << endl;
	}
	else {
		errorMessage("@@");
		return;
	}

	optDeclList();

	if (currentToken.lexeme() == "@@") {
		newToken();
		cout << currentToken << endl;
	}
	else {
		errorMessage("@@");
		return;
	}

	statementList();
}

void SyntaxAnalyzer::optFunDefs() {
	if (currentToken.lexeme() == "function") {
		cout << "<Opt Function Definitions> -> <Function Definitions>" << endl;
		funDefs();
	}
	else {
		cout << "<Opt Function Definitions> -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::funDefs() {
	cout << "<Function Definitions> -> <Function> <Function Definitons>'" << endl;
	fun();
	funDefsPrime();
}

void SyntaxAnalyzer::funDefsPrime() {
	if (currentToken.lexeme() == "function") {
		cout << "<Function Definitions>' -> <Function Definitions>" << endl;
		funDefs();
	}
	else {
		cout << "<Function Definitions>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::fun() {
	if (currentToken.lexeme() == "function") {
		cout << "<Function> -> function <Identifier> [ <Opt Parameter List> ]\n"
			<< "\t<Opt Declaration List>" "<Body>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("function"); }

	if (currentToken.type() == "identifier") {
		cout << "<Function> -> function <Identifier> [ <Opt Parameter List> ]\n"
			<< "\t<Opt Declaration List>" "<Body>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("<Identifier>"); }

	if (currentToken.lexeme() == "[") {
		cout << "<Function> -> function <Identifier> [ <Opt Parameter List> ]\n"
			<< "\t<Opt Declaration List>" "<Body>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("["); }

	optParamList();

	if (currentToken.lexeme() == "]") {
		cout << "<Function> -> function <Identifier> [ <Opt Parameter List> ]\n"
			<< "\t<Opt Declaration List>" "<Body>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("]"); }

	optDeclList();

	body();
}

void SyntaxAnalyzer::optParamList() {
	if (currentToken.type() == "identifier") {
		cout << "<Opt Parameter List> -> <Parameter List>" << endl;
		paramList();
	}
	else {
		cout << "<Opt Paramter List> -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::paramList() {
	cout << "<Parameter List> -> <Parameter> <Parameter List>'" << endl;
	param();
	paramListPrime();
}

void SyntaxAnalyzer::paramListPrime() {
	if (currentToken.type() == "identifier") {
		cout << "<Parameter List>' -> <Paramter List>" << endl;
		paramList();
	}
	else {
		cout << "<Parameter List>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::param() {
	cout << "<Parameter> -> <IDs> <Qualifier>" << endl;
	ids();
	qualifier();
}

void SyntaxAnalyzer::qualifier() {
	if (currentToken.lexeme() == "int" || currentToken.lexeme() == "boolean"
		|| currentToken.lexeme() == "real") {
		cout << "<Qualifier> -> " << currentToken.lexeme() << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("int\", \"boolean\", or \"real"); }
}

void SyntaxAnalyzer::body() {
	if (currentToken.lexeme() == "{") {
		cout << "<Body> -> { <Statment List> }" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("{"); }
	
	statementList();

	if (currentToken.lexeme() == "}") {
		cout << "<Body> -> { <Statment List> }" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("}"); }
}

void SyntaxAnalyzer::optDeclList() {
	if (currentToken.lexeme() == "int" || currentToken.lexeme() == "boolean"
		|| currentToken.lexeme() == "real") {
		cout << "<Opt Declaration List> -> <Declaration List>" << endl;
		declList();
	}
	else {
		cout << "<Opt Declaration List> -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::declList() {
	cout << "<Declaration List> -> <Declaration> <Declaration List>'" << endl;
	decl();
	declListPrime();
}

void SyntaxAnalyzer::declListPrime() {
	if (currentToken.lexeme() == "int" || currentToken.lexeme() == "boolean"
		|| currentToken.lexeme() == "real") {
		cout << "<Declaration List>' -> <Declaration List>" << endl;
		declList();
	}
	else {
		cout << "Declaration List>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::decl() {
	cout << "<Declaration> -> <Qualifier> <IDs>" << endl;
	qualifier();
	ids();
}

void SyntaxAnalyzer::ids() {
	if (currentToken.type() == "identifier") {
		cout << "<IDs> -> <Identifier> <IDs>'" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("<Identifier>"); }
	idsPrime();
}

void SyntaxAnalyzer::idsPrime() {
	if (currentToken.type() == "identifier") {
		cout << "<IDs>' -> <IDs>" << endl;
		ids();
	}
	else {
		cout << "<IDs>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::statementList() {
	cout << "<Statement List> -> <Statement> <Stament List>'" << endl;
	statement();
	stateListPrime();
}

void SyntaxAnalyzer::stateListPrime() {
	if (currentToken.lexeme() == "{" || currentToken.type() == "identifier"
		|| currentToken.lexeme() == "if" || currentToken.lexeme() == "return"
		|| currentToken.lexeme() == "write" || currentToken.lexeme() == "read"
		|| currentToken.lexeme() == "while") {
			cout << "<Statement List>' -> <Statement List>" << endl;
			statementList();
	}
	else {
		cout << "<Statement List>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::statement() {
	if (currentToken.lexeme() == "{") {
		cout << "<Statement> -> <Compound>" << endl;
		compound();
	}
	else if (currentToken.type() == "identifier") {
		cout << "<Statement> -> <Assign>" << endl;
		assign();
	}
	else if (currentToken.lexeme() == "if") {
		cout << "<Statement> -> <If>" << endl;
		ifProcedure();
	}
	else if (currentToken.lexeme() == "return") {
		cout << "<Statement> -> <Return>" << endl;
		returnProcedure();
	}
	else if (currentToken.lexeme() == "write") {
		cout << "<Statement> -> <Write>" << endl;
		write();
	}
	else if (currentToken.lexeme() == "read") {
		cout << "<Statement> -> <Write>" << endl;
		read();
	}
	else if (currentToken.lexeme() == "while") {
		cout << "<Statement> -> <While>" << endl;
		whileProcedure();
	}
	else { errorMessage("}\", <Identifer>, \"if\", \"return\", \"write\", \"read\", or \"while"); }
}

void SyntaxAnalyzer::compound() {
	if (currentToken.lexeme() == "{") {
		cout << "<Compound> -> { <Statement List> }" << endl;
		newToken();
		cout << currentToken << endl;		
	}
	else { errorMessage("{"); }

	statementList();

	if (currentToken.lexeme() == "}") {
		cout << "<Compound> -> { <Statement List> }" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("}"); }
}

void SyntaxAnalyzer::assign() {
	if (currentToken.type() == "identifier") {
		cout << "<Assign> -> <Identifier> := <Expression>";
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("<Identifier>"); }

	if (currentToken.lexeme() == ":=") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage(":="); }

	expression();
}

void SyntaxAnalyzer::ifProcedure() {
	if (currentToken.lexeme() == "if") {
		cout << "<If> -> if ( <Condition> ) <Statement> <If>'" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("if"); }

	if (currentToken.lexeme() == "(") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("("); }

	condition();

	if (currentToken.lexeme() == ")") {
		cout << "<If> -> if ( <Condition> ) <Statement> <If>'" << endl;
		newToken();
		cout << currentToken << endl;
	}
	
	statement();

	ifProcPrime();
}

void SyntaxAnalyzer::ifProcPrime() {
	if (currentToken.lexeme() == "endif") {
		cout << "<If>' -> endif" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "else") {
		cout << "<If>' -> else <Statement> endif" << endl;
		newToken();
		cout << currentToken << endl;

		statement();

		if (currentToken.lexeme() == "endif") {
			cout << "<If>' -> else <Statement> endif" << endl;
			newToken();
			cout << currentToken << endl;
		}
		else { errorMessage("endif"); }
	}
	else { errorMessage("endif\" or \"else"); }
}

void SyntaxAnalyzer::returnProcedure() {
	if (currentToken.lexeme() == "return") {
		cout << "<Return> -> return <Return>'" << endl;
		newToken();
		cout << currentToken << endl;

		returnProcPrime();
	}
	else { errorMessage("return"); }
}

void SyntaxAnalyzer::returnProcPrime() {
	if (currentToken.lexeme() == "-" || currentToken.type() == "identifier"
		|| currentToken.type() == "integer" || currentToken.lexeme() == "("
		|| currentToken.type() == "real" || currentToken.lexeme() == "true"
		|| currentToken.type() == "false") {
		cout << "<Return>' -> <Expression>" << endl;
	}
	else {
		cout << "<Return>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::write() {
	if (currentToken.lexeme() == "write") {
		cout << "<Write> -> write ( <Expression> );" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("write"); }

	if (currentToken.lexeme() == "(") {
		newToken();
		cout << currentToken << endl;
	}

	expression();

	if (currentToken.lexeme() == ")") {
		cout << "<Write> -> write ( <Expression> );" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage(")"); }

	if (currentToken.lexeme() == ";") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage(";"); }
}

void SyntaxAnalyzer::read() {
	if (currentToken.lexeme() == "read") {
		cout << "<Read> -> read ( <IDs> );" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("read"); }

	if (currentToken.lexeme() == "(") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("("); }

	ids();

	if (currentToken.lexeme() == ")") {
		cout << "<Read> -> read ( <IDs> );" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage(")"); }

	if (currentToken.lexeme() == ";") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage(";"); }
}

void SyntaxAnalyzer::whileProcedure() {
	if (currentToken.lexeme() == "while") {
		cout << "<While> -> while ( <Condition> ) do <Statement>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("while"); }

	if (currentToken.lexeme() == "(") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("("); }

	condition();

	if (currentToken.lexeme() == ")") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage(")"); }

	if (currentToken.lexeme() == "do") {
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("do"); }

	statement();
}

void SyntaxAnalyzer::condition() {
	cout << "<Condition> -> <Expression> <Relop> <Expression>" << endl;
	expression();
	relop();
	expression();
}

void SyntaxAnalyzer::relop() {
	if (currentToken.lexeme() == "=") {
		cout << "<Relop> -> =" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "!=") {
		cout << "<Relop> -> !=" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == ">") {
		cout << "<Relop> -> >" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "<") {
		cout << "<Relop> -> <" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "=>") {
		cout << "<Relop> -> =>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "<=") {
		cout << "<Relop> -> <=" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("=\", \"!=\", \">\", \"<\", \"=>\", or \"<="); }
}

void SyntaxAnalyzer::expression() {
	cout << "<Expression> -> <Term> <Expression>'" << endl;
	term();
	expressionPrime();
}

void SyntaxAnalyzer::expressionPrime() {
	if (currentToken.lexeme() == "+") {
		cout << "<Expression>' -> + <Term> <Expression>'" << endl;
		newToken();
		cout << currentToken << endl;

		term();
		expressionPrime();
	}
	else if (currentToken.lexeme() == "-") {
		cout << "<Expression>' -> - <Term> <Expression>'" << endl;
		newToken();
		cout << currentToken << endl;

		term();
		expressionPrime();
	}
	else {
		cout << "<Expression>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::term() {
	cout << "<Term> -> <Factor> <Term>'" << endl;
	factor();
	termPrime();
}

void SyntaxAnalyzer::termPrime() {
	if (currentToken.lexeme() == "*") {
		cout << "<Term>' -> * <Factor> <Term>'" << endl;
		newToken();
		cout << currentToken << endl;

		factor();
		termPrime();
	}
	else if (currentToken.lexeme() == "/") {
		cout << "<Term>' -> / <Factor> <Term>'" << endl;
		newToken();
		cout << currentToken << endl;

		factor();
		termPrime();
	}
	else {
		cout << "<Term>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::factor() {
	if (currentToken.lexeme() == "-") {
		cout << "<Factor> -> - <Primary>" << endl;
		newToken();
		cout << currentToken << endl;

		primary();
	}
	else { primary(); }
}

void SyntaxAnalyzer::primary() {
	if (currentToken.type() == "identifier") {
		cout << "<Primary> -> <Identifier> <Primary>'" << endl;
		newToken();
		cout << currentToken << endl;

		primaryPrime();
	}
	else if (currentToken.type() == "integer") {
		cout << "<Primary> -> <Integer>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "(") {
		cout << "<Primary> -> ( <Expression> )" << endl;
		newToken();
		cout << currentToken << endl;

		expression();

		if (currentToken.lexeme() == ")") {
			cout << "<Primary> -> ( <Expression> )" << endl;
			newToken();
			cout << currentToken << endl;
		}
		else { errorMessage(")"); }
	}
	else if (currentToken.type() == "real") {
		cout << "<Primary> -> <Real>" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "true") {
		cout << "<Primary> -> true" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else if (currentToken.lexeme() == "false") {
		cout << "<Primary> -> false" << endl;
		newToken();
		cout << currentToken << endl;
	}
	else { errorMessage("<Identifier>, <Integer>, <Real>, \")\", \"true\", or \"false\""); }
}

void SyntaxAnalyzer::primaryPrime() {
	if (currentToken.lexeme() == "[") {
		cout << "<Primary>' -> [ <IDs> ]" << endl;
		newToken();
		cout << currentToken << endl;

		ids();

		if (currentToken.lexeme() == "]") {
			cout << "<Primary>' -> [ <IDs> ]" << endl;
			newToken();
			cout << currentToken << endl;
		}
		else { errorMessage("]"); }
	}
	else {
		cout << "<Primary> -> <Empty>" << endl;
	}
}

//void SyntaxAnalyzer::fillNonTerminals() {
//	symbols["Rat15F"] = NONTERMINAL;
//	symbols["Opt Function Definitions"] = NONTERMINAL;
//	symbols["Function Definitions"] = NONTERMINAL;
//	symbols["Function"] = NONTERMINAL;
//	symbols["Opt Parameter List"] = NONTERMINAL;
//	symbols["Parameter List"] = NONTERMINAL;
//	symbols["Parameter"] = NONTERMINAL;
//	symbols["Qualifier"] = NONTERMINAL;
//	symbols["Body"] = NONTERMINAL;
//	symbols["Opt Declaration List"] = NONTERMINAL;
//	symbols["Declaration List"] = NONTERMINAL;
//	symbols["Declaration"] = NONTERMINAL;
//	symbols["IDs"] = NONTERMINAL;
//	symbols["Statement List"] = NONTERMINAL;
//	symbols["Statement"] = NONTERMINAL;
//	symbols["Compound"] = NONTERMINAL;
//	symbols["Assign"] = NONTERMINAL;
//	symbols["If"] = NONTERMINAL;
//	symbols["Return"] = NONTERMINAL;
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
//}
//
//void SyntaxAnalyzer::fillTerminals() {
//	symbols["identifier"] = NONTERMINAL;
//	symbols["real"] = NONTERMINAL;
//	symbols["integer"] = NONTERMINAL;
//	symbols["="] = NONTERMINAL;
//	symbols["!="] = NONTERMINAL;
//	symbols["<"] = NONTERMINAL;
//	symbols[">"] = NONTERMINAL;
//	symbols["=>"] = NONTERMINAL;
//	symbols["<="] = NONTERMINAL;
//	symbols["*"] = NONTERMINAL;
//	symbols["-"] = NONTERMINAL;
//	symbols["+"] = NONTERMINAL;
//	symbols["/"] = NONTERMINAL;
//	symbols[":="] = NONTERMINAL;
//	symbols["boolean"] = NONTERMINAL;
//	symbols["real"] = NONTERMINAL;
//	symbols["function"] = NONTERMINAL;
//	symbols["int"] = NONTERMINAL;
//	symbols["if"] = NONTERMINAL;
//	symbols["endif"] = NONTERMINAL;
//	symbols["else"] = NONTERMINAL;
//	symbols["return"] = NONTERMINAL;
//	symbols["write"] = NONTERMINAL;
//	symbols["read"] = NONTERMINAL;
//	symbols["while"] = NONTERMINAL;
//	symbols["do"] = NONTERMINAL;
//	symbols["true"] = NONTERMINAL;
//	symbols["false"] = NONTERMINAL;
//	symbols["@@"] = NONTERMINAL;
//	symbols["["] = NONTERMINAL;
//	symbols["]"] = NONTERMINAL;
//	symbols["("] = NONTERMINAL;
//	symbols[")"] = NONTERMINAL;
//	symbols["{"] = NONTERMINAL;
//	symbols["}"] = NONTERMINAL;
//	symbols[";"] = NONTERMINAL;
//	symbols[","] = NONTERMINAL;
//}