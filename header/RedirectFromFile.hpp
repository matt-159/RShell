#ifndef RedirectFromFile_hpp
#define RedirectFromFile_hpp

#include "Redirect.hpp"

#include <vector>

class RedirectFromFile : public Redirect
{
	public:
		RedirectFromFile();

		RedirectFromFile(std::vector<std::string> v);

		virtual ~RedirectFromFile();

		virtual int execute();

		virtual const std::string to_string() const;

	private:

		bool fileExists;	
};

#endif
