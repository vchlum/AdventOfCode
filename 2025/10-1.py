input_file = '10.input'
lines = []
config = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        indicator = ()
        seek = []
        buttons = []
        for l in line.split():
            if l[0] == '[':
                indicator = list(l[1:-1])
                seek = ['.' for x in indicator]
            if l[0] == '(':
                buttons.append([int(x) for x in l[1:-1].split(',')])
        config.append([indicator, seek, buttons])

def press(seek_ind, buttons):
    for b in buttons:
        if seek_ind[b] == '.':
            seek_ind[b] = '#'
        else:
            seek_ind[b] = '.'

res = 0
for conf in config:
    some_min = -1
    n = len(conf[2])
    k = 1
    done = False
    while not done:
        indices = [0] * k
        while True:
            conf[1] = ['.' for x in range(len(conf[0]))]
            for j in indices:
                press(conf[1], conf[2][j])
            if conf[0] == conf[1]:
                done = True
                break
            i = k - 1
            while i >= 0 and indices[i] == n - 1:
                i -= 1
            if i < 0:
                break
            indices[i] += 1
            for j in range(i + 1, k):
                indices[j] = indices[i]
        if not done:
            k += 1
    res += k
print(res)
