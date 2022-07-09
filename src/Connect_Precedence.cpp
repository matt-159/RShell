#include "../header/Connect_Precedence.hpp"
#include <iostream>

Connect_Precedence::Connect_Precedence() : Connector() {}

Connect_Precedence::Connect_Precedence(const std::string& command) : Connector()
{
	lhs = Parser::parse(command.substr(1, command.length() - 2));

	rhs = nullptr;
}

Connect_Precedence::~Connect_Precedence() 
{
	delete lhs;

	lhs = nullptr;
}

int Connect_Precedence::execute()
{	
	if(terminate==false)
	{
		return lhs->execute();
	}
	else
	{
		return 0;
	}
}

const std::string Connect_Precedence::to_string() const
{
	return "(" + lhs->to_string() + ")";
}

