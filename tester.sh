#!/bin/bash

TEST_DIR=./tests
FILE_DIR=$TEST_DIR/files
MAIN_DIR=$TEST_DIR/mains
SRC_DIR=./srcs
RES_DIR=$TEST_DIR/res

# COLORS 

BLACK="30"
NORMALBLACK="\e[0;${BLACK}m"
BOLDBLACK="\e[1;${BLACK}m"

RED="31"
NORMALRED="\e[0;${RED}m"
BOLDRED="\e[1;${RED}m"

GREEN="32"
NORMALGREEN="\e[0;${GREEN}m"
BOLDGREEN="\e[1;${GREEN}m"

YELLOW="33"
NORMALYELLOW="\e[0;${YELLOW}m"
BOLDYELLOW="\e[1;${YELLOW}m"

BLUE="34"
NORMALBLUE="\e[0;${BLUE}m"
BOLDBLUE="\e[1;${BLUE}m"

MAGENTA="35"
NORMALMAGENTA="\e[0;${MAGENTA}m"
BOLDMAGENTA="\e[1;${MAGENTA}m"

CYAN="36"
NORMALCYAN="\e[0;${CYAN}m"
BOLDCYAN="\e[1;${CYAN}m"

GRAY="90"
NORMALGRAY="\e[0;${GRAY}m"
BOLDGRAY="\e[1;${GRAY}m"

WHITE="97"
NORMALWHITE="\e[0;${WHITE}m"
BOLDWHITE="\e[1;${WHITE}m"

# /***************************************************************************/
#                             GENERAL FUNCTIONS
# /***************************************************************************/
clean () {
	rm -rf $RES_DIR/*
}

print_test_name () {
	echo "$BOLDGRAY ==== $BOLDBLUE $1 $BOLDGRAY ==== $NORMALWHITE"
}

print_buffer_size () {
	echo "$NORMALYELLOW BUFFER_SIZE = $1 $NORMALWHITE"
}

print_ok () {
	echo "$BOLDGREEN OK $NORMALWHITE"
}

print_fail () {
	echo  "$BOLDRED FAIL $NORMALWHITE"
}

compile_test () {
	# $1 ~> test main name
	# $2 ~> buffer size
	print_buffer_size $2
	gcc -Wall -Wextra -Werror $SRC_DIR/get_next_line.c $SRC_DIR/get_next_line_utils.c $MAIN_DIR/$1 -I . -D BUFFER_SIZE=$2 -o gnl
}

if [ "$1" = "clean" ]
then
	echo "deleted all /tests/res/ files"
	clean
	exit
elif [ $# -ne 0 ]
then
	echo "$BOLDRED No argument should be supplied except \"clean\""
	echo "Usage: ./tester.sh"
	exit
else
	clean
fi

# /***************************************************************************/
#                                    SINGLE_LINE
# /***************************************************************************/

single_line_tester () {
	./gnl $FILE_DIR/$1  > $RES_DIR/$1.me
	printf "$1: "
	diff $FILE_DIR/$1 $RES_DIR/$1.me
	if [ $? -eq 0 ];
	then
		print_ok
	else
		print_fail
	fi
}

print_test_name "SINGLE_LINE"

# 32
compile_test single_line.c 32
single_line_tester single_line.txt
# 42
compile_test single_line.c 42
single_line_tester single_line.txt
# 1
compile_test single_line.c 1
single_line_tester single_line.txt
# 10000
compile_test single_line.c 10000
single_line_tester single_line.txt
# 9999999
compile_test single_line.c 9999999
single_line_tester single_line.txt

# /***************************************************************************/
#                                     LONG LINE
# /***************************************************************************/

long_line_tester () {
	./gnl $FILE_DIR/$1  > $RES_DIR/$1.me
	printf "$1: "
	diff $FILE_DIR/$1 $RES_DIR/$1.me
	if [ $? -eq 0 ];
	then
		print_ok
	else
		print_fail
	fi
}

print_test_name "LONG_LINE"

# 32
compile_test long_line.c 32
long_line_tester long_line.txt
# 42
compile_test long_line.c 42
long_line_tester long_line.txt
# 1
compile_test long_line.c 1
long_line_tester long_line.txt
# 10000
compile_test long_line.c 10000
long_line_tester long_line.txt
# 9999999
compile_test long_line.c 9999999
long_line_tester long_line.txt

# /***************************************************************************/
#                                     MUTLIPLE LINES
# /***************************************************************************/

multiple_line_tester () {
    ./gnl $FILE_DIR/$1 > $RES_DIR/$1.me
    printf "$1: ";
    diff $FILE_DIR/$1 $RES_DIR/$1.me
	if [ $? -eq 0 ];
	then
		print_ok
	else
		print_fail
	fi
}

print_test_name "MULTIPLE_LINE"

# 32
compile_test multiple_line.c 32
multiple_line_tester multiple_line.txt
# 42
compile_test multiple_line.c 42
multiple_line_tester multiple_line.txt
# 1
compile_test multiple_line.c 1
multiple_line_tester multiple_line.txt
# 10000
compile_test multiple_line.c 10000
multiple_line_tester multiple_line.txt
# 9999999
compile_test multiple_line.c 9999999
multiple_line_tester multiple_line.txt

# /***************************************************************************/
#                                     MUTLIPLE FD
# /***************************************************************************/

multiple_fd_tester () {
    ./gnl $FILE_DIR/$1 $FILE_DIR/$2 $FILE_DIR/$3

    printf "$1 : ";
    diff $FILE_DIR/$1 $RES_DIR/multi_fd1
	if [ $? -eq 0 ];
	then
		print_ok
	else
		print_fail
	fi

	printf "$2 : ";
	diff $FILE_DIR/$2 $RES_DIR/multi_fd2
	if [ $? -eq 0 ];
	then
		print_ok
	else
		print_fail
	fi

	printf "$2 : ";
	diff $FILE_DIR/$3 $RES_DIR/multi_fd3
	if [ $? -eq 0 ];
	then
		print_ok
	else
		print_fail
	fi
}

print_test_name "MULTIPLE_FD"

# 32
compile_test multiple_fd.c 32
multiple_fd_tester file1.txt file2.txt file3.txt 
# 42
compile_test multiple_fd.c 42
multiple_fd_tester file1.txt file2.txt file3.txt 
# 1
compile_test multiple_fd.c 1
multiple_fd_tester file1.txt file2.txt file3.txt 
# 10000
compile_test multiple_fd.c 10000
multiple_fd_tester file1.txt file2.txt file3.txt 
# 9999999
compile_test multiple_fd.c 9999999
multiple_fd_tester file1.txt file2.txt file3.txt 

# /***************************************************************************/
# 									STDIN
# /***************************************************************************/

stdin_tester () {
	printf "stdin $1: "
	
	arg=$2
	$arg > $RES_DIR/$1.expected
	$arg | ./gnl > $RES_DIR/$1.me
	diff $RES_DIR/$1.expected $RES_DIR/$1.me
	if [ $? -eq 0 ]
	then
		print_ok
	else
		print_fail
	fi
}

stdin_test_battery() {
	stdin_tester "simple_newline" "echo \n"
	stdin_tester "Bonjour" "echo Bonjour"
	stdin_tester "nothing" "echo "
	stdin_tester "c" "echo c"
	stdin_tester "3nl_Bonjour_3nl" "echo \n\n\nBonjour\n\n\n"
	stdin_tester "tab_nl_tab_nl" "echo \t\n\t\n"
	stdin_tester "long_line" "cat $FILE_DIR/long_line.txt"
	stdin_tester "bible" "cat $FILE_DIR/bible.txt"
}

print_test_name "STDIN"

# 32
compile_test stdin.c 32
stdin_test_battery
# 42
compile_test stdin.c 42
stdin_test_battery
# 1
compile_test stdin.c 1
stdin_test_battery
# 10000
compile_test stdin.c 10000
stdin_test_battery
# 9999999
compile_test stdin.c 9999999
stdin_test_battery


printf "\n $BOLDGREEN === $BOLDWHITE TESTS DONE $BOLDGREEN === \n"