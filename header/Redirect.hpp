#ifndef Redirect_hpp
#define Redirect_hpp

#include "Executable.hpp"

class Redirect : public Executable
{
	protected:
		Executable* e;

		std::string path;
	public:
		Redirect() {}

		virtual ~Redirect() {}

		virtual int execute() = 0;

		virtual const std::string to_string() const = 0;
};

#endif
