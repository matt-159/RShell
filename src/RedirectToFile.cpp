#include "../header/RedirectToFile.hpp"
#include "../header/Parser.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

//#include <iostream>

RedirectToFile::RedirectToFile() : Redirect(), mode(none) 
{ 
	this->path = "";

	this->e = nullptr; 
} 

RedirectToFile::RedirectToFile(std::vector<std::string> v, Mode m) : Redirect(), mode(m)
{
	this->e = Parser::parse(v.at(0));

	this->path = v.at(1);

	while(this->path[0] == ' ')
	{
		this->path.erase(0, 1);
	}

	//std::cout << "Path: " << this->path << std::endl;

	//std::cout << "Command: " << this->e->to_string() << std::endl;

	std::string temp = "test -e " + path;

	struct stat s;

	if (stat(this->path.c_str(), &s) == -1)
	{
		temp = "touch " + path;

		Parser::parse(temp)->execute();
	}
}

RedirectToFile::~RedirectToFile()
{
	if (this->e != nullptr)
	{
		delete e;
		
		e = nullptr;
	}
}

int RedirectToFile::execute()
{
	int ret = 0;
	
	if (this->terminate == false)
	{
		ret = -1;
		
		if (this->mode != none)
		{
			int dupout = dup(1); //backup stdout

			int newfile;
	
			if (this->mode == trunc)
			{
				newfile = open(this->path.c_str(), O_WRONLY | O_TRUNC);
			}
			else
			{
				newfile = open(this->path.c_str(), O_WRONLY | O_APPEND);
			}

			close(1); //close stdout

			dup(newfile); //make the file the *new stdout*

			ret = e->execute();
	
			close(1); //close the file

			dup(dupout); //restore stdout
		}
	}

	return ret;
}


const std::string RedirectToFile::to_string() const
{
	std::string ret = "";
	
	if (this->mode != none)
	{
		ret += this->e->to_string() + " >";

		if (this->mode == append)
		{
			ret += ">";
		}

		ret += " " + this->path;
	}
	
	return ret;
}
