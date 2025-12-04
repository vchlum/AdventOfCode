cat 2.input | awk 'function abs(x){return ((x < 0) ? -x : x)}
BEGIN {res = 0} {
incr = $1 < $2
safe = 1
for (i = 1; i < NF; i++) {
    diff = abs($i - $(i+1))
    if (diff > 3 || diff < 1) {safe = 0; break;}
    if (incr && $i > $(i+1)) {safe = 0; break;}
    if ((!incr) && $i < $(i+1)) {safe = 0; break;}
}
if (safe == 1) res ++
} END {print res}'