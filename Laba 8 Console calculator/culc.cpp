#include"culc.h"
#include"consts.h"
#include<fstream>

std::ofstream out("MemoryStatus.txt");
Memory memory;

bool Culc::checkStatus()
{
	return status;
}


std::vector<double> Culc::result()
{
	std::vector<double> result;

	result.push_back(res);

	while (currentToken.type != EndOfFile&&currentToken.type!=ASSIGN)
	{
		clearTree();
		result.push_back(eval(parse()));
	}
	return result;
}

void Culc::process(std::string input)
{
	status = false;
	globalTree = NULL;
	lexer.setBuffer(input);
	initMem();
	currentToken = lexer.getNextToken();
	res = eval(parse());
}

void Culc::initMem()
{
	for (auto iter = memory.begin(); iter != memory.end(); iter++)
	{
		iter->second.counter = 0;
	}
}

Father* Culc::parse()
{
	return phaser();
}


void Culc::eat(std::string tokenType)
{
	if (currentToken.type == tokenType)
		currentToken = lexer.getNextToken();
	else
		
		throw tokenType[0];
}

int Culc::toINT(std::string value)
{
	int digit = 0;
	for (int i = 0; i <= value.length() - 1; i++)
	{
		digit = digit * 10 + value[i] - 48;
	}
	return digit;
}

Father* Culc::factor()
{
	bool prap = false;
	Token token;
	Father *tree=NULL, *condT=NULL, *condF=NULL, *p=NULL;
	int pos;
	tree = NULL;
	token = currentToken;
	if (token.type == PLUS)
	{
		eat(PLUS);
		tree = new Unar(token, factor());
	}
	else
		if (token.type == MINUS)
		{
			eat(MINUS);
			tree = new Unar(token, factor());
		}
		else
			if (token.type == INTEGER)
			{
				eat(INTEGER);
				tree = new Atomar(token);
				
			}
			else
				if (token.type == LRB)//(
				{
					eat(LRB);
					if (currentToken.type == EndOfFile)
						throw '(';
					else
						if (currentToken.type == ASSIGN)
							throw 'a';
					tree = new Binar(phaser(), token, new Atomar(Token(RRB, ")")));
					
					eat(RRB);
				}
				else
					if (token.type == RRB)//)
					{
						eat(RRB);
						tree = phaser();
						if (tree==NULL)
						tree = new Atomar(Token(INTEGER, "0"));
					}
					else
							if (token.type == ID)//token.type == ID
							{

								tree = new Atomar(token);
								eat(ID);

								if (currentToken.type == ASSIGN)//add exception trow and  catch in main for a= , ( smth like that
								{
									eat(ASSIGN);
									if (currentToken.type == EndOfFile)
										throw '=';
									tree = new Binar(tree, Token(ASSIGN, "="), phaser());
									
								}
							}
							else
								if (currentToken.type == RESERV)
								{
									token = currentToken;
									if (token.value == "@")
									{
										eat(RESERV);
										tree = phaser();
										condT = phaser();
										tree = new Command(token, tree, condT);
									}
									if (token.value == "if")
									{
										eat(RESERV);
										tree = phaser();
										condT = phaser();
										if (currentToken.value == "else")
										{
											eat(RESERV);
											condF = phaser();
											if (condF == NULL)
												throw 'e';
										}
										tree = new Command(token, tree, condT, condF);
									}
									
								}
							/*	else
									if (currentToken.type == RSB)
									{
										throw ']';
									}*/
	if (currentToken.type == LSB)//[
	{
		if (status)
			prap = true;
		else
			status = true;
		eat(LSB);
		pos = lexer.position();
		p = phaser();
		lexer.normalizeBuffer(pos, p);
		if (!prap)
			status = false;
		eat(RSB);
		lexer.normalizeBuffer(-1, NULL);
		
		/*if (currentToken.type == EndOfFile)
			throw ']';*/
	}


	return tree;
}
Father* Culc::btd()
{
	Father* tree;
	Token token;
	tree = factor();
	while (currentToken.type == BTD)
	{
		token = currentToken;
		eat(BTD); 
		tree = new Binar(tree, token, btd());
		//globalTree = tree;
	}
	return tree;
}
Father* Culc::term()
{
	Father* tree;
	Token token;

	tree = btd();
	while (currentToken.type == MULTIPLY || currentToken.type == DIVIDE || currentToken.type == ROD)
	{
		token = currentToken;
		eat(token.type);
		tree = new Binar(tree, token, btd());
	//	globalTree = tree;
	}
	return tree;
}

Father * Culc::constituent()
{
	Father* tree;
	Token token;

	tree = term();
	while (currentToken.type == PLUS || currentToken.type == MINUS)
	{
		token = currentToken;
		eat(token.type);
		tree = new Binar(tree, token, term());
		//	globalTree = tree;
	}
	return tree;
}

Father* Culc::phaser() {
	Father* tree;
	Token token;

	tree = constituent();
	while (currentToken.type == RTB || currentToken.type == LTB || currentToken.type == RTB_ASSIGN || 
		   currentToken.type == LTB_ASSIGN || currentToken.type == ASSIGN_ASSIGN  ||
		   currentToken.type == OR || currentToken.type == AND || currentToken.type == NOT )
	{
		token = currentToken;
		eat(token.type);
		tree = new Binar(tree, token, constituent());
		
	}
	globalTree = tree;
	return tree;
}


void Culc::checkMem()
{
	std::cout << "Memory status \n";
	for (auto iter = memory.begin(); iter != memory.end(); iter++)
	{
		std::cout << iter->first << " = " << iter->second.data<<"\n";
	}
}

void Culc::save()
{
	out << memory.size() << "\n";
	for (auto iter = memory.begin(); iter != memory.end(); iter++)
	{
		out << iter->first << " " << iter->second.tree->calculate() << "\n";
	}
}

void Culc::clearTree()
{
	if (globalTree != NULL)
		globalTree->dispose();
	delete globalTree;
	globalTree = NULL;
}

void Culc::clearMemory()
{
	for (auto iter = memory.begin(); iter != memory.end(); iter++)
	{
		iter->second.tree->dispose();
		delete iter->second.tree;
		iter->second.tree = NULL;
	}
	memory.erase(memory.begin(), memory.end());
}

double Culc::eval(Father *tree)
{ 
	if (tree == NULL)
		throw  't';
	this->globalTree = tree;
	return(tree->calculate());
}

void Culc::variableStatus()
{
	std::cout << "Memory Varible Expression Status \n";
	for (auto iter = memory.begin(); iter != memory.end(); iter++)
	{
		std::cout << iter->first << " = " << iter->second.tree->expression() << "\n";
	}
}

