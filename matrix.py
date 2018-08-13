#!/usr/bin/env python
'''
import sys
import time
import numpy as np
import multiprocessing

NUM_OF_PROCESSES = 10

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
'''

import random
import multiprocessing
from itertools import starmap, izip, repeat, imap
from operator import mul
import timeit
import numpy as np

def calc_row_of_product_matrix(a_row, b, zip=zip):
    '''Calculate a row of the product matrix P = A * B
    Arguments:
      a_row is af A
      b is the B matrix
    returns the corresponding row of P matrix'''
    return map(lambda col: sum(starmap(mul,zip(a_row,col))), zip(*b))

def eval_func_tuple(f_args):
    '''Takes a tuple of a function and args, evaluates and returns result'''
    return f_args[0](*f_args[1:])

class multimatrix(list):

    def __mul__(self, b, zip=zip, repeat=repeat):
        '''Concurrent matrix multiplication with multiprocessing.Pool. '''
        pool = multiprocessing.Pool(multiprocessing.cpu_count())
        return pool.map(eval_func_tuple, zip(repeat(calc_row_of_product_matrix), self, repeat(b))) 

class itermatrix(list):

    @staticmethod
    def sumprod(row, col, sum=sum, starmap=starmap, mul=mul):
        '''Returns sumproduct of two vectors.'''
        return sum(starmap(mul,zip(row,col)))

    def __mul__(self, b, imap=imap, zip=zip):
        '''Matrix multiplication returning iterable of iterables'''
        return imap(lambda row: imap(lambda col: itermatrix.sumprod(row, col), zip(*b)), self)

def iterate_results(result):
    '''Iterate over iterable of iterables,
    and returns elements in list of lists.
    Usage: if you want to run the whole calculation at once:
    p = iterate_results(itermatrix([[1, 3], [-5, 6], [2, 4]]) * itermatrix([[1, 4], [8, 7]]))'''
    return[[col for col in row] for row in result]

def random_v(K=1000,min=-1000,max=1000):
    '''Generates a random vector of dimension N;
    Returns a list of integers.
    The values are integers in the range [min,max].'''
    return [random.randint(min,max) for k in range(K)]

def random_m(N=1000, K=1000):
    '''Generates random matrix. Returns list of list of integers.'''
    #return [random_v(K) for n in range(N)]
    return np.random.randint(0,10,size=(K,N))