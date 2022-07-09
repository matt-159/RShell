#include <string>
#include <sstream>

#include "gtest/gtest.h"

#include "../header/Parser.hpp"
#include "../header/Command.hpp"
#include "../header/Connect_Or.hpp"
#include "../header/Connect_And.hpp"
#include "../header/Connect_Comment.hpp"
#include "../header/Connect_Semicolon.hpp"

TEST(ParserParseTestSet, ParseCommandTest)
{
	Executable* e = Parser::parse("ls -a");
	
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParserSingleOrTest)
{
	Executable* e = Parser::parse("echo hello world || echo goodbye cruel world");

	EXPECT_EQ("echo hello world || echo goodbye cruel world", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseMultipleOrTest)
{
	Executable* e = Parser::parse("echo hello || echo goodbye || echo world");

	EXPECT_EQ("echo hello || echo goodbye || echo world", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParserSingleAndTest)
{
	Executable* e = Parser::parse("echo hello world && echo goodbye cruel world");

	EXPECT_EQ("echo hello world && echo goodbye cruel world", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseMultipleAndTest)
{
	Executable* e = Parser::parse("echo hello && echo goodbye && echo world");

	EXPECT_EQ("echo hello && echo goodbye && echo world", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParserSingleCommentTest)
{
	Executable* e = Parser::parse("echo hello world# || echo goodbye cruel world");

	EXPECT_EQ("echo hello world", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParserSingleSemicolonTest)
{
	Executable* e = Parser::parse("echo hello world; echo goodbye cruel world");

	EXPECT_EQ("echo hello world; echo goodbye cruel world", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseMultipleSemicolonTest)
{
	Executable* e = Parser::parse("echo hello; echo goodbye; echo world");

	EXPECT_EQ("echo hello; echo goodbye; echo world", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseMixAndMatchTest)
{
	Executable* e = Parser::parse("ls -a && echo world || echo hello; echo asdf#jkl;");

	EXPECT_EQ("ls -a && echo world || echo hello; echo asdf", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseMixAndMatchWithExitTest)
{
	Executable* e = Parser::parse("ls -a || exit && echo hello world; echo didn't quit");

	EXPECT_EQ("ls -a || exit && echo hello world; echo didn't quit", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests1)
{
	Executable* e = Parser::parse("echo \"A#; echo B\"");

	EXPECT_EQ("echo \"A#; echo B\"", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests2)
{
    Executable* e = Parser::parse("echo \"A && exit\"");

    EXPECT_EQ("echo \"A && exit\"", e->to_string());
    EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests3)
{
    Executable* e = Parser::parse("echo \"\"");

    EXPECT_EQ("echo \"\"", e->to_string());
    EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests4)
{
    Executable* e = Parser::parse("echo \"echo echo ; echo echo\"");

    EXPECT_EQ("echo \"echo echo ; echo echo\"", e->to_string());
    EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests5)
{
	Executable* e = Parser::parse("(test -d __test__.txt && (echo True A && echo True B))");

	EXPECT_EQ("(test -d __test__.txt && (echo True A && echo True B))", e->to_string());
	EXPECT_EQ(1, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests6)
{
	Executable* e = Parser::parse("(test -e __test__.txt && (echo True A && echo \"True B in quotes\"))");

	EXPECT_EQ("(test -e __test__.txt && (echo True A && echo \"True B in quotes\"))", e->to_string());
	EXPECT_EQ(1, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests7)
{
	Executable* e = Parser::parse("(echo Truee && (echo Truee && (echo Truee)))");

	EXPECT_EQ("(echo Truee && (echo Truee && (echo Truee)))", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests8)
{
	Executable* e = Parser::parse("(echo Truee || (echo Falsee))");

	EXPECT_EQ("(echo Truee || (echo Falsee))", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParseFailedTests9)
{
	Executable* e = Parser::parse("(echo Truee && (echo \"Truee in quotes\"))");

	EXPECT_EQ("(echo Truee && (echo \"Truee in quotes\"))", e->to_string());
	EXPECT_EQ(0, e->execute());
}

TEST(ParserParseTestSet, ParsePipesAndRedirection)
{
	std::string input = "cat < ../names.txt | tr A-Z a-z | tee temp.txt | tr a-z A-Z > temp2.txt";

	Executable* e = Parser::parse(input);

	EXPECT_EQ(input, e->to_string());
	EXPECT_EQ(0, e->execute());
}
