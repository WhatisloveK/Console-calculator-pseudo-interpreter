#include"culc.h"
#include"consts.h"
int Lexer::position()
{
	return buffer.currentPos();
}
void Lexer::setBuffer(std::string input)
{
	buffer.setB(input);
}

void Lexer::normalizeBuffer(int pos, Father* node)
{
	if (pos == -1)
		buffer.normalizeBuffer(-1, -1);
	else
		if (node == NULL)
			buffer.normalizeBuffer(pos, 0);
		else
	      buffer.normalizeBuffer(pos, node->calculate());

}

Token Lexer::getNextToken()
{
	while (buffer.currentChar() != 'N')
	{
		if (!buffer.isDigit() && !buffer.isOperator() && !buffer.isLetter())
		  buffer.skipSpace();
		else
		{
			if (buffer.isLetter()|| buffer.currentChar() == '@')
			{
				Token token(ID, buffer.Id());
				if (buffer.currentChar() == '@')
					token.value = "@";
				 if (token.value == "if"|| token.value == "else" || token.value == "@")
					 token.type = RESERV;
				 return token;
			}

			if (buffer.isDigit())
				return Token(INTEGER, buffer.multyInteger());
			switch (buffer.currentChar())
			{
			case '+':
			{
				buffer.nextChar();
				return Token(PLUS, "+");
				break;
			}
			case '-':
			{
				buffer.nextChar();
				return Token(MINUS, "-");
				break;
			}
			case '*':
			{
				buffer.nextChar();
				return Token(MULTIPLY, "*");
				break;
			}
			case '/':
			{
				buffer.nextChar();
				return Token(DIVIDE, "/");
				break;
			}
			case '(':
			{
				buffer.nextChar();
				return Token(LRB, "(");
				break;
			}
			case ')':
			{
				buffer.nextChar();
				return Token(RRB, ")");
				break;
			}
			case '[':
			{
				buffer.nextChar();
				return Token(LSB, "[");
				break;
			}
			case ']':
			{
				buffer.nextChar();
				return Token(RSB, "]");
				break;
			}
			case'%':
			{
				buffer.nextChar();
				return Token(ROD, "%");
				break;
			}
			case'=':
			{
				buffer.nextChar();
				if (buffer.currentChar() == '=')
				{
					buffer.nextChar();
					return Token(ASSIGN_ASSIGN, "==");
				}
				return Token(ASSIGN, "=");
			}
			case'^':
			{
				buffer.nextChar();
				return Token(BTD, "^");
			}
			case '<':
			{
				buffer.nextChar();
				if (buffer.currentChar() == '=')
				{
					buffer.nextChar();
					return Token(LTB_ASSIGN, "<=");
			    }
				return Token(LTB, "<");
			}
			case '>':
			{
				buffer.nextChar();
				if (buffer.currentChar() == '=')
				{
					buffer.nextChar();
					return Token(RTB_ASSIGN, ">=");
				}
				return Token(RTB, ">");
			}
			case '!':
			{
				buffer.nextChar();
				if (buffer.currentChar() == '=')
				{
					buffer.nextChar();
					return Token(NOT, "!=");
				}
				break;
			}
			case '&':
			{
				buffer.nextChar();
				return Token(AND, "&");
				break;
			}
			case '$':
			{
				buffer.nextChar();
				return Token(OR, "OR");
				break;
			}
			default:
				
				BufferInput::avariyneZaversheniaProgramy();
				break;
			}
		}
	}
	return Token(EndOfFile, NONE);
}

