input_file = '5.input'
lines = []

with open(input_file, 'r') as f:
    lines = f.readlines()

ranges = []
ingredients = []
for line in lines:
    l = line.split("-")
    if len(l) == 2:
        [min,max] = [int(l[0]), int(l[1])]
        ranges += [[min,max]]

    if len(l) == 1 and l[0].strip() != "":
        ingredients.append(int(l[0]))

ranges = sorted(ranges, key=lambda x: x[0])

merged = []
for r in ranges:
    last = len(merged) - 1
    if merged == [] or merged[last][1] < r[0]:
        merged.append(r)
    else:
        merged[last] = [merged[last][0], merged[last][1] if merged[last][1] > r[1] else r[1]]

res = 0
for r in merged:
    res += len(range(r[0], r[1]+1))
print(res)
