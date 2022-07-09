#include "../header/Connect_Comment.hpp"

Connect_Comment::Connect_Comment() : Connector() {}

Connect_Comment::Connect_Comment(std::vector<std::string>v) : Connector()
{
	lhs = Parser::parse(v.at(0));

	rhs = nullptr;
}

Connect_Comment::~Connect_Comment() 
{
	delete lhs;

	lhs = nullptr;
}

int Connect_Comment::execute()
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

const std::string Connect_Comment::to_string() const
{
	return lhs->to_string();
}

