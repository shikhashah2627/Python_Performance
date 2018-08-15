import multiprocessing
from itertools import izip, repeat, imap, starmap
from operator import mul
import sys
import numpy as np

def calc_row_of_product_matrix(a_row, b, zip=zip):
    #print "In Calc function"
    #print map(lambda col: sum(starmap(mul,zip(a_row,col))), zip(*b))
    return map(lambda col: sum(starmap(mul,zip(a_row,col))), zip(*b))

def eval_func_tuple(row_args):
    #print "In eval function"
    #print (row_args[1:])
    return row_args[0](*row_args[1:])

class multimatrix(list):

    def __mul__(self,b,zip=zip,repeat=repeat):
        pool = multiprocessing.Pool(multiprocessing.cpu_count())
        return pool.map(eval_func_tuple, zip(repeat(calc_row_of_product_matrix), self, repeat(b)))


if __name__ == '__main__':
    K = int(sys.argv[1])
    L = int(sys.argv[2])
    M = int(sys.argv[3])
    X = np.random.randint(0,10,size=(K,L))
    Y = np.random.randint(0,10,size=(L,M))

    #print X
    #print Y
    final_matrix = multimatrix(X) * multimatrix(Y)
    #print final_matrix
