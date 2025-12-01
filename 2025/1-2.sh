cat 1.input | awk 'BEGIN {for (i = 0; i < 100; i++) dial[i]=0; pos=50;} {
    dir=gensub(/([LR]+).*/, "\\1","g", $1);
    num=gensub(/[LR]+([0-9]+)$/, "\\1","g", $1);
    posprev = pos;
    click = num % 100;
    click0 = int(num/100)
    if (dir == "L") {
        pos = pos - click;
        if (pos < 0) {pos = 100 + pos; if (pos != 0 && posprev != 0) click0 += 1;}
        dial[pos]+=1;
    }
    if (dir == "R") {
        pos = pos + click;
        if (pos > 99) {pos = pos - 100; if (pos != 0 && posprev != 0) click0 += 1;}
        dial[pos]+=1;
    }
    dial[0]+=click0;
} END {printf(dial[0]"\n");}'