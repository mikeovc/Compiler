////////////////////SyntaxAnalyzer.cpp

#include "SyntaxAnalyzer.h"

const int TERMINAL = 0, NONTERMINAL = 1, NEW_PRODUCTION = 2;

SyntaxAnalyzer::SyntaxAnalyzer(list<Token> t) {
	tokens = t;
	currentToken = tokens.front();
}

void SyntaxAnalyzer::analyze() {
	rat15F();
	cout << endl;
	cout << "-----SYMBOL TABLE-----" << endl;
	cout << table << endl;
	cout << "---INSTRUCTION TABLE---" << endl;
	cout << instTable << endl;
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
	exit(EXIT_FAILURE);
}

void SyntaxAnalyzer::addToTable(const string& id, const string& type) {
	if (table.has(id)) {
		cout << "Error: Identifier " << id << " already declared." << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	else {
		table.add(id, type);
	}
}

void SyntaxAnalyzer::checkIdExistence(const string& id) {
	if (!table.has(id)) {
		cout << "Identifier " << id << " undefined." << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void SyntaxAnalyzer::rat15F() {
	cout << endl << currentToken << endl;

	if (currentToken.lexeme() == "@@") {
		cout << "<Rat15F> -> @@ <Opt Declaration List> @@ <Statement List>" << endl;
		newToken();
	}
	else {
		errorMessage("@@");
		return;
	}

	optDeclList();

	if (currentToken.lexeme() == "@@") {
		cout << "<Rat15F> -> @@ <Opt Declaration List> @@ <Statement List>" << endl;
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

void SyntaxAnalyzer::qualifier() {
	if (currentToken.lexeme() == "int" || currentToken.lexeme() == "boolean") {
		cout << "<Qualifier> -> " << currentToken.lexeme() << endl;
		newToken();
	}
	else { errorMessage("int\" or \"boolean\""); }
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
	if (currentToken.lexeme() == "int" || currentToken.lexeme() == "boolean") {
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
	if (currentToken.lexeme() == "int" || currentToken.lexeme() == "boolean") {
		cout << "<Declaration List>' -> <Declaration List>" << endl;
		declList();
	}
	else {
		cout << "Declaration List>' -> <Empty>" << endl;
	}
}

void SyntaxAnalyzer::decl() {
	cout << "<Declaration> -> <Qualifier> <IDs>" << endl;
	string type = currentToken.lexeme();
	qualifier();
	ids(type);
}

void SyntaxAnalyzer::ids(const string& type, bool fromRead) {
	if (currentToken.type() == "identifier") {
		cout << "<IDs> -> <Identifier> <IDs>'" << endl;
		if (type != "") {
			addToTable(currentToken.lexeme(), type);
		}
		if (fromRead) {
			checkIdExistence(currentToken.lexeme());
			instTable.genInstr("STDIN", NIL);
			int addr = table.getAddress(currentToken.lexeme());
			instTable.genInstr("POPM", addr);
		}
		newToken();
	}
	else { errorMessage("<Identifier>"); }

	idsPrime(type);
}

void SyntaxAnalyzer::idsPrime(const string& type, bool fromRead) {
	if (currentToken.lexeme() == ",") {
		cout << "<IDs>' -> , <IDs>" << endl;
		newToken();

		if (currentToken.type() == "identifier") {
			cout << "<IDs>' -> , <IDs>" << endl;
			ids(type, fromRead);
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

		checkIdExistence(currentToken.lexeme());
		string save = currentToken.lexeme();
		newToken();

		if (currentToken.lexeme() == ":=") {
			newToken();
			expression();
			int address = table.getAddress(save);
			instTable.genInstr("POPM", address);
		}
		else { errorMessage(":="); }
	}
	else { errorMessage("<Identifier>"); }

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
	else { errorMessage(")"); }
	
	statement();

	int address = instTable.instrAddress();
	instTable.genInstr("JUMP", NIL);
	instTable.backPatch();
	instTable.genInstr("LABEL", NIL);
	instTable.pushJumpStack(address);

	ifProcPrime();

	instTable.backPatch();
	instTable.genInstr("LABEL", NIL);
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
	instTable.genInstr("STDOUT", NIL);

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

	ids("", true);

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
	int address = NIL;
	if (currentToken.lexeme() == "while") {
		cout << "<While> -> while ( <Condition> ) do <Statement>" << endl;
		address = instTable.instrAddress();
		instTable.genInstr("LABEL", NIL);
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
	instTable.genInstr("JUMP", address);
	instTable.backPatch();
}

void SyntaxAnalyzer::condition() {
	cout << "<Condition> -> <Expression> <Relop> <Expression>" << endl;
	expression();
	string op = currentToken.lexeme();
	relop();
	expression();
	if (op == "<") {
		instTable.genInstr("LES", NIL);
		instTable.pushJumpStack();
		instTable.genInstr("JUMPZ", NIL);
	}
	else if (op == ">") {
		instTable.genInstr("GRT", NIL);
		instTable.pushJumpStack();
		instTable.genInstr("JUMPZ", NIL);
	}
	else if (op == "<=") {
		instTable.genInstr("LET", NIL);
		instTable.pushJumpStack();
		instTable.genInstr("JUMPZ", NIL);
	}
	else if (op == "=>") {
		instTable.genInstr("GET", NIL);
		instTable.pushJumpStack();
		instTable.genInstr("JUMPZ", NIL);
	}
	else if (op == "=") {
		instTable.genInstr("EQU", NIL);
		instTable.pushJumpStack();
		instTable.genInstr("JUMPZ", NIL);
	}
	else { // op == "!="
		instTable.genInstr("EQU", NIL);
		instTable.genInstr("PUSHI", -1);
		instTable.genInstr("MUL", NIL);
		instTable.pushJumpStack();
		instTable.genInstr("JUMPZ", NIL);
	}
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
		instTable.genInstr("ADD", NIL);
		expressionPrime();
	}
	else if (currentToken.lexeme() == "-") {
		cout << "<Expression>' -> - <Term> <Expression>'" << endl;
		newToken();

		term();
		instTable.genInstr("SUB", NIL);
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
		instTable.genInstr("MUL", NIL);
		termPrime();
	}
	else if (currentToken.lexeme() == "/") {
		cout << "<Term>' -> / <Factor> <Term>'" << endl;
		newToken();

		factor();
		instTable.genInstr("DIV", NIL);
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
		primary(true);
	}
	else {
		cout << "<Factor> -> <Primary>" << endl;
		primary();
	}
}

void SyntaxAnalyzer::primary(bool isNegative) {
	if (currentToken.type() == "identifier") {
		cout << "<Primary> -> <Identifier> <Primary>'" << endl;
		checkIdExistence(currentToken.lexeme());
		int address = table.getAddress(currentToken.lexeme());
		if (isNegative) {
			instTable.genInstr("PUSHI", 0);
			instTable.genInstr("PUSHM", address);
			instTable.genInstr("SUB", NIL);
		}
		else {
			instTable.genInstr("PUSHM", address);
		}
		newToken();

		primaryPrime();
	}
	else if (currentToken.type() == "integer") {
		cout << "<Primary> -> <Integer>" << endl;
		int address = table.getAddress(currentToken.lexeme());
		if (isNegative) {
			instTable.genInstr("PUSHI", -std::stoi(currentToken.lexeme()));
		}
		else {
			instTable.genInstr("PUSHI", std::stoi(currentToken.lexeme()));
		}
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
	else if (currentToken.lexeme() == "true") {
		cout << "<Primary> -> true" << endl;
		instTable.genInstr("PUSHI", 1);
		newToken();
	}
	else if (currentToken.lexeme() == "false") {
		cout << "<Primary> -> false" << endl;
		instTable.genInstr("PUSHI", 0);
		newToken();
	}
	else { errorMessage("<Identifier>, <Integer>, \")\", \"true\", or \"false\""); }
}

void SyntaxAnalyzer::primaryPrime() {
	if (currentToken.lexeme() == "[") {
		cout << "<Primary>' -> [ <IDs> ]" << endl;
		newToken();
		checkIdExistence(currentToken.lexeme());
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