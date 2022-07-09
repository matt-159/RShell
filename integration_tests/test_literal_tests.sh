#!/bin/sh

#-------------------------------------------------------#
#			Test: mkdir			#
#-------------------------------------------------------#
.././rshell <<< "mkdir asdfasdf"

if [ -e asdfasdf ]; then
	echo "Test: mkdir succeeded"
else
	echo "Test: mkdir failed"
fi


#-------------------------------------------------------#
#			Test: rmdir			#
#-------------------------------------------------------#
.././rshell <<< "rmdir asdfasdf"

if ! [ -e asdfasdf ]; then
	echo "Test: rmdir succeeded"
else
	echo "Test: rmdir failed"
fi


#-------------------------------------------------------#
#			Test: cp			#
#-------------------------------------------------------#
.././rshell <<< "cp precedence_tests.sh words.txt"

if [ -e words.txt ]; then
	echo "Test: cp succeeded"
else
	echo "Test: cp failed"
fi


#-------------------------------------------------------#
#			Test: rm			#
#-------------------------------------------------------#
.././rshell <<< "rm words.txt"

if ! [ -e words.txt ]; then
	echo "Test: rm succeeded"
else
	echo "Test: rm failed"
fi


#git status
#ls -a
#cat ../images/ascii.txt
