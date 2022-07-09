#!/bin/sh

#-------------------------------#
#	Provided Pipe Test	#
#-------------------------------#

echo Running provided pipe test

INPUT=("cat < ../names.txt | tr A-Z a-z | tee ../temp.txt | tr a-z A-z > ../temp_2.txt")

OUTPUT=$(./../rshell << EOF
${INPUT}
EOF
)

if (test -e ../temp.txt) && (test -e ../temp_2.txt)
then
	SIZE_1=$(wc -c < ../temp.txt)

	SIZE_2=$(wc -c < ../temp_2.txt)

	if [ "${SIZE_1}" = "${SIZE_2}" ]
	then
		echo provided pipe test PASSED
	else
		echo provided pipe test FAILED
	fi
else
	echo provided pipe test FAILED
fi

rm ../temp.txt ../temp_2.txt

#-------------------------------#
#	    Sort Uniq Pipe Test
#-------------------------------#

echo running sort uniq pipe test

INPUT=("cat < ../names.txt | sort | uniq > ../result.txt")

OUTPUT=$(./../rshell << EOF
${INPUT}
EOF
)

if (test -e ../result.txt)
then
	SIZE_result=$(wc -c < ../result.txt)

	if [ "${SIZE_result}" = "86" ]
	then
		echo sort uniq pipe test PASSED
	else
		echo sort uniq pipe test FAILED
	fi
else
	echo sort uniq pipe test FAILED
fi

rm ../result.txt

#-------------------------------#
#       Sort Pipe Test
#-------------------------------#

echo running sort pipe test

INPUT=("cat < ../names.txt | sort > ../result.txt")

OUTPUT=$(./../rshell << EOF
${INPUT}
EOF
)

if (test -e ../result.txt)
then
    SIZE_result=$(wc -c < ../result.txt)

    if [ "${SIZE_result}" = "86" ]
    then
        echo sort pipe test PASSED
    else
        echo sort pipe test FAILED
    fi
else
    echo sort pipe test FAILED
fi

rm ../result.txt

