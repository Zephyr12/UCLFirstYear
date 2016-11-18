import pdb
import sys
import time

sys.setrecursionlimit(100000)

def memorised(f):
    def new_fn(*args):
        # pdb.set_trace()
        mem = new_fn.mem
        if args not in mem:
            ret_val = f(*args)
            mem[args] = ret_val
        #print (mem)
        return mem[args]
    new_fn.mem = {}
    return new_fn

def num_permutations(l):
    digit_counts = {}
    for i in l:
        if i in digit_counts:
            digit_counts[i] += 1
        else:
            digit_counts[i] = 1
    t = factorial(len(l))
    for key, value in digit_counts.items():
        t /= factorial(value)
    return t


@memorised
def factorial(a):
    if a <= 1:
        return 1
    else:
        return a * factorial(a-1)

def sln(a,b):
    solutions = []
    for i in range(10**b + 1):
        #if i % 10000 == 0:
        #    print(i / 10**b)
        if sum(map(int, str(i))) == a:
            solutions.append(i)
    return solutions

def partition(n, s=[10]):
    #print (n, s)
    partitions = []
    #print ([x for x in "123456789" if int(x) <= n])
    for c in [x for x in "123456789" if int(x) <= min(n, s[-1])]:
        if n - int(c) == 0:
            partitions.append(s + [int(c)])
        elif n - int(c) > 0:
            partitions += (partition (n - int(c), s + [int(c)]))
        else:
            pass
    return partitions



def sln2(digits, total):
    parts = [
                num_permutations([0]*(digits - len(part) + 1) + part[1:])
                for part in partition(total) 
                if len(part) <= digits + 1
            ]
    return sum(parts)

