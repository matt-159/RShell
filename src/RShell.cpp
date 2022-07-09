#include <unistd.h>
#include <iostream>
#include <string>

#include "../header/Parser.hpp"
#include "../header/Executable.hpp"

bool is_balanced(const std::string&);

int main()
{
	Executable* e = nullptr;

	do
	{	
		if (e != nullptr) { delete e; }
		
		e = nullptr;

		std::string input;
		
		if(isatty(0)) //if this is being run by a user in the terminal
		{
			std::cout << "$ ";
		}

		std::getline(std::cin, input);

		if (std::cin.eof()) 
		{ 
			std::cout << std::endl;
			break; 
		}
		
		if (is_balanced(input))
		{
			Executable* e = Parser::parse(input);

			e->execute();
		}
		else
		{
			std::cout << "Cannot execute an unbalanced input. A small price to pay for salvation." << std::endl;
		}
	}while (e->isTerminated() == false);

	return 0;
}

bool is_balanced(const std::string& input)
{
	int numParens = 0;
	int numBrackets = 0;
	int numCurlies = 0;

	bool ignoringChars = false;

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '"')
		{
			ignoringChars = !ignoringChars;
		}
		
		if (ignoringChars == false)
		{
			if (input[i] == '(')
			{
				numParens++;
			}
			else if (input[i] == ')')
			{
				numParens--;
			}
			else if (input[i] == '[')
			{
				numBrackets++;
			}
			else if (input[i] == ']')
			{
				numBrackets--;
			}
			else if (input[i] == '{')
			{
				numCurlies++;
			}
			else if (input[i] == '}')
			{
				numCurlies--;
			}
		}
	}

	return (ignoringChars == false) && (numParens == 0) && (numBrackets == 0) && (numCurlies == 0);
}
