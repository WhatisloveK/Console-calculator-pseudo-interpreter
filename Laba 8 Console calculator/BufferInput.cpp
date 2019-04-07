#include"BufferInput.h"
#include <cctype>
#include<string>
void BufferInput::setB(std::string input)
{
	this->input = input;
	position = 0;
	current = input[position];
}

int BufferInput::currentPos()
{
	return position;
}

void BufferInput::avariyneZaversheniaProgramy()
{
	std::cout << "Kovaljungend detected ERROR";
}

char BufferInput::currentChar()
{
	return current;
}

void BufferInput::nextChar()
{
	position++;
	if (position > input.length() - 1)
		current = 'N';
	else
		current = input[position];
}


void BufferInput::skipSpace()
{
	while (current != 'N'&& !isDigit() && !isLetter() && !isOperator())
		nextChar();
}

bool BufferInput::isDigit()
{
	if ((int)current >= 48 && (int)current <= 57)
		return true;
	else
		return false;
}

bool BufferInput::isLetter()
{
	if (((int)current >= 65 && (int)current <= 90) || current=='@' || ((int)current >= 97 && (int)current <= 122))
		return true;
	else
		return false;
}
std::string BufferInput::Id()
{
	std::string result;
	while (current != 'N'&& isalnum(current) || current=='@')
	{
		
		result += current;
		if (current == '@')
		{
			nextChar(); break;
		}
		nextChar();
	}
	return result;
}

std::string BufferInput::multyInteger()
{
	std::string result;
	while ((current != 'N' && isDigit())||(current=='.'))
	{
		result += current;
		nextChar();
	}
	return result;
}

bool BufferInput::isOperator()
{
	if (current != '+' && current != '-' && current != '*' && current != '/' && current != '('
		&& current != ')' && current != '%' && current != '^' && current != '=' && current != '[' && current != '@'
		&& current != ']'&& current!='>'&& current!='<' && current != '&' && current != '$' && current != '!' )
	{
		return false;
	}
	return true;
}

std::string BufferInput::getExpr()
{
	std::string result;
	int i = 1;
	while (input[position + i] != '>'/*&& position + i < input.length() - 1*/)
	{
		result += input[position + i];
		i++;
	}
	input.erase(position, i);

	return result;
}

void BufferInput::normalizeBuffer(int pos,double res)
{
	int result = (int)res % 6;

	if (pos == -1)
	{
		input.erase(position - 2, 1);
		position--;
	}
	else
	{
		pos--;
		input.erase(pos - 1, position - pos);
		position = pos;

		switch (result)//!
		{
		case 0:
		{
			input.insert(pos, "+");
			current = '+';
			break;
		}
		case 1:
		{
			input.insert(pos, "-");
			current = '-';
			break;
		}
		case 2:
		{
			input.insert(pos, "*");
			current = '*';
			break;
		}
		case 3:
		{
			input.insert(pos, "/");
			current = '/';
			break;
		}
		case 4:
		{
			input.insert(pos, "%");
			current = '%';
			break;
		}
		case 5:
		{
			input.insert(pos, "^");
			current = '^';
			break;
		}
		default:
		{
			input.insert(pos, "+");
			current = '+';
			//avariyneZaversheniaProgramy();
			break;
		}
		}
	}
}