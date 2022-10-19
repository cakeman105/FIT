#!/bin/bash

#simple C I/O tester
#place into project root folder
echo "C TESTER"
echo ""

for VAR in {0000..0011} #change vars according to test file amount
do
	echo "---------------------"
	echo "test $VAR"
	cat CZE/"$VAR"_in.txt | ./citaty > out/"$VAR"_out.txt
	diff CZE/"$VAR"_out.txt out/"$VAR"_out.txt && echo "TEST PASSED" || echo "TEST FAILED"
done
