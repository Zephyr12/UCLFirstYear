def clamp(a):
    return sorted([0,a,3])[1]

def adj(n):
    x, y = (n-1)%4, (n-1)//4
    coord_pairs = list(set([clamp(x+a) + 4*clamp(y+b) + 1 for a, b in [(0,1), (0,-1), (-1,0), (1,0)]] + [n]))
    return coord_pairs

def whack(l, n):
    a = adj(n)
    x = l[::]
    for index, value in enumerate(l):
        x[index] = not l[index] if (index + 1 in a) else l[index]
    return x

def print_list(l):
    fck_herbster = [13,14,15,16,
                    9,10,11,12,
                    5,6,7,8,
                    1,2,3,4]
    for index, val in enumerate(l):
        print("x" if l[fck_herbster[index] - 1] else "o", end=" ")
        if (index % 4 == 3):
            print()

def transition(l):
    return [(n, whack(l, n)) for n in range(1,17) if l[n-1]]

def bfs(l, target):
    searched = []
    searching = [(l, [])]
    candidates = []
    while 1:
        print(searched, searching)
        for state, path in searching:
            if state == target:
                return path
            else:
                for n, new_state in transition(state):
                    if new_state == target:
                        return path+[n]
                    if new_state not in [s[0] for s in searched]:
                        candidates.append((new_state, path+[n]))
        searched += searching
        searching = candidates
        candidates = []

def construct(arr):
    l = [False]*16
    for v in arr:
        l[v-1] = True
    return l
