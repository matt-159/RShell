#include "../header/Connect_Pipe.hpp"
#include "../header/Parser.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

//#include <iostream>

Connect_Pipe::Connect_Pipe() : Connector()
{
	this->lhs = nullptr;

	this->rhs = nullptr;
}

Connect_Pipe::Connect_Pipe(std::vector<std::string> v) : Connector()
{
	this->lhs = Parser::parse(v.at(0));

	this->rhs = Parser::parse(v.at(1));

	//std::cout << "lhs command: " << lhs->to_string() << std::endl;
	//std::cout << "rhs command: " << rhs->to_string() << std::endl;
}

Connect_Pipe::~Connect_Pipe()
{
	if (lhs != nullptr)
	{
		delete lhs;

		lhs = nullptr;
	}

	if (rhs != nullptr)
	{
		delete rhs;

		rhs = nullptr;
	}
}

int Connect_Pipe::execute()
{
	int dupstdin = dup(0);
	int dupstdout = dup(1);
	
	int fds[2];

	pid_t cpid;

	if (pipe(fds) == -1)
	{
		return -1;
	}

	cpid = fork();

	if (cpid == 0) //child process will process the lhs
	{
		//std::cout << "running command: " << lhs->to_string() << std::endl;
		
		close(fds[0]); //close unused read end

		close(1); //close stdout
		dup(fds[1]); 
		
		lhs->execute();

	//	close(1); //close pipe
	//	dup2(dupstdout, 1); //restore stdout
	
		_exit(EXIT_SUCCESS);
	}
	else
	{
		int status;

		waitpid(-1, &status, 0);
		
		close(fds[1]); //close unused write end

		close(0); //close stdin
		
		dup(fds[0]);

		//std::cout << "running command: " << rhs->to_string() << std::endl;
		
		rhs->execute();
		
	//	close(0); //close pipe
	//	dup2(dupstdin, 0);	
	}

	close(0);
	dup2(dupstdin, 0);

	close(1);
	dup2(dupstdout, 1);

	return 0;
}

const std::string Connect_Pipe::to_string() const
{
	return lhs->to_string() + " | " + rhs->to_string();
}
