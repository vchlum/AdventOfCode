import z3
input_file = '10.input'
lines = []
config = []
with open(input_file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        indicator = ()
        buttons = []
        for l in line.split():
            if l[0] == '(':
                buttons.append([int(x) for x in l[1:-1].split(',')])
            if l[0] == '{':
                joltage = [int(x) for x in l[1:-1].split(',')]
        config.append([joltage, buttons])

res = 0
for conf in config:
    o = z3.Optimize()
    x = [z3.Int(f"x{i}") for i in range(len(conf[1]))]
    for xi in x:
        o.add(xi >= 0)
    eqs = []
    for i in range(len(conf[0])):
        j = [k for k in range(len(conf[1])) if i in conf[1][k] ]
        e = [x[xi] for xi in range(len(x)) if xi in j]
        eq = e[0]
        for k in range(1, len(e)):
            eq += e[k] 
        f = conf[0][i] == eq
        o.add(f)
    obj = x[0]
    for i in range(1, len(x)):
        obj += x[i]
    o.minimize(obj)
    o.check()
    model = o.model()
    res += model.evaluate(obj).as_long()
print(res)
