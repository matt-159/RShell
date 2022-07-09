#!/bin/sh


#-------------------------------------------------------#
#		Testing ' && ' Symbol			#
#-------------------------------------------------------#
echo Running Connect-And Test

INPUT=("echo hello && echo world && echo test")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "hello\nworld\ntest")

if [ "${OUTPUT}" = "${test_val}" ]
then
	echo Connect-And Test Passed!
else
	echo Connect-And Test Failed!
fi


#-------------------------------------------------------#
#		Testing ' || ' Symbol			#
#-------------------------------------------------------#
echo Running Connect-Or Test

INPUT=("echo hello || echo world || echo test")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo ${OUTPUT}

test_val=$(echo -e "hello")

if [ "${OUTPUT}" = "${test_val}" ]
then
	echo Connect-Or Test Passed!
else
	echo Connect-Or Test Failed!
fi


#-------------------------------------------------------#
#		Testing '#' Symbol			#
#-------------------------------------------------------#
echo Running Connect-Comment Test

INPUT=("echo hello#echo world; echo test")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "hello")

if [ "${OUTPUT}" = "${test_val}" ]
then
	echo Connect-Comment Test Passed!
else
	echo Connect-Comment Test Failed!
fi


#-------------------------------------------------------#
#		Testing '; ' Symbol			#
#-------------------------------------------------------#
echo Running Connect-Semicolon Test

INPUT=("echo hello; echo world; echo test")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "hello\nworld\ntest")

if [ "${OUTPUT}" = "${test_val}" ]
then
	echo Connect-Semicolon Test Passed!
else
	echo Connect-Semicolon Test Failed!
fi


#-------------------------------------------------------#
#		Testing All Symbols			#
#-------------------------------------------------------#
echo Running Mixed Connectors Test

INPUT=("echo hello; rmdir temp || mkdir temp && mkdir temp || echo world && rmdir temp; echo test")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${OUTPUT}"

test_val=$(echo -e "hello\nworld\ntest")

if [ "${OUTPUT}" = "${test_val}" ]
then
	echo Mixed Connectors Test Passed!
else
	echo Mixed Connectors Test Failed!
fi


#-------------------------------------------------------#
#	Testing Exit Command with Symbols		#
#-------------------------------------------------------#
echo Running Exit Command With Connectors Test

INPUT=("echo hello; exit; echo test")

output=$(./../rshell <<EOF
${INPUT}
EOF
)

echo -e "${output}"

test_val=$(echo -e "hello")

if [ "${output}" = "${test_val}" ]
then
	echo Exit Command With Connectors Test Passed!
else
	echo Exit Command With Connectors Test Failed!
fi
