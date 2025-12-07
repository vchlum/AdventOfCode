input_file = '7.input'
lines = []
problem = []
tmp = []
x = 0
y = 0
beams = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    y = len(lines)
    for line in lines:
        l = line.strip()
        x = len(l);
        beams.append(l)
beam = []
for c in range(0, x):
        if beams[0][c] == 'S':
             beam.append(c)
res = 0
for j in range(1, y):
    beam2=[]
    for i in range(0, x):
        for b in beam:
            if beams[j][b] == '^' and b in beam:
                beam.remove(b)
                split = False
                if b - 1 >=0:
                    beam2.append(b - 1)
                    split = True
                if b + 1 <= x - 1:
                    beam2.append(b + 1)
                    split = True
                if split:
                    res += 1
    beam = list(set(beam + beam2))
print(res)
