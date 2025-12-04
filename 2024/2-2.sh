cat 2.input | awk 'function abs(x){return ((x < 0) ? -x : x)}
BEGIN {res = 0} {
really_safe = 0
for (s = 0; s <= NF; s++){
    safe = 1
    a = $1
    b = $2
    if (s == 1) {a = $2; b = $3}
    if (s == 2) {a = $1; b = $3}
    incr = a < b

    for (i = 1; i < NF; i++) {
        a = $i
        b = $(i+1)

        if (s > 0 && i == s) continue
        if (s > 0 && i+1 == s) {
            if (i+2 == NF+1) continue
            b = $(i+2)
        }

        diff = abs(a - b)
        if (diff > 3 || diff < 1) {safe = 0; break;}
        if (incr && a > b) {safe = 0; break;}
        if ((!incr) && a < b) {safe = 0; break;}
    }
    if (safe) {really_safe = 1; break;}
}
if (really_safe == 1) res ++
} END {print res}'