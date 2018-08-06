#!/bin/bash

# Get a list of all files beginning with "case" but not *.cpp files
tests=`ls -1 Python*`
echo $tests
out_file=out_${tests}.${var}.${test_run}
for var in 100 400 1000
    do
        for test_run in {1..10}
            do              
                { ./$tests ${var} ${var} ${var} ; } &>> ${out_file}
                echo "Round " ${test_run} " completed. with matrix size of " ${var} "x" ${var} >> ${out_file}
            done
    done        