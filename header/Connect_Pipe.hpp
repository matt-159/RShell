#ifndef Connect_Pipe_hpp
#define Connect_Pipe_hpp

#include "Connector.hpp"

class Connect_Pipe : public Connector
{
	public:
		Connect_Pipe();

		Connect_Pipe(std::vector<std::string> v);

		virtual ~Connect_Pipe();

		virtual int execute();

		virtual const std::string to_string() const;
};

#endif
