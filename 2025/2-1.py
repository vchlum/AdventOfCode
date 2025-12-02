input_file = '2.input'
input = []

def check_num(n):
    [l, r] = [n[:len(n)//2], n[len(n)//2:]]
    if l == r:
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
