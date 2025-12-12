input_file = '11.input'
lines = []
rack = {}
with open(input_file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        s = line.strip().split()
        rack[s[0][:-1]] =  s[1:]

def paths(start, end):
    res = 0
    curr = {}
    curr[start] = 1
    while len(curr) > 0:
        next = {}
        for node in curr.keys():
            if node == end:
                res += curr[node]
            elif node == 'out':
                continue
            else:
                for n in rack[node]:
                    if not n in next.keys():
                        next[n] = 0
                    next[n] += curr[node]
        curr = next
    return res

res = paths('svr', 'fft') * paths('fft', 'dac') * paths('dac', 'out') + paths('svr', 'dac') * paths('dac', 'fft') * paths('fft', 'out')
print(res)
