#! /bin/python

import sys
import ast
from math import sqrt, ceil
import pdb

nums = [float(i) for i in sys.argv[1:]]

def gcf (nums):
    gcf = 0
    for i in range(1, int(min(nums)) + 1):
        if all([num % i == 0 for num in nums]):
            gcf = i
    return gcf

gcf_nums = gcf(nums)
sum_nums = sum(nums)
print("{} {}".format(gcf_nums, int(sum_nums / gcf_nums)))
