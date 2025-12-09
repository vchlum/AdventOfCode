input_file = '9.input'
lines = []
coordinates = []
polygon = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        (x, y) = line.strip().split(',')
        coordinates.append((int(x), int(y)))
        polygon.append((int(x), int(y)))
coordinates.sort()

def get_size(a, b):
    return (b[0] - a[0] + 1) * (abs(b[1] - a[1]) + 1)

def is_valid(a, b):
    for i in range(len(polygon)):
        if i == len(polygon) - 1:
            A = polygon[0]
            B = polygon[i]
        else:
            A = polygon[i]
            B = polygon[i + 1]
        ok = False
        if min(a[1], b[1])>= A[1] and min(a[1], b[1]) >= B[1]:
            ok = True
        if min(a[0], b[0])>= A[0] and min(a[0], b[0]) >= B[0]:
            ok = True
        if max(a[0], b[0]) <= A[0] and max(a[0], b[0]) <= B[0]:
            ok = True
        if max(a[1], b[1]) <= A[1] and max(a[1], b[1]) <= B[1]:
            ok = True
        if not ok:
            return False
    return True

output = []
for i in range(len(coordinates)):
    for j in range(i + 1, len(coordinates)):
        if is_valid(coordinates[i], coordinates[j]):
            output.append(get_size(coordinates[i], coordinates[j]))
output.sort()
print(output[len(output) -1])
