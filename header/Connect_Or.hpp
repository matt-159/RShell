#ifndef Connect_Or_hpp
#define Connect_Or_hpp

#include "Connector.hpp"

class Connect_Or : public Connector
{
	public:
		Connect_Or();
		Connect_Or(std::vector<std::string>v);

		virtual ~Connect_Or();

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
