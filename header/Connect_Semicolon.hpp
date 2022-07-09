#ifndef Connect_Semicolon_hpp
#define Connect_Semicolon_hpp

#include "Connector.hpp"

class Connect_Semicolon : public Connector
{
	public:
		Connect_Semicolon();
		Connect_Semicolon(std::vector<std::string> v);

		virtual ~Connect_Semicolon();

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
