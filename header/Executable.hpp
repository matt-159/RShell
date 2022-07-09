#ifndef Executable_hpp
#define Executable_hpp

#include <string>

class Executable
{
	protected:
		static bool terminate;

	public:
		Executable() {this->terminate = false;}
		
		bool isTerminated(){return this->terminate;}

		virtual ~Executable() {}
		
		virtual int execute() = 0;
		
		virtual const std::string to_string() const = 0;
};

#endif
