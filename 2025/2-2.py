input_file = '2.input'
input = []

def check_num(n):
    for i in range (1, len(n)):
        s = [n[x:x+i] for x in range(0,len(n),i)]
        if s == [s[0]] * len(s):
            return True
    return False

with open(input_file, 'r') as f:
    input = f.readline().split(',')

nums = []
for i in input:
    [start, stop] = i.split('-')
    for j in range(int(start), int(stop) + 1):
        nums.append(j)

res = 0
for n in nums:
    if check_num(str(n)):
        res += n

print(res)
