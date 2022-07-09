#include "gtest/gtest.h"

#include "parser_tests.hpp"
#include "command_tests.hpp"

#include "parser_parse_tests.hpp"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
