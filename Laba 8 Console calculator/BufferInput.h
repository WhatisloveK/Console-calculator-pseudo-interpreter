#include<iostream>
class BufferInput {

	std::string input;
	char current;
	int position;
public:

	void setB(std::string input);
	int currentPos();
	char currentChar();
	bool isLetter();
	bool isDigit();
	std::string Id();
	void skipSpace();
	void nextChar();
	bool isOperator();
	void normalizeBuffer(int,double);
	std::string getExpr();
	std::string multyInteger();
	static void avariyneZaversheniaProgramy();
};
