#include "../header/Connect_And.hpp"

Connect_And::Connect_And() : Connector() {}

Connect_And::Connect_And(std::vector<std::string>v) : Connector()
{
	lhs = Parser::parse(v.at(0));

	rhs = Parser::parse(v.at(1));
}

Connect_And::~Connect_And() 
{
	delete lhs;

	delete rhs;

	lhs = nullptr;

	rhs = nullptr;
}

int Connect_And::execute()
{
	if(terminate==false)
	{
		int lhs_result = lhs->execute();

		if (lhs_result == 0)
		{
			return rhs->execute();	
		}
	}
	else{
		return 0;
	}
}

const std::string Connect_And::to_string() const
{
	return lhs->to_string() + " && " + rhs->to_string();
}

