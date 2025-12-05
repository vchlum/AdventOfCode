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

fresh = 0
for i in ingredients:
    for [min, max] in ranges:
        if i >= min and i <= max:
            fresh += 1
            break
print(fresh)
