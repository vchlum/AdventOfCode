cat 1.input | awk 'BEGIN {for (i = 0; i < 100; i++) dial[i]=0; pos=50;} {
    dir=gensub(/([LR]+).*/, "\\1","g", $1);
    num=gensub(/[LR]+([0-9]+)$/, "\\1","g", $1);
    num = num % 100;
    if (dir == "L") {
        pos = pos - num;
        if (pos < 0) pos = 100 + pos;
        dial[pos]+=1;
    }
    if (dir == "R") {
        pos = pos + num;
        if (pos > 99) pos = pos - 100;
        dial[pos]+=1;
    }
} END {printf(dial[0]  "\n");}'