#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <vector>

#include "Executable.hpp"

class Parser
{
	private:
		static std::string hide_groups(const std::string& input);
	public:
		static Executable* parse(const std::string& input);

		static std::vector<std::string> splitOnceOn(	const std::string& input,
								const std::string& delims	);

		static std::vector<std::string> splitOnceAt(	const std::string& input,
								const std::string& delims,
								const std::size_t& loc		);

		static std::vector<std::string> splitOnWS(const std::string& input);

		static void consolidateQuotes(std::vector<std::string>& tokens);	
};

#endif
