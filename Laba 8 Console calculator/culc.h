#include"BufferInput.h"
#include"treeElements.h"
#include<vector>
class Lexer {

	BufferInput buffer;
public:
	int position();
	void setBuffer(std::string input);
	void normalizeBuffer(int pos,Father* node);
	Token getNextToken();
};
 
class Culc {

	Token currentToken;
	Lexer lexer;
	bool status;
	Father* globalTree;


	void eat(std::string tokenType);
	int toINT(std::string value);
	
	Father* factor();
	Father* btd();
	Father* term();
	Father* constituent();
	Father* phaser();
//	Father* commands();
	void initMem();
	double eval(Father *tree);
	Father* parse();
	double res;
public:
	
	bool checkStatus();
	void variableStatus();
	std::vector<double> result();
	void process(std::string input);
	void checkMem();
	void save();
	void clearTree();
	void clearMemory();

};

