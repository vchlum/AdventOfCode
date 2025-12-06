input_file = '6.input'
lines = []
problem = []
tmp = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    y = len(lines)
    for l in range (0, len(lines)):
        line = lines[l]
        x = len(line.split())
        xline = len(line)
        tmp.append(line)

index = 0
skip = False
eq = []
for i in reversed(range(0, xline - 1)):
    if skip:
        skip = False
        continue
    eq.append("")
    for j in range(0, y - 1):
        if tmp[j][i] != ' ':
            eq[index] += tmp[j][i]
    index += 1
    op = tmp[y - 1][i]
    if op == '+' or op == '*':
        eq.append(op)
        index = 0
        skip = True
        problem.append(eq)
        eq = []

res = 0
for eq in problem:
    r = int(eq[0])
    op = eq[len(eq) - 1]
    for i in range(1, len(eq) - 1):
        if op == '+':
            r += int(eq[i])
        if op == '*':
            r *= int(eq[i])
    res += r
print(res)
