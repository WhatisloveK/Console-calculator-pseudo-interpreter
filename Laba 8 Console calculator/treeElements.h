#include<iostream>
#include<string>
#include<map>

/*class Memory
{
typedef std::map<std::string, Father*> MEMORY;
MEMORY memory;


};*/

struct exep {
	double data;
	std::string operation;
};

class Token {
public:
	std::string type, value;
	Token();
	Token(std::string type, std::string value);
};

class Father
{
public:
	Token token;
	double toINT(std::string value);
	double virtual calculate() = 0;
	bool virtual checkRecurtion(Token Id) = 0;
	void virtual dispose() = 0;
	std::string virtual expression() = 0;
	bool virtual ReplaceRecurVariable(Token Id, Father *replacement) = 0;
	bool virtual checkVariablePresence() = 0;
};

class Binar :public Father
{
	Father * rightSon, *leftSon;
public:
	Binar();
	Binar(Father *left, Token lex, Father *right);
	double calculate();
	bool checkRecurtion(Token Id);
	void dispose();
	std::string expression();
	bool ReplaceRecurVariable(Token Id,Father *replacement);
	bool  checkVariablePresence();
};

class Atomar :public Father
{
public:
	int counter;
	double calculate();
	Atomar(Token token);
	bool checkRecurtion(Token Id);
	void dispose() { };
	std::string expression();
	bool ReplaceRecurVariable(Token Id, Father *replacement);
	bool  checkVariablePresence();
};

class Unar :public Father
{
	Father *son;
public:
	Unar();
	Unar(Token token, Father *son);
	double calculate();
	bool checkRecurtion(Token Id);
	void dispose();
	std::string expression();
	bool ReplaceRecurVariable(Token Id, Father *replacement);
	bool  checkVariablePresence();
};

class Command :public Father
{
	Father *condition, *conditionTrue, *conditionFalse;
public:
	Command(Token token, Father *condition, Father *conditionTrue, Father *conditionFalse);
	Command(Token token, Father *condition, Father *conditionTrue);
	double calculate();
	bool checkRecurtion(Token ID);
	void dispose();
	std::string expression();
	bool ReplaceRecurVariable(Token Id, Father *replacement);
	bool  checkVariablePresence();
};
