#!/bin/sh

#-----------------------------------------------------#
#               Testing Single Parentheses
#-----------------------------------------------------#
echo Single Parentheses Test

INPUT=("echo hello || (echo world && echo test)")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "hello")

if [ "${OUTPUT}" = "${test_val}" ]
then
    echo Single Parentheses Test Passed!
else
    echo Single Parentheses Test Failed!
fi


#------------------------------------------------------#
#               Testing Uneven Parentheses
#------------------------------------------------------#
echo Uneven Parentheses Test

INPUT=("((echo temp) && (echo world)")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "Cannot execute an unbalanced input. A small price to pay for salvation.")

if [ "${OUTPUT}" = "${test_val}" ]
then
    echo Uneven Parentheses Test Passed!
else
    echo Uneven Parentheses Test Failed!
fi

#------------------------------------------------------#
#               Previously Failed Case in Parentheses
#------------------------------------------------------#
echo Previously Failed Case in Parentheses Test

INPUT=("(echo \"A #; echo B\")")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "A #; echo B")

if [ "${OUTPUT}" = "${test_val}" ]
then
    echo Previously Failed Case in Parentheses Test Passed!
else
    echo Previously Failed Case in Parentheses Test Failed!
fi


#------------------------------------------------------#
#          Testing Multiple Commands in Parentheses
#------------------------------------------------------#
echo Parentheses Multi Command Test

INPUT=("(echo world) && (echo temp) && (echo hello) && (echo another) || (echo multi)")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "world\ntemp\nhello\nanother")

if [ "${OUTPUT}" = "${test_val}" ]
then
    echo Parentheses Multi Command Test Passed!
else
    echo Parentheses Multi Command Test Failed!
fi


#------------------------------------------------------#
#          Testing Provided Example Case
#------------------------------------------------------#
echo Provided Parentheses Example Test

INPUT=("(echo A && echo B) || (echo C && echo D)")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "A\nB")

if [ "${OUTPUT}" = "${test_val}" ]
then
    echo Provided Parentheses Example Test Passed!
else
    echo Provided Parentheses Example Test Failed!
fi


