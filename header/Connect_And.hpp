#ifndef Connect_And_hpp
#define Connect_And_hpp

#include "Connector.hpp"

class Connect_And : public Connector
{
	public:
		Connect_And();

		Connect_And(std::vector<std::string>v);

		virtual ~Connect_And();

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
