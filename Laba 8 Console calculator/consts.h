#define INTEGER "INTEGER"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define EndOfFile "EOF"
#define NONE "NONE"
#define MULTIPLY "MULTIPLY"
#define DIVIDE "DIVIDE"
#define LRB "LRB"// (
#define RRB "RRB"//)
#define ROD  "ROD"//remainder of the division %
#define ID "ID"
#define ASSIGN "ASSIGN"
#define BTD "BTD" //bring to a degree
#define RSB "RSB" // ]
#define LSB "LSB" // [
#define RTB "RTB" // >
#define LTB "LTB" // <
#define LTB_ASSIGN "LTB_ASSIGN"
#define RTB_ASSIGN "RTB_ASSIGN"
#define RESERV "RESERV"
#define ASSIGN_ASSIGN "ASSIGN_ASSIGN"
#define AND "AND"
#define OR "OR"
#define NOT "NOT"
class mem
{
public:
	int counter = 0;
	double data;
	Father* tree;

	mem() { counter = 0; }
	mem(int c,double d,Father* s)
	{
		counter = c;
		data = d;
		tree = s;
	}
};
typedef std::map<std::string, mem> Memory;
