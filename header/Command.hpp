#ifndef Command_hpp
#define Command_hpp

#include "Executable.hpp"

class Command : public Executable
{
	private:
		std::string command;
	
	public:
		Command();

		Command(const std::string& cmd);

		virtual ~Command(); 

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
