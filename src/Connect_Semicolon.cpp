#include "../header/Connect_Semicolon.hpp"

Connect_Semicolon::Connect_Semicolon() : Connector() {}

Connect_Semicolon::Connect_Semicolon(std::vector<std::string>v) : Connector()
{
	lhs = Parser::parse(v.at(0));

	rhs = Parser::parse(v.at(1));
}

Connect_Semicolon::~Connect_Semicolon()
{
	delete lhs;

	delete rhs;

	lhs = nullptr;

	rhs = nullptr;
}

int Connect_Semicolon::execute()
{
	if(terminate==false){
		lhs->execute();

		return rhs->execute();
	}
	else
	{
		return 0;
	}
}

const std::string Connect_Semicolon::to_string() const
{
	return lhs->to_string() + "; " + rhs->to_string();
}

