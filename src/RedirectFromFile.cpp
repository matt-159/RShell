#include "../header/RedirectFromFile.hpp"
#include "../header/Parser.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

RedirectFromFile::RedirectFromFile() : Redirect() 
{
	this->path = "";

	this->e = nullptr;

	this->fileExists = false;
}

RedirectFromFile::RedirectFromFile(std::vector<std::string> v) : Redirect()
{
	this->e = Parser::parse(v.at(0));

	this->path = v.at(1);

	this->fileExists = true;
	
	while(this->path[0] == ' ')
	{
		this->path.erase(0, 1);
	}

	struct stat s;
	
	if(stat(this->path.c_str(), &s) == -1)
    {
		this->fileExists = false;
	}

}

RedirectFromFile::~RedirectFromFile()
{
	if(this->e != nullptr)	
	{
		delete e;

		e = nullptr;
	}
}

int RedirectFromFile::execute()
{
	int ret = 0;

	if(this->terminate == false)
	{
		ret = -1;

		if (this->fileExists == false)
		{
			return ret;
		}
		
		int dupout = dup(0); //backup stdin

		int newfile;

		newfile = open(this->path.c_str(), O_RDONLY);

		close(0); // close stdin

		dup(newfile); // make the file the *new stdin*

		ret = e->execute();

		close(0); // close the file

		dup(dupout); //restore stdin
	}
	
	return ret;
}

const std::string RedirectFromFile::to_string() const
{
	std::string ret = "";

	ret += this->e->to_string() + " < " + this->path;

	return ret;
}
