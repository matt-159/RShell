#include <unistd.h>
#include <sys/wait.h>

#include <ostream>
#include <string>
#include <vector>

#include "../header/Command.hpp"
#include "../header/Parser.hpp"

Command::Command() : Executable(), command("") {}

Command::Command(const std::string& cmd) : Executable(), command(cmd) 
{
	while (this->command[this->command.length() - 1] == ' ')
	{
		this->command.erase(command.length() - 1, 1);
	}
}

Command::~Command() {}

int Command::execute()
{
	if(terminate==false)
	{
		if (this-> command == "exit")
		{
			this->terminate=true;
			
			return 0;
		}		
		else
		{
			std::vector<std::string> commands = Parser::splitOnWS(command);
	
			Parser::consolidateQuotes(commands);
	
			int pid = fork();
	
			if (pid == 0)
			{
				std::vector<const char*> args;
			
				for (std::string s : commands)
				{
					args.push_back(s.c_str());
				}
				
				args.push_back(nullptr);
			
				char* const* argv = const_cast<char* const*>(args.data());
			
				execvp(argv[0], argv);
			}
			else
			{
				int status;
		
				int retVal = waitpid(-1, &status, 0);
				
				return status;
			}
		}
	}
	else
	{
		return 0; 
	}
}

const std::string Command::to_string() const
{
	return this->command;
}
