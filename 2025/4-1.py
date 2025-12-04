input_file = '4.input'
lines = []

with open(input_file, 'r') as f:
    lines = f.readlines()

grid = [[0 for x in range(len(lines[0]))] for y in range(len(lines))]
for x in range(0, len(lines)):
    line = lines[x].strip()
    for y in range(0, len(line)):
        grid[x][y] = line[y]

def check(x,y):
    if grid[x][y] != '@':
        return 0
    
    positions = [1, 0, -1]
    free = [x + i < 0 or x + i >= len(grid) or y + j < 0 or y + j>= len(grid[i]) or grid[x + i][y + j] != '@' for i in positions for j in positions]
    return sum(free) > 4

res = 0
for x in range(0, len(grid)):
    for y in range(0, len(grid[x])):
        res += check(x, y)

print(res)
