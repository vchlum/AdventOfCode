input_file = '8.input'
lines = []
boxes = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        boxes.append([int(i) for i in line.split(',')])

def distance(box1, box2):
    return ((box1[0] - box2[0])**2 +(box1[1] - box2[1])**2 + (box1[2] - box2[2])**2)**(1/2)

distances = []
for i in range(0, len(boxes)):
    for j in range(i + 1, len(boxes)):
        b1 = boxes[i]
        b2 = boxes[j]
        distances.append([distance(b1, b2), (b1, b2)])

distances.sort()

id = [i for i in range(len(boxes))]

def get_index(a):
    for i in range(0, len(boxes)):
        if a == boxes[i]:
            return i
    return -1

def connected(a, b):
    if a == b:
        return False
    ia = get_index(a)
    ib = get_index(b)
    if id[ia] == id[ib] and id[ia] != -1:
        return True
    return False

for d in distances:
    a = d[1][0]
    b = d[1][1]
    if not connected(a, b):
        ia = get_index(a)
        ib = get_index(b)
        rewr = [id[ib]]
        while len(rewr) > 0:
            r = rewr.pop()
            for i in range(0, len(id)):
                if id[i] != -1 and id[i] == r:
                    rewr = rewr + [id[i]] 
                    id[i] = id[ia]

        id[ib] = id[ia]
        if [id[0]] * len(id) == id:
            res = a[0] * b[0]
            print(res)
            break
