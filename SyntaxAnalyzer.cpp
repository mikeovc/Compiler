////////////////////SyntaxAnalyzer.cpp

#include "SyntaxAnalyzer.h"

const int TERMINAL = 0, NONTERMINAL = 1, NEW_PRODUCTION = 2;

SyntaxAnalyzer::SyntaxAnalyzer(list<Token> t) {
	tokens = t;
	currentToken = tokens.front();
}

void SyntaxAnalyzer::analyze() {
	rat15F();
}

void SyntaxAnalyzer::newToken() {
	cout << endl;
	tokens.pop_front();
	currentToken = tokens.front();
	cout << currentToken << endl;
}

void SyntaxAnalyzer::errorMessage(const string& expected) {
	cout << "Error after token \"" << currentToken.lexeme() 
		<< "\". First of \"" << expected << "\" expected." << endl;
	system("pause");
}

void SyntaxAnalyzer::addToTable(const string& id, const string& type) {
	if (table.has(id)) {
		cout << "Error: Identifier " << id << " already declared." << endl;
		system("pause");
	}
	else {
		table.add(id, type);
		cout << table;
	}
}

void SyntaxAnalyzer::rat15F() {
	cout << endl << currentToken << endl;

	cout << "<Rat15F> -> <Opt Function Definitions> \n\t\t@@ <Opt Declaration List> \n"
		<< "\t\t@@ <Statement List>" << endl;
	optFunDefs();

	if (currentToken.lexeme() == "@@") {
		cout << "<Rat15F> -> <Opt Function Definitions> \n\t\t@@ <Opt Declaration List> \n"
			<< "\t\t@@ <Statement List>" << endl;
		newToken();
	}
	else {
		errorMessage("@@");
		return;
	}

	optDeclList();

	if (currentToken.lexeme() == "@@") {
		cout << "<Rat15F> -> <Opt Function Definitions> \n\t\t@@ <Opt Declaration List> \n"
			<< "\t\t@@ <Statement List>" << endl;
		newToken();
	}
	else {
		errorMessage("@@");
		return;
	}

	statementList();

	if (currentToken.type() == "eof") {
		cout << "\n\nCompleted. Syntax correct!" << endl;
	}
	else {
		cout << "Error. No more tokens were expected." << endl;
	}
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
			<< "\t\t<Opt Declaration List>" "<Body>" << endl;
		newToken();
	}
	else { errorMessage("function"); }

	if (currentToken.type() == "identifier") {
		cout << "<Function> -> function <Identifier> [ <Opt Parameter List> ]\n"
			<< "\t<Opt Declaration List>" "<Body>" << endl;
		addToTable(currentToken.lexeme(), "function");
		newToken();
	}
	else { errorMessage("<Identifier>"); }

	if (currentToken.lexeme() == "[") {
		cout << "<Function> -> function <Identifier> [ <Opt Parameter List> ]\n"
			<< "\t<Opt Declaration List>" "<Body>" << endl;
		newToken();
	}
	else { errorMessage("["); }

	optParamList();

	if (currentToken.lexeme() == "]") {
		cout << "<Function> -> function <Identifier> [ <Opt Parameter List> ]\n"
			<< "\t<Opt Declaration List>" "<Body>" << endl;
		newToken();
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
	if (currentToken.lexeme() == ",") {
		cout << "<Parameter List>' -> , <Paramter List>" << endl;
		newToken();
		if (currentToken.type() == "identifier") {
			cout << "<Parameter List>' -> , <Parameter List>" << endl;
			paramList();
		}
		else { errorMessage("<Identifier>"); }
	}
	else {
		cout << "<Parameter List>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::param() {
	cout << "<Parameter> -> <IDs> <Qualifier>" << endl;
	string id = currentToken.lexeme();
	ids();
	addToTable(id, currentToken.lexeme()); // currentToken is a qualifier (int bool or real)
	qualifier();
}

void SyntaxAnalyzer::qualifier() {
	if (currentToken.lexeme() == "int" || currentToken.lexeme() == "boolean"
		|| currentToken.lexeme() == "real") {
		cout << "<Qualifier> -> " << currentToken.lexeme() << endl;
		newToken();
	}
	else { errorMessage("int\", \"boolean\", or \"real"); }
}

void SyntaxAnalyzer::body() {
	if (currentToken.lexeme() == "{") {
		cout << "<Body> -> { <Statment List> }" << endl;
		newToken();
	}
	else { errorMessage("{"); }
	
	statementList();

	if (currentToken.lexeme() == "}") {
		cout << "<Body> -> { <Statment List> }" << endl;
		newToken();
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
	cout << "<Declaration List> -> <Declaration> ; <Declaration List>'" << endl;
	decl();

	if (currentToken.lexeme() == ";") {
		cout << "<Declaration List> -> <Declaration> ; <Declaration List>'" << endl;
		newToken();
	}
	else { errorMessage(";"); }
	
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
	}
	else { errorMessage("<Identifier>"); }

	idsPrime();
}

void SyntaxAnalyzer::idsPrime() {
	if (currentToken.lexeme() == ",") {
		cout << "<IDs>' -> , <IDs>" << endl;
		newToken();

		if (currentToken.type() == "identifier") {
			cout << "<IDs>' -> , <IDs>" << endl;
			ids();
		}
		else { errorMessage("<Identifier>"); }
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
	}
	else { errorMessage("{"); }

	statementList();

	if (currentToken.lexeme() == "}") {
		cout << "<Compound> -> { <Statement List> }" << endl;
		newToken();
	}
	else { errorMessage("}"); }
}

void SyntaxAnalyzer::assign() {
	if (currentToken.type() == "identifier") {
		cout << "<Assign> -> <Identifier> := <Expression> ;" << endl;
		newToken();
	}
	else { errorMessage("<Identifier>"); }

	if (currentToken.lexeme() == ":=") {
		newToken();
	}
	else { errorMessage(":="); }

	expression();

	if (currentToken.lexeme() == ";") {
		cout << "<Assign> -> <Identifier> := <Expression> ;" << endl;
		newToken();
	}
	else { errorMessage(";"); }
}

void SyntaxAnalyzer::ifProcedure() {
	if (currentToken.lexeme() == "if") {
		cout << "<If> -> if ( <Condition> ) <Statement> <If>'" << endl;
		newToken();
	}
	else { errorMessage("if"); }

	if (currentToken.lexeme() == "(") {
		newToken();
	}
	else { errorMessage("("); }

	condition();

	if (currentToken.lexeme() == ")") {
		cout << "<If> -> if ( <Condition> ) <Statement> <If>'" << endl;
		newToken();
	}
	
	statement();

	ifProcPrime();
}

void SyntaxAnalyzer::ifProcPrime() {
	if (currentToken.lexeme() == "endif") {
		cout << "<If>' -> endif" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == "else") {
		cout << "<If>' -> else <Statement> endif" << endl;
		newToken();

		statement();

		if (currentToken.lexeme() == "endif") {
			cout << "<If>' -> else <Statement> endif" << endl;
			newToken();	
		}
		else { errorMessage("endif"); }
	}
	else { errorMessage("endif\" or \"else"); }
}

void SyntaxAnalyzer::returnProcedure() {
	if (currentToken.lexeme() == "return") {
		cout << "<Return> -> return <Return>'" << endl;
		newToken();

		returnProcPrime();
	}
	else { errorMessage("return"); }
}

void SyntaxAnalyzer::returnProcPrime() {
	if (currentToken.lexeme() == "-" || currentToken.type() == "identifier"
		|| currentToken.type() == "integer" || currentToken.lexeme() == "("
		|| currentToken.type() == "real" || currentToken.lexeme() == "true"
		|| currentToken.type() == "false") {

		cout << "<Return>' -> <Expression> ;" << endl;
		expression();

		if (currentToken.lexeme() == ";") {
			cout << "<Return> -> <Expression> ;" << endl;
			newToken();
		}
		else { errorMessage(";"); }
	}
	else if (currentToken.lexeme() == ";") {
		cout << "<Return> -> ;" << endl;
		newToken();
	}
	else { errorMessage(";"); }
}

void SyntaxAnalyzer::write() {
	if (currentToken.lexeme() == "write") {
		cout << "<Write> -> write ( <Expression> ) ;" << endl;
		newToken();
	}
	else { errorMessage("write"); }

	if (currentToken.lexeme() == "(") {
		newToken();
	}

	expression();

	if (currentToken.lexeme() == ")") {
		cout << "<Write> -> write ( <Expression> );" << endl;
		newToken();
	}
	else { errorMessage(")"); }

	if (currentToken.lexeme() == ";") {
		newToken();
	}
	else { errorMessage(";"); }
}

void SyntaxAnalyzer::read() {
	if (currentToken.lexeme() == "read") {
		cout << "<Read> -> read ( <IDs> ) ;" << endl;
		newToken();
	}
	else { errorMessage("read"); }

	if (currentToken.lexeme() == "(") {
		newToken();
	}
	else { errorMessage("("); }

	ids();

	if (currentToken.lexeme() == ")") {
		cout << "<Read> -> read ( <IDs> );" << endl;
		newToken();
	}
	else { errorMessage(")"); }

	if (currentToken.lexeme() == ";") {
		newToken();
	}
	else { errorMessage(";"); }
}

void SyntaxAnalyzer::whileProcedure() {
	if (currentToken.lexeme() == "while") {
		cout << "<While> -> while ( <Condition> ) do <Statement>" << endl;
		newToken();
	}
	else { errorMessage("while"); }

	if (currentToken.lexeme() == "(") {
		newToken();
	}
	else { errorMessage("("); }

	condition();

	if (currentToken.lexeme() == ")") {
		newToken();
	}
	else { errorMessage(")"); }

	if (currentToken.lexeme() == "do") {
		newToken();
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
	}
	else if (currentToken.lexeme() == "!=") {
		cout << "<Relop> -> !=" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == ">") {
		cout << "<Relop> -> >" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == "<") {
		cout << "<Relop> -> <" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == "=>") {
		cout << "<Relop> -> =>" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == "<=") {
		cout << "<Relop> -> <=" << endl;
		newToken();
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

		term();
		expressionPrime();
	}
	else if (currentToken.lexeme() == "-") {
		cout << "<Expression>' -> - <Term> <Expression>'" << endl;
		newToken();

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

		factor();
		termPrime();
	}
	else if (currentToken.lexeme() == "/") {
		cout << "<Term>' -> / <Factor> <Term>'" << endl;
		newToken();

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

		primary();
	}
	else {
		cout << "<Factor> -> <Primary>" << endl;
		primary();
	}
}

void SyntaxAnalyzer::primary() {
	if (currentToken.type() == "identifier") {
		cout << "<Primary> -> <Identifier> <Primary>'" << endl;
		newToken();

		primaryPrime();
	}
	else if (currentToken.type() == "integer") {
		cout << "<Primary> -> <Integer>" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == "(") {
		cout << "<Primary> -> ( <Expression> )" << endl;
		newToken();

		expression();

		if (currentToken.lexeme() == ")") {
			cout << "<Primary> -> ( <Expression> )" << endl;
			newToken();
		}
		else { errorMessage(")"); }
	}
	else if (currentToken.type() == "real") {
		cout << "<Primary> -> <Real>" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == "true") {
		cout << "<Primary> -> true" << endl;
		newToken();
	}
	else if (currentToken.lexeme() == "false") {
		cout << "<Primary> -> false" << endl;
		newToken();
	}
	else { errorMessage("<Identifier>, <Integer>, <Real>, \")\", \"true\", or \"false\""); }
}

void SyntaxAnalyzer::primaryPrime() {
	if (currentToken.lexeme() == "[") {
		cout << "<Primary>' -> [ <IDs> ]" << endl;
		newToken();

		ids();

		if (currentToken.lexeme() == "]") {
			cout << "<Primary>' -> [ <IDs> ]" << endl;
			newToken();	
		}
		else { errorMessage("]"); }
	}
	else {
		cout << "<Primary>' -> <Empty>" << endl;
	}
}