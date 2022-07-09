#ifndef Connect_Precedence_hpp
#define Connect_Precedence_hpp

#include "Connector.hpp"

class Connect_Precedence : public Connector
{
	public:
		Connect_Precedence();
		
		Connect_Precedence(const std::string& command);

		virtual ~Connect_Precedence();

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
