#include "treeElements.h"
#include "consts.h"
#include <string>
#include <exception>
#include <cmath>
extern Memory memory;

Token::Token() { type = NONE; value = NONE; }

Token::Token(std::string type, std::string value)
{
	this->type = type;
	this->value = value;
}

double Father::toINT(std::string value)
{
	double digit = 0; bool flag = true;

	for (int i = 0, j = 1, length = value.length() - 1; i <= length; i++)
	{
		if (flag)
		{
			if (value[i] == '.')
				flag = false;
			else
				digit = digit * 10 + value[i] - 48;
		}
		else
		{
			digit = digit + (value[i] - 48) / pow(10, j); j++;
		}
	}
	return digit;
}

Binar::Binar()
{
	rightSon = nullptr;
	leftSon = nullptr;
}
Binar::Binar(Father *left, Token lex, Father *right)
{
	leftSon = left;
	rightSon = right;
	token = lex;
}

double Binar::calculate()
{
	double result = 0,right,left;
	
		if (token.type == ASSIGN && leftSon != NULL)//
		{
			
			if (memory.count(leftSon->token.value) > 0)
			{
				if (!checkRecurtion(leftSon->token))
				{
					result = memory[leftSon->token.value].data = rightSon->calculate();
					memory[leftSon->token.value].tree = rightSon;
					memory[leftSon->token.value].counter = 0;
				}
				else
				{
					if(memory[leftSon->token.value].counter == 0)
					    memory[leftSon->token.value].counter = 1;
			 
					if (!memory[leftSon->token.value].tree->checkVariablePresence())
					{
						memory[leftSon->token.value].data = memory[leftSon->token.value].tree->calculate();
					}
					else
					{
						rightSon->ReplaceRecurVariable(leftSon->token, memory[leftSon->token.value].tree);
					}
					memory[leftSon->token.value].tree = rightSon;
					result = memory[leftSon->token.value].data = rightSon->calculate();
				}
					//memory[leftSon->token.value] = new Atomar(Token(INTEGER, std::to_string((result))));//ATTENTION (int)result
			}
			else
			{
				result = rightSon->calculate();
				if (memory.count(leftSon->token.value) > 0)
				{
				   memory[leftSon->token.value].data = result;
				   memory[leftSon->token.value].tree = rightSon;
			    }
				else
				memory.insert( Memory::value_type(leftSon->token.value, mem(0, result , rightSon)) );
				
			}
		}
		else
			if (token.type == PLUS && leftSon != NULL)
			{
				if (rightSon == NULL)               
				{
					exep e{ leftSon->calculate(),"+" };
					throw e;
				}
				result = leftSon->calculate() + rightSon->calculate();
			}
			else
				if (token.type == BTD && leftSon != NULL)
				{

					if (rightSon == NULL)              
					{
						exep e{ leftSon->calculate(),"^" };
						throw e;
					}

					right = rightSon->calculate(), left = leftSon->calculate();
					
						result = pow(left,right);						
				}
				else
					if (token.type == MINUS)
					{
						if (rightSon == NULL)             
						{
							exep e{ leftSon->calculate(),"-" };
							throw e;
						}
						left = leftSon->calculate();
						right = rightSon->calculate();
						result = (right == INFINITY) && (left == INFINITY) ? INFINITY : left - right;
					}
					else
						if (token.type == MULTIPLY && leftSon != NULL)
						{
							if (rightSon == NULL)              
							{
								exep e{ leftSon->calculate(),"*" };
								throw e;
							}
							result = (leftSon->calculate() * rightSon->calculate());//!!!!!!!!!!!! infinity*0??
						}
						else
							if (token.type == DIVIDE && leftSon != NULL)
							{
								if (rightSon == NULL)               
								{
									exep e{ leftSon->calculate(),"/" };
									throw e;
								}
								if (rightSon->calculate() == INFINITY)
									if (leftSon->calculate() == INFINITY)
										result = INFINITY;
									else
										result = 0;
								else
								result = rightSon->calculate() == 0 ? INFINITY : (leftSon->calculate() / rightSon->calculate());
							}
							else
								if (token.type == ROD && leftSon != NULL)
								{
									if (rightSon == NULL)              
									{
										exep e{ leftSon->calculate(),"%" };
										throw e;
									}
									if (leftSon->calculate() == INFINITY || rightSon->calculate() == 0)
										result = 0;
									else
										result = (leftSon->calculate() > 0 ? (int)leftSon->calculate() : -1 * (int)leftSon->calculate()) % (int)rightSon->calculate();
								}
								else
									if (token.type == LTB && leftSon != NULL)//<
									{
										if (rightSon == NULL)
										{
											exep e{ leftSon->calculate(),"<" };
											throw e;
										}
										result = leftSon->calculate() < rightSon->calculate() ? 1 : 0;
									}
									else
										if (token.type == RTB && leftSon != NULL)//>
										{
											if (rightSon == NULL)
											{
												exep e{ leftSon->calculate(),">" };
												throw e;
											}
											result = leftSon->calculate() > rightSon->calculate() ? 1 : 0;
										}
										else
												if (token.type == LTB_ASSIGN && leftSon != NULL)
												{
													if (rightSon == NULL)
													{
														exep e{ leftSon->calculate(),"<=" };
														throw e;
													}
													result = leftSon->calculate() <= rightSon->calculate() ? 1 : 0;
												}
												else
													if (token.type == RTB_ASSIGN && leftSon != NULL)
													{
														if (rightSon == NULL)
														{
															exep e{ leftSon->calculate(),">=" };
															throw e;
														}
														result = leftSon->calculate() >= rightSon->calculate() ? 1 : 0;
													}
													else
														if (token.type == ASSIGN_ASSIGN && leftSon != NULL)
														{
															if (rightSon == NULL)
															{
																exep e{ leftSon->calculate(),"==" };
																throw e;
															}
															result = leftSon->calculate() == rightSon->calculate() ? 1 : 0;
														}
														else
															if (token.type == NOT && leftSon != NULL)
															{
																if (rightSon == NULL)
																{
																	exep e{ leftSon->calculate(),"!=" };
																	throw e;
																}
																result = leftSon->calculate() != rightSon->calculate() ? 1 : 0;
															}
															else
																if (token.type == AND && leftSon != NULL)
																{
																	if (rightSon == NULL)
																	{
																		exep e{ leftSon->calculate(),"&" };
																		throw e;
																	}
																	result = leftSon->calculate()!=0 && rightSon->calculate()!=0 ? 1 : 0;
																}
																else
																	if (token.type == OR && leftSon != NULL)
																	{
																		if (rightSon == NULL)
																		{
																			exep e{ leftSon->calculate(),"$" };
																			throw e;
																		}
																		result = leftSon->calculate() !=0 || rightSon->calculate()!=0 ? 1 : 0;
																	}
																	else
																		if (token.type == LRB) {
																			result = leftSon->calculate();
																		}

	return result;
}
bool Binar::checkRecurtion(Token Id)
{
	if (token.type == ASSIGN)
		return(rightSon->checkRecurtion(Id));
	else
		return(rightSon->checkRecurtion(Id) + leftSon->checkRecurtion(Id));
}
void Binar::dispose()
{
	bool flag = false;
	if(leftSon!=NULL)
		leftSon->dispose();

	if (rightSon != NULL)
		if (token.type != ASSIGN)
			rightSon->dispose();
		else
			flag = true;

	delete(leftSon);
	if (!flag){
		delete(rightSon);
	}
	rightSon = NULL;
	leftSon = NULL;
}

std::string Binar::expression()
{
	std::string result;
	if(token.type==LRB)
	   result = "( " + leftSon->expression() + " )";
	else
		result = leftSon->expression() +" "+ token.value +" "+ rightSon->expression();
	return result;
}

bool Binar::ReplaceRecurVariable(Token Id, Father * replacement)
{
	if ((token.type == ASSIGN)&&(leftSon->token.value == Id.value))
	{
		if (rightSon->ReplaceRecurVariable(Id, replacement))
		{
			delete rightSon;
			rightSon = replacement;
		}
	}
	else
	{
		if (rightSon->ReplaceRecurVariable(Id, replacement))
		{
			delete rightSon;
			rightSon = replacement;
		}
		if (leftSon->ReplaceRecurVariable(Id, replacement))
		{
			delete leftSon;
			leftSon = replacement;
		}
	}
	return false;
}

bool Binar::checkVariablePresence()
{
	return leftSon->checkVariablePresence() + rightSon->checkVariablePresence();
}

Unar::Unar()
{
	son = nullptr;
}
Unar::Unar(Token token, Father *son)
{
	this->son = son;
	this->token = token;
}
double Unar::calculate()
{
	double result = 0;
	if (son == NULL)
		throw 'u';

	if (token.type == PLUS)
		return son->calculate();
	else
	{
		result = son->calculate();

		return -1 * result== -0 ? 0 : -1 * result;
	}
}
bool Unar::checkRecurtion(Token Id)
{
	return(son->checkRecurtion(Id));
}

void Unar::dispose()
{

	son->dispose();
	delete son;
	son = NULL;
}

std::string Unar::expression()
{
	std::string result;
	if (token.type == MINUS)
		result = "-" + son->expression();
	else
		result = son->expression();
	return result;
}

bool Unar::ReplaceRecurVariable(Token Id, Father * replacement)
{
	if (son->ReplaceRecurVariable(Id, replacement))
	{
		if(son->token.type==INTEGER)
		delete son;
		son = replacement;
	}
	return false;
}

bool Unar::checkVariablePresence()
{
	return son->checkVariablePresence();
}

Atomar::Atomar(Token tok)
{
	token = tok;
}

double Atomar::calculate()
{

	if (token.type == ID)
		if (memory.count(token.value) > 0)
		{	
			if (memory[token.value].tree->token.value == "inf")
			  return INFINITY;

		    if (memory[token.value].counter == 0)
			{   
				if(checkRecurtion(token))
					memory[token.value].counter++;
				memory[token.value].data = memory[token.value].tree->calculate();
				return memory[token.value].data;
			}
			else
			{
				return memory[token.value].data;
			}
        }
		else
		{
			memory.insert(Memory::value_type(token.value, mem( 0,0, new Atomar(Token(INTEGER, "0")) )));
				return 0;
		}
			
    return(toINT(token.value));
}

bool Atomar::checkRecurtion(Token Id)
{
	if(token.value==Id.value)
	  return true;
	return false;
}

std::string Atomar::expression()
{
	return token.value;
}

bool Atomar::ReplaceRecurVariable(Token Id, Father * replacement)
{
	if(token.value == Id.value)
	{
		return true;
	}
	return false;
}

bool Atomar::checkVariablePresence()
{
	return token.type == ID ? true : false;
}

Command::Command(Token token, Father * condition, Father * conditionTrue, Father * conditionFalse)
{
	this->token = token;
	this->condition = condition;
	this->conditionTrue = conditionTrue;
	this->conditionFalse = conditionFalse;
}

Command::Command(Token token, Father * condition, Father * conditionTrue)
{
	this->token = token;
	this->condition = condition;
	this->conditionTrue = conditionTrue;
}

double Command::calculate()
{
	double result=0; int i = 0;
	if (token.value == "if")
	{
		if (condition == NULL || conditionTrue == NULL )
		{
			exep e{ 0,"if" };
			throw e;
		}
		if (condition->calculate() != 0)
			result = conditionTrue->calculate();
		else
			if (conditionFalse != NULL)
				result = conditionFalse->calculate();
			else
				result = 0;
	}
	else
	{
		if (condition == NULL || conditionTrue == NULL)
		{
			exep e{ 0,"@" };
			throw e;
		}

		while (condition->calculate() != 0)
		{
			if (i > 100000)
				throw '@';

			i++;
			result = conditionTrue->calculate();
		}
	}
	return result;
}

void Command::dispose()
{	
	if(conditionTrue)
		conditionTrue->dispose();
	condition->dispose();

	if (conditionFalse != NULL)
	{
		conditionFalse->dispose();
		delete conditionFalse;
		conditionFalse = NULL;
	}
	delete condition;
	delete conditionTrue;
	condition = NULL;
	conditionTrue = NULL;
}

std::string Command::expression()
{
	std::string result;
	 
	result = " if (" + condition->expression() + ')' + " " + conditionTrue->expression();
	if (conditionFalse != NULL)
		result += " else " + conditionFalse->expression();
	return result;
}

bool Command::ReplaceRecurVariable(Token Id, Father * replacement)
{
	return false;
}

bool Command::checkVariablePresence()
{
	return false;
}

bool Command::checkRecurtion(Token Id)//jhgfds
{
	return false;
}


