#!/bin/bash

#simple C I/O tester
#place into project root folder with compiled binary and folder containing test files named CZE/

banner "TESTER.SHH"
echo "---------------------------------------"
FILECOUNT=$(ls CZE/ | grep _in.txt | wc -l) #finally automated the test file selection
let "FILECOUNT=FILECOUNT-1"
echo "found $FILECOUNT input test files"
mkdir out && echo "making dir 'out'"
time for VAR in $(eval echo {0000..00$FILECOUNT}) 
do
	echo "---------------------"
	echo "test $VAR"
	cat CZE/"$VAR"_in.txt | ./a.out > out/"$VAR"_out.txt
	diff CZE/"$VAR"_out.txt out/"$VAR"_out.txt && echo "TEST PASSED" || echo "TEST FAILED"
done
