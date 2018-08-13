#!/bin/bash

# Get a list of all files beginning with "case" but not *.cpp files
tests=`ls -1 OMP_Matrix* | grep -v cpp`
echo $tests
out_file=out_OMP_Results${tests}
for var in 100 400 1000
    do
        for test_run in {1..10}
            do              
                { time ./$tests ${var} `expr $var + 100` `expr $var + 200` ; } &>> ${out_file}
                echo "Round " ${test_run} " completed. with matrix size of " ${var} "x" `expr $var + 200` >> ${out_file}
            done
    done        