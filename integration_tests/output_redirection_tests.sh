#!/bin/sh

#---------------------------------------#
#	Simple Redirection Test		#
#---------------------------------------#

INPUT=("echo asdf > ../temp.txt")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

SIZE=$(wc -c < ../temp.txt)

if [ "${SIZE}" = "5" ]
then
	echo Simple Redirection Test PASSED
else
	echo Simple Redirection Test FAILED
fi

rm ../temp.txt

#---------------------------------------#
#   Double Arrow Redirection Test     #
#---------------------------------------#

INPUT=("echo asdf >> ../temp.txt")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

SIZE=$(wc -c < ../temp.txt)

if [ "${SIZE}" = "5" ]
then
    echo Double Arrow Redirection Test PASSED
else
    echo Double Arrow Redirection Test FAILED
fi

rm ../temp.txt

#----------------------------------------#
#    Append Contents Test
#----------------------------------------#

INPUT=("echo asdf >> ../temp.txt")

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

OUTPUT=$(./../rshell <<EOF
${INPUT}
EOF
)

SIZE=$(wc -c < ../temp.txt)

if [ "${SIZE}" = "10" ]
then
	echo Append Contents Test PASSED
else
	echo Append Contents Test FAILED
fi

rm ../temp.txt

