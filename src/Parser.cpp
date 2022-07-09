#include <iostream>
#include <sstream>

#include "../header/Parser.hpp"
#include "../header/Command.hpp"
#include "../header/Command_Test.hpp"

#include "../header/RedirectToFile.hpp"
#include "../header/RedirectFromFile.hpp"

#include "../header/Connect_Or.hpp"
#include "../header/Connect_And.hpp"
#include "../header/Connect_Comment.hpp"
#include "../header/Connect_Semicolon.hpp"
#include "../header/Connect_Precedence.hpp"

#include "../header/Connect_Pipe.hpp"

std::vector<std::string> Parser::splitOnceOn(	const std::string& input,
						const std::string& delims	)
{
	std::size_t loc = input.rfind(delims);

	return Parser::splitOnceAt(input, delims, loc);
}


std::vector<std::string> Parser::splitOnceAt(	const std::string& input,
						const std::string& delims,
						const std::size_t& loc		)
{
	std::vector<std::string> ret;
	
	if (loc != std::string::npos)
	{
		ret.push_back(input.substr(0, loc));
		ret.push_back(input.substr(loc + delims.length()));
	}
	else
	{
		ret.push_back(input);
	}

	return ret;
}


std::vector<std::string> Parser::splitOnWS(const std::string& input)
{
	std::vector<std::string> ret;
	std::stringstream ss;

	ss << input;

	std::string temp;

	while (ss >> temp)
	{
		ret.push_back(temp);
	}
	
	return ret;
}				


void Parser::consolidateQuotes(std::vector<std::string>& tokens)
{
	auto start = tokens.begin();

	bool needsFixing = true;
	
	while (needsFixing)
	{
		needsFixing = false;

		while(start != tokens.end())
		{
			std::size_t opening = (*start).find("\"");
		
			if (opening != std::string::npos)
			{
				std::size_t closing = (*start).rfind("\"");

				if (opening == closing) 
				{
					//	So something like:		
					//	"OneBigWordBetweenQuotes"	
					//	doesn't cause things to		
					//	go wonky.			
					//	What should get caught is:	
					//	"NoEndingQuoteHere		
					needsFixing = true;
					break;
				}
			}
			++start;
		}
		
		if (needsFixing)
		{
			bool foundQuotes = false;

			while(foundQuotes == false && start != tokens.end())
			{
				auto middle = start;

				++middle;

				if ((*middle).find("\"") != std::string::npos)
				{
					foundQuotes = true;			
				}
				
				*start += " " + *middle;
	
				tokens.erase(middle);
			}
		}	
	}

	for (int i = 0; i < tokens.size(); i++)
	{
		std::size_t loc;

		do
		{
			loc = tokens.at(i).find("\"");

			if (loc != std::string::npos)
			{
				tokens.at(i).erase(loc, 1);
			}

		}while (loc != std::string::npos);
	}
}


Executable* Parser::parse(const std::string& input)
{
	//std::cout << "masking: " << input << std::endl;
	
	std::string mask = Parser::hide_groups(input);

	//std::cout << "mask: " << mask << std::endl;

	std::size_t loc = mask.find("#");

	if (loc != std::string::npos)
	{
		return new Connect_Comment(Parser::splitOnceAt(input, "#", loc));
	}

	loc = mask.find_first_of("()");

	if (loc != std::string::npos)
	{	
		loc = mask.rfind("; ");

		if (loc != std::string::npos)
		{
			return new Connect_Semicolon(Parser::splitOnceAt(input, "; ", loc));
		}

		loc = mask.find_last_of("&|");

		if (loc != std::string::npos)
		{
			if (mask[loc] == '&')
			{
				loc = mask.rfind(" && ");
			
				return new Connect_And(Parser::splitOnceAt(input, " && ", loc));
			}
			
			if (mask[loc] == '|')
			{
				if (mask[loc - 1] == '|')
				{
					loc = mask.rfind(" || ");
				
					return new Connect_Or(Parser::splitOnceAt(input, " || ", loc));
				}
				else
				{
					loc = mask.rfind(" | ");

					return new Connect_Pipe(Parser::splitOnceAt(input, " | ", loc));
				}
			}
		}
		
		return new Connect_Precedence(input);
	}
	else
	{
		loc = mask.rfind("; ");

		if (loc != std::string::npos)
		{
			return new Connect_Semicolon(Parser::splitOnceAt(input, "; ", loc));
		}

		loc = mask.find_last_of("&|");

		if (loc != std::string::npos)
		{
			if (input[loc] == '&')
			{
				loc = mask.rfind(" && ");

				return new Connect_And(Parser::splitOnceAt(input, " && ", loc));
			}
			
			if (input[loc] == '|')
			{	
				if (input[loc - 1] == '|')
				{
					loc = mask.rfind(" || ");

					return new Connect_Or(Parser::splitOnceAt(input, " || ", loc));
				}
				else
				{
					loc = mask.rfind(" | ");

					return new Connect_Pipe(Parser::splitOnceAt(input, " | ", loc));
				}
			}
		}

		loc = mask.find("test");

		if ((loc != std::string::npos && loc == 0) || mask.find("[ ") != std::string::npos)
		{
			return new Command_Test(input);
		}

		if (mask.rfind(">") != std::string::npos)
		{
			loc = mask.rfind(">>");

			if (loc != std::string::npos)
			{
				return new RedirectToFile(Parser::splitOnceAt(input, ">>", loc), RedirectToFile::Mode::append);
			}
			else
			{
				loc = mask.rfind(">");

				return new RedirectToFile(Parser::splitOnceAt(input, ">", loc), RedirectToFile::Mode::trunc);
			}
		}
		
		if (mask.rfind("<") != std::string::npos)
		{
			loc = mask.rfind("<");

			return new RedirectFromFile(Parser::splitOnceAt(input, "<", loc));
		}
		
		return new Command(input);
	}
}


std::string Parser::hide_groups(const std::string& input)
{
	std::string ret = input;
	
	std::size_t l_paren = ret.rfind("(");
	
	std::size_t r_paren = ret.find(")", l_paren);


	bool l_paren_check = l_paren != std::string::npos;
	
	bool r_paren_check = r_paren != std::string::npos;
	
	while (l_paren_check && r_paren_check)
	{
		//std::cout << "building mask: " << ret << std::endl;
		
		l_paren = ret.rfind("(");
		
		r_paren = ret.find(")", l_paren);

		l_paren_check = l_paren != std::string::npos;
		
		r_paren_check = r_paren != std::string::npos;
	
		if (l_paren == 0 && r_paren == input.length() - 1)
		{
			l_paren++;

			r_paren--;
		}

		if (l_paren != std::string::npos && r_paren != std::string::npos)
		{
			for (std::size_t i = 0; l_paren + i <= r_paren; i++)
			{
				ret[l_paren + i] = '.';
			}
		}

		if (ret.find("(.") == 0)
		{
			break;
		}
	}

	std::size_t l_quote;
	std::size_t r_quote;	

	char quote = '"';

	do
	{
		l_quote = ret.find(quote);
		r_quote = ret.find(quote, l_quote + 1);

		if (l_quote != std::string::npos && r_quote != std::string::npos)
		{
			for (std::size_t i = 0; l_quote + i <= r_quote; i++)
			{
				ret[l_quote + i] = '.';
			}
		}
	}while (l_quote != std::string::npos && r_quote != std::string::npos);

	return ret;
}
