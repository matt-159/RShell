CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
	
	src/RShell.cpp

	src/Parser.cpp
	src/Executable.cpp

	src/Command.cpp
	src/Command_Test.cpp

	src/Connect_Or.cpp
	src/Connect_And.cpp
	src/Connect_Comment.cpp
	src/Connect_Semicolon.cpp
	src/Connect_Precedence.cpp

	src/RedirectFromFile.cpp
	src/RedirectToFile.cpp
	src/Connect_Pipe.cpp
)

ADD_EXECUTABLE(test
	unit_tests/unit_tests.cpp

	src/Parser.cpp
	src/Executable.cpp
	
	src/Command.cpp
	src/Command_Test.cpp

	src/Connect_Or.cpp
	src/Connect_And.cpp
	src/Connect_Comment.cpp
	src/Connect_Semicolon.cpp
	src/Connect_Precedence.cpp

	src/RedirectFromFile.cpp
	src/RedirectToFile.cpp
	src/Connect_Pipe.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
