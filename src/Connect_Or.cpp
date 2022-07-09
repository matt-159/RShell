#include "../header/Connect_Or.hpp"

Connect_Or::Connect_Or() : Connector() {}

Connect_Or::Connect_Or(std::vector<std::string>v) : Connector()
{
	lhs = Parser::parse(v.at(0));

	rhs = Parser::parse(v.at(1));
}

Connect_Or::~Connect_Or()
{
	delete lhs;
	
	delete rhs;
	
	lhs = nullptr;
	
	rhs = nullptr;
}

int Connect_Or::execute()
{
	if(terminate==false)
	{
		int lhs_result = lhs->execute();

		if (lhs_result != 0)
		{
			return rhs->execute();
		}
	}
	else
	{
		return 0;
	}
}

const std::string Connect_Or::to_string() const
{
	return lhs->to_string() + " || " + rhs->to_string();
}

