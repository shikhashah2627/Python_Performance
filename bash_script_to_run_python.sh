#!/bin/bash

# Get a list of all files beginning with "case" but not *.cpp files
tests=`ls -1 python_matr*`
echo $tests
out_file=out_${tests}.${var}.${test_run}
for var in 1000 2000 3000
    do
        for thread_values in 8 16 24
        do
            for test_run in {1..10}
                do              
                    { time ./$tests ${var} ${var} ${var} ${thread_values}; } &>> ${out_file}
                    echo "Round " ${test_run} " completed. with matrix size of " ${var} "x" ${var} "with threads" ${thread_values}>>"${out_file}"
                done
        done 
    done    

