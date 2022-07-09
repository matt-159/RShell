#ifndef parser_tests_hpp
#define parser_tests_hpp

#include "gtest/gtest.h"
#include <string>

#include "../header/Parser.hpp"

//									
//	Testing functio Parser::splitOnWS				
//									

TEST(ParserTest, function_SplitOnWS_sentence)
{
	std::string sentence = "I'm a little teapot, short and stout!";
	std::vector<std::string> words = Parser::splitOnWS(sentence);
	
	EXPECT_EQ(words.size(), 7);
}


TEST(ParserTest, function_SplitOnWS_no_ws)
{
	std::string no_ws = "canyoureadthis?it'sawful!";
	std::vector<std::string> words = Parser::splitOnWS(no_ws);

	EXPECT_EQ(words.size(), 1);
}


TEST(ParserTest, function_SplitOnWS_extra_ws)
{
	std::string extra_ws = "what  is  correct  spacing?";
	std::vector<std::string> words = Parser::splitOnWS(extra_ws);

	EXPECT_EQ(words.size(), 4);
}


TEST(ParserTest, function_SplitOnWS_newlines_and_tabs)
{
	std::string sentence = "hello\tthere!\nGeneral\tKenobi!";

	std::vector<std::string> words = Parser::splitOnWS(sentence);
	EXPECT_EQ(words.size(), 4);
}


TEST(ParserTest, function_SplitOnWS_all_ws_is_removed)
{
	std::string sentence = "hello\tthere!\nGeneral\tKenobi!";

	std::vector<std::string> words = Parser::splitOnWS(sentence);
	
	std::string test = "";

	for (std::string word : words)
	{
		test += word;
	}

	words = Parser::splitOnWS(test);

	EXPECT_EQ(words.size(), 1);
}

//									
//	Testing function Parser::consolidateQuotes			
//									

TEST(ParserTest, function_ConsolidateQuotes_quoted_sentence)
{
	std::string sentence = "Bob says, \"Hello. How are you doing today?\"";
	std::vector<std::string> words = Parser::splitOnWS(sentence);

	Parser::consolidateQuotes(words);

	EXPECT_EQ(words.size(), 3);
}


TEST(ParserTest, function_ConsolidateQuotes_no_quotes)
{
	std::string sentence = "Bob says, Hello. How are you doing today?";
	std::vector<std::string> words = Parser::splitOnWS(sentence);
	
	int before = words.size();

	Parser::consolidateQuotes(words);

	int after = words.size();

	EXPECT_EQ(before, after);
}


TEST(ParserTest, function_ConsolidateQuotes_quotes_at_end)
{
	std::string sentence = "Bob says, \"Hello World\"";
	std::vector<std::string> words = Parser::splitOnWS(sentence);
	
	Parser::consolidateQuotes(words);
	
	EXPECT_EQ(words.size(), 3);
}


TEST(ParserTest, function_ConsolidateQuotes_multiple_quotes)
{
	std::string sentence = "Bob says, \"How are you today?\"."; 
	sentence += " Jim replies, \"Nothing to complain about.\"";
	
	std::vector<std::string> words = Parser::splitOnWS(sentence);

	Parser::consolidateQuotes(words);

	EXPECT_EQ(words.size(), 6);
}


TEST(ParserTest, function_ConsolidateQuotes_empty_inner_quotes)
{
	std::string sentence = "\" \"";
	std::vector<std::string> words = Parser::splitOnWS(sentence);

	Parser::consolidateQuotes(words);

	EXPECT_EQ(words.size(), 1);
}

#endif
