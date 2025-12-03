input_file = '3.input'
lines = []

def get_joltage(b):
    i=[-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]

    for j in range(0, len(i)):
        max = 0
        for k in range(0 if j == 0 else i[j - 1] + 1, len(b) - len(i) + j):
            if int(b[k]) > max:
                i[j] = k
                max = int(b[k])
         
    return int(f"{b[i[0]]}{b[i[1]]}{b[i[2]]}{b[i[3]]}{b[i[4]]}{b[i[5]]}{b[i[6]]}{b[i[7]]}{b[i[8]]}{b[i[9]]}{b[i[10]]}{b[i[11]]}")

with open(input_file, 'r') as f:
    lines = f.readlines()

res = 0
for l in lines:
    res += get_joltage(list(l))
print(res)