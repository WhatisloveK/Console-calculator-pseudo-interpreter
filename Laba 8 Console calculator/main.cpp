#include"culc.h"
#include <algorithm>
std::string fix(std::string s)
{
	size_t dot = s.find_first_of('.'), last = s.find_last_not_of(".0");

	if (dot != std::string::npos) return s.substr(0, std::max(dot, last + 1));
	else return s;
}
std::string fix(double in) {
	std::string s = std::to_string(in);
	size_t dot = s.find_first_of('.'), last = s.find_last_not_of(".0");

	if (dot != std::string::npos) return s.substr(0, std::max(dot, last + 1));
	else return s;
}
void output(Culc &culc, std::string &input, std::string &correction, bool &prap, bool &variable)
{
	std::vector<double> result;
	//std::cout << std::fixed;
	try
	{
		if (prap == true)
		{
			culc.process(input);
		}
		else
		{
			input = correction + input;
			culc.process(input);
		}
		result = culc.result();
		for (int i = 0, end = result.size(); i < end; i++)
			std::cout << fix(result[i]) << " ";
		std::cout << "\n";
		culc.clearTree();
		prap = true;
		variable = false;
	}
	catch (char c)
	{
		//culc.exterminate();
		if (c == 'u'||c == 't'||c == 'a' || c == '@')
		{
			std::cout <<0<<"\n";
		}
		else
		{
			if (c == '='||c == '[' || c== ']' )
				variable = true;
			/*if (c == ']')
			{
				input.erase(input.size() - 1, 1);
				variable = true;
			}*/

			std::cout << input;
			correction = input;
			prap = false;
		}
		culc.clearTree();
	}
	catch (exep error)
	{
		if (variable||culc.checkStatus()||error.operation=="if" || error.operation == "@")
		{
			std::cout << input;
			correction =input; prap = false;
		}
		else
		{
			std::cout << error.data << error.operation;
			correction = fix(error.data) + error.operation;
		}
		culc.clearTree();
		prap = false;
	}


}

int main()
{
	Culc culc;
	std::string input,correction;
	bool flag = true, prap = true,variable=false;
	std::cout <<"POSSIBLE COMANDS \n";
	std::cout << "If you want to exit: exit\n";
	std::cout << "If you want to save: save\n";
	std::cout << "If you want to check the memory status: check\n";
	std::cout << "Or you can simply calculate smth\n";
	while (flag)
	{

		std::cout << ">";	
		std::getline(std::cin, input);
		std::cin.clear();
		std::cin.sync();

		if (input != "exit")
		{
			if (input == "check")
			{
				culc.checkMem();
			}
			else
			{
				if (input == "save")
				{
					culc.save();
				}
				else
					if (input == "status")
					{
						culc.variableStatus();
					}
					else
						if (input == "delete")
						{
							culc.clearMemory();
						}
						else
						if (input != "")
						{
							output(culc,input,correction,prap,variable);
						}
			}
	    }
		else
			flag = false;
	}
	return 0;
}