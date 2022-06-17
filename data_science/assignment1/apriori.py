import sys
import pandas as pd
import numpy as np
from itertools import combinations
import math

data = []
items = []
t = []
candi_init = []
candi_set = []
freq_set = []
min_supp = 0

def cal_freq(data, set_):
    cnt = 0
    for i in range(len(data)):
        if set(set_).issubset(set(data[i])):
            cnt = cnt + 1
    return cnt

def support(data, n):
    return n/len(data) * 100

def nCr(n, r):
    f = math.factorial
    if n < r:
        return 0
    if n == r:
        return 1
    return f(n) // f(r) // f(n-r)

def write_file(data, freq_set):
    for i in range(1, len(freq_set)):
        for j in range(len(freq_set[i])):
            for k in range(1, len(freq_set[i][j][0])):
                for ele in combinations(list(freq_set[i][j][0]), k):
                    output_file.write(str(set(ele)) + '\t' + str(set(freq_set[i][j][0] - set(ele))) + '\t' 
                    + format(freq_set[i][j][1], '.2f') + '\t' + format(freq_set[i][j][1]/support(data, cal_freq(data, set(ele))) * 100, '.2f') + '\n')

# generate k-th candidate set
def candi_set_gen(data, items, k):
    global candi_set
    if k == 0:
        candi_set.append([])
        for i in range(len(items)):
            cnt = cal_freq(data, [items[i]])
            candi_set[k].insert(len(candi_set[k]),(set([items[i]]), support(data, cnt)))

    else:
        candi_set.append([])

        # pruning
        comb_all = combinations(items, k + 1)
        for comb in comb_all:
            chk = 0
            for pset in freq_set[k-1]:
                if set(pset[0]).issubset(set(comb)):
                    chk = chk + 1

            if chk >= (nCr(k + 1, k)):
                cnt = cal_freq(data, comb)
                candi_set[k].insert(len(candi_set[k]), (set(comb), support(data, cnt)))

# generate k-th frequent set
def freq_set_gen(candi_set, min_supp, k):
    global freq_set
    freq_set.append([])
    freq_set[k] = [x for x in candi_set[k] if x[1] >= min_supp]
    

def apriori(input_file, output_file, min_supp):
    global data
    global candi_set
    global items

    data = input_file.readlines()
    for i in range(len(data)):
        data[i] = data[i].strip().split('\t')
        data[i] = list(map(int, data[i]))

    t = pd.DataFrame(data).fillna(-1).astype('int')

    for i in range(len(t.columns)):
        items = np.concatenate((items, t[i].unique()), axis = 0)
    items = np.unique(items)
    items = np.delete(items, 0).astype('int')

    k = 0
    while True:
        candi_set_gen(data, items, k)
        freq_set_gen(candi_set, min_supp, k)
        if len(freq_set[k]) == 0:
            del freq_set[k]
            break
        k = k + 1

if __name__ == '__main__':
    min_supp = int(sys.argv[1])
    input_file = open(sys.argv[2], 'r')
    output_file = open(sys.argv[3], 'w')

    apriori(input_file, output_file, min_supp)

    write_file(data, freq_set)