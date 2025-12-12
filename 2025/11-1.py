input_file = '11.input'
lines = []
rack = {}
with open(input_file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        s = line.strip().split()
        rack[s[0][:-1]] =  s[1:]

def BFS(s, e):
    r = 0
    queue = [s]
    while len(queue)> 0:
        n = queue.pop()
        for i in rack[n]:
            if i == e:
                r += 1
            queue += [j for j in rack.keys() if j == i]
    return r

res = BFS('you', 'out')
print(res)
