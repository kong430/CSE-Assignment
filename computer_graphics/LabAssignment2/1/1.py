import math
import numpy as np

M = np.array([2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26])
print(M, "\n")
M = M.reshape(5,5)
print(M, "\n")
M[1:4,1:4] = 0
print(M, "\n")
M = M@M
print(M, "\n")
v = M[0,:]
print(math.sqrt(sum(i**2 for i in v)))
