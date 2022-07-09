#ifndef Connector_hpp
#define Connector_hpp

#include "Command.hpp"
#include "Parser.hpp"

class Connector : public Executable
{
	protected:
		Executable* lhs;
		Executable* rhs;

	public:
		Connector() : Executable() {}
		virtual ~Connector() {}
	
		virtual int execute() = 0;
		
		virtual const std::string to_string() const = 0;
};

#endif
