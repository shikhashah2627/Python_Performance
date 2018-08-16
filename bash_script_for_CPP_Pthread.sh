#!/bin/bash

# Get a list of all files beginning with "case" but not *.cpp files
tests=`ls -1 Pthreads_Matrix* | grep -v cpp`
echo $tests
out_file=out_Pthreads_Results${tests}
for var in 1200 1920 3072
    do
        for thread_values in 8 16 24
        do
            for test_run in {1..10}
                do              
                    # { time ./$tests ${var} `expr $var + 100` `expr $var + 200` ; } &>> ${out_file}
                    { time ./$tests ${var} ${var} ${var} ${thread_values}; } &>> ${out_file}
                    echo "Round " ${test_run} " completed. with matrix size of " ${var} "x" ${var} >> ${out_file}
                done
        done 
    done           