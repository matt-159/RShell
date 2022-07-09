#!/bin/sh

#---------------------------------------#
#	Simple Redirection Test		#
#---------------------------------------#

INPUT=("wc -c < ../names.txt")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

if [ "${OUTPUT}" = "86" ]
then
	echo Simple Redirection Test PASSED
else
	echo Simple Redirection Test FAILED
fi

#---------------------------------------#
#   Simple Sort Redirection Test     #
#---------------------------------------#

INPUT=("cat ../names.txt | sort > ../result.txt")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

INPUT2=("wc -c < ../result.txt")

OUTPUT=$(./../rshell <<EOF
${INPUT2}
EOF
)

if [ "${OUTPUT}" = "86" ]
then
	echo Simple Sort Redirection Test PASSED
else 
	echo Simple Sort Redirection Test FAILED
fi

rm ../result.txt

#-----------------------------------------#
#    Line Count Redirection Test
#-----------------------------------------#

INPUT=("wc -l < ../header/Command.hpp")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

if [ "${OUTPUT}" = "23" ]
then
	echo Line Count Redirection Test PASSED
else
	echo Line Count Redirection Test FAILED
fi


#-----------------------------------------#
#       And and Or Redirection Test
#-----------------------------------------#

INPUT=("(wc -l < ../header/Redirect.hpp) && (wc -c < ../header/Redirect.hpp) && (wc -l < ../src/Connect_Or.cpp) || (wc -w < ../src/Connect_And.cpp) && (wc -m < ../header/Command.hpp)")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

test_val=$(echo -e "22\n301\n44\n306")

if [ "${OUTPUT}" = "${test_val}" ]
then
	echo And and Or Redirection Test PASSED
else
	echo And and Or Redirection Test FAILED
fi


#-----------------------------------------------#
#      Many Ands and Ors Test
#-----------------------------------------------#

INPUT=("(wc -l < ../header/Parser.hpp) && (wc -c < ../header/Connector.hpp) && (wc -l < ../src/Connect_Pipe.cpp) || (wc -w < ../src/Connect_Or.cpp) && (wc -m < ../header/Command_Test.hpp); (wc -l < ../header/Executable.hpp) && (wc -c < ../header/RedirectFromFile.hpp) && (wc -l < ../src/RShell.cpp) || (wc -w < ../src/Connect_Precedence.cpp) && (wc -m < ../header/Connect_Comment.hpp) && (wc -l < ../header/Connect_Semicolon.hpp) && (wc -c < ../header/RedirectToFile.hpp) && (wc -l < ../src/Connect_Comment.cpp) || (wc -w < ../src/Connect_Pipe.cpp) && (wc -m < ../header/Connector.hpp)")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

test_val=$(echo -e "28\n343\n109\n484\n23\n375\n95\n318\n19\n404\n35\n343")

if [ "${OUTPUT}" = "${test_val}" ]
then
    echo Many Ands and Ors Test PASSED
else
    echo Many Ands and Ors Test FAILED
fi

