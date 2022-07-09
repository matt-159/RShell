#ifndef Command_Tests_hpp
#define Command_Tests_hpp

#include "gtest/gtest.h"
#include <string>

#include "../header/Command.hpp"

TEST(CommandTestSet, DefaultConstructorTest)
{
	Command* c = new Command();

	EXPECT_NE(0, c->execute());
}

TEST(CommandTestSet, ExplicitConstructorTest)
{
	Command* c = new Command("ls -a");

	EXPECT_EQ(0, c->execute());
}

TEST(CommandTestSet, OstreamOperatorTest)
{
	Command* c = new Command("ls -a");

	EXPECT_EQ("ls -a", c->to_string());
}
#endif
