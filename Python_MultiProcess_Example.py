#!/usr/bin/env python
import sys
import time
import numpy as np
import multiprocessing

NUM_OF_PROCESSES = 4

def matrix_mult(X,Y):
    result = [[sum(a*b for a,b in zip(X_row,Y_col)) for Y_col
    in zip(*Y)] for X_row in X]
    #print result

K = int(sys.argv[1])
L = int(sys.argv[2])
M = int(sys.argv[3])
X = np.random.randint(0,10,size=(K,L))
#print [i for i in X]
Y = np.random.randint(0,10,size=(L,M))
start_time = time.time()
processes = [multiprocessing.Process(target=matrix_mult,args=(X,Y))
for _ in range(int(NUM_OF_PROCESSES))]
[process.start() for process in processes] 
[process.join() for process in processes]
end_time = time.time()

print("Parallel time=" , end_time - start_time)   
