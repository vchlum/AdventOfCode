input_file = '12.input'
lines = []
presents = {}
areas = {}
with open(input_file, 'r') as f:
    lines = f.readlines()
    ai = -1
    for line in lines:
        l = line.strip().split()
        if len(l) == 1:
            if ':' in l[0]:
                pi = int(l[0][:-1])
                presents[pi] = {}
                presents[pi]['size'] = 0
            else:
                presents[pi]['size'] += sum([ 1 if i == '#' else 0 for i in l[0]])

        if len(l) > 1:
            ai += 1
            areas[ai] = {'x': int(l[0][:-1].split('x')[0]), 'y': int(l[0][:-1].split('x')[1])}
            areas[ai]['req'] = [int(i) for i in l[1:]]

def check_size(a):
    size = a['x'] * a['y']
    req = 0
    for i in range(len(a['req'])):
        req += presents[i]['size'] * a['req'][i]
    if req > size:
        return False
    return True

res = 0
for i in areas:
    if check_size(areas[i]):
        res += 1
print(res)
