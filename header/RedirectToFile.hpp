#ifndef RedirectToFile_hpp
#define RedirectToFile_hpp

#include "Redirect.hpp"
#include <vector>


class RedirectToFile : public Redirect
{
	public:

		enum Mode {trunc, append, none};

		RedirectToFile();

		RedirectToFile(std::vector<std::string> v, Mode mode);

		virtual ~RedirectToFile();

		virtual int execute();

		virtual const std::string to_string() const;

	private:

		Mode mode;
};

#endif
