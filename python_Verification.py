import numpy as np
import sys

if __name__ == '__main__':
    K = int(sys.argv[1])
    L = int(sys.argv[2])
    M = int(sys.argv[3])
    X = np.random.randint(0,10,size=(K,L))
    Y = np.random.randint(0,10,size=(L,M))

    Z = np.matmul(X,Y)