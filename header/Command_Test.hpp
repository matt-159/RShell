#ifndef Command_Test_hpp
#define Command_Test_hpp

#include <sys/stat.h>

#include "Executable.hpp"

class Command_Test : public Executable
{
	private:
		std::string path;
		
		std::string flag;

		struct stat sb;

		bool (Command_Test::*test)();

		bool test_e();

		bool test_f();

		bool test_d();

	public:
		Command_Test();

		Command_Test(const std::string& cmd);

		virtual ~Command_Test(); 

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
