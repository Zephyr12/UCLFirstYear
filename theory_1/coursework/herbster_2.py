#! /bin/env python

import sys
import ast
import pdb
import random

try:
    input_data = ast.literal_eval(sys.argv[1])
    if type(input_data) != type([]):
        raise Exception("HELL")
except:
    input_data = [random.randint(1,1000) for i in range(int(sys.argv[1]))]
print(input_data)
nodes = list(zip(input_data[0::2], input_data[1::2]))

def manhatten(a,b):
    return abs(b[0] - a[0]) + abs(b[1] - a[1])

def prims(nodes, dist_func):
    # pdb.set_trace()
    mst = [nodes[0]]
    total_weight = 0
    while len(mst) != len(nodes):
        next_node = ("NOPE!","NOPE!")
        next_weight = 10000000000000000000
        for in_node in mst[:]:
            for out_node in nodes[:]:
                if out_node not in mst:
                    if dist_func(in_node, out_node) < next_weight:
                        next_node = out_node
                        next_weight = dist_func(in_node, out_node)
        total_weight += next_weight
        mst.append(next_node)


    return total_weight

print(prims(list(set(nodes)), manhatten))
