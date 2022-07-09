#ifndef Connect_Comment_hpp
#define Connect_Comment_hpp

#include "Connector.hpp"

class Connect_Comment : public Connector
{
	public:
		Connect_Comment();
		Connect_Comment(std::vector<std::string>v);

		virtual ~Connect_Comment();

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
