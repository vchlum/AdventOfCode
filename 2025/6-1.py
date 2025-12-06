input_file = '6.input'
lines = []

problem = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    y = len(lines)
    for l in range (0, len(lines)):
        tmp = []
        line = lines[l].split()
        x = len(line)
        for w in range(0, len(line)):
            if (line[w] == '+' or line[w] == '*'):
                tmp.append(line[w].strip())
            else:
                tmp.append(int(line[w].strip()))
        problem.append(tmp)

res = 0
for i in range(0, x):
    r = problem[0][i]
    op = problem[y - 1][i]
    for j in range(1, y - 1):
        if op == '+':
            r += problem[j][i]
        if op == '*':
            r *= problem[j][i]
    res += r
print(res)
