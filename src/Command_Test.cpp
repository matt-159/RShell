#include <iostream>
#include <string>
#include <vector>

#include "../header/Command_Test.hpp"
#include "../header/Parser.hpp"

bool Command_Test::*test;

Command_Test::Command_Test() : Executable(), flag("-e"), test(&Command_Test::test_e) {}

Command_Test::Command_Test(const std::string& cmd) : Executable()
{
	std::vector<std::string> v = Parser::splitOnWS(cmd);

	if (v.size() > 1)
	{
		if (	(v.at(1).length() == 2) && 
			(v.at(1).find_first_not_of("-edf") == std::string::npos))
		{
			this->flag = v.at(1);
		}
		else
		{
			this->flag = "-e";
		}

		if (v.size() > 2)
		{
			if (v.at(2).find("]") == std::string::npos)
			{
				this->path = v.at(2);
			}
			else
			{
				if (v.at(0).find("[") != std::string::npos)
				{
					this->path = v.at(1);
				}
				else
				{
					this->path = "";
				}
			}
		}
	}
	else
	{
		this->flag = "-e";

		this->path = "";
	}

	switch(this->flag[1])
	{
		case 'e': 	
			this->test = &Command_Test::test_e; 
			break;
		case 'f': 
			this->test = &Command_Test::test_f; 
			break;
		case 'd':
			this->test = &Command_Test::test_d;
			break;
	}
}

Command_Test::~Command_Test() {}

bool Command_Test::test_e()
{
	return !this->path.empty() && stat(path.c_str(), &this->sb) != -1;
}

bool Command_Test::test_f()
{
	if (this->test_e())
	{
		return S_ISREG(this->sb.st_mode & S_IFMT) != 0;
	}
	else
	{
		return false;
	}
}

bool Command_Test::test_d()
{
	if (this->test_e())
	{
		return S_ISDIR(this->sb.st_mode & S_IFMT) != 0;
	}
	else
	{
		return false;
	}
}

int Command_Test::execute()
{
	if(terminate==false)
	{
		bool ret = (this->*test)();

		std::cout << '(' << (ret ? "True" : "False") << ')' << std::endl;

		return ret ? 0 : 1;
	}
	else
	{
		return 0; 
	}
}

const std::string Command_Test::to_string() const
{
	return "test " + this->flag + " " + this->path;
}
