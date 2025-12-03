input_file = '3.input'
lines = []


def get_joltage(b):
    max = 0
    for j in range (0, len(b)):
        for k in range(j+1, len(b)):
            cur = int(f"{b[j]}{b[k]}")
            if  cur > max:
                max = cur
    return max

with open(input_file, 'r') as f:
    lines = f.readlines()

res = 0
for l in lines:
    res += get_joltage(list(l))
print(res)