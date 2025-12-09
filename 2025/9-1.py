input_file = '9.input'
lines = []
coordinates = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        (x, y) = line.strip().split(',')
        coordinates.append((int(x), int(y)))
coordinates.sort()

def get_size(a, b):
    return (b[0] - a[0] + 1) * (abs(a[1] - b[1]) + 1)

output = []
for i in range(len(coordinates)):
    for j in range(i + 1, len(coordinates)):
        output.append(get_size(coordinates[i], coordinates[j]))
output.sort()
print(output[len(output) -1])
