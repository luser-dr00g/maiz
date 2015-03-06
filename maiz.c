#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *charclass[256];

void defcharclass(char *str){
    char *end;
    int num;
    num = strtol(str, &end, 10);
    if (isspace(end[0])) ++end;
    charclass[num] = strdup(end);
}

typedef struct mach {
    char *opp;
    char class;
    int n;
    struct mach *link[3];
} mach;

mach fail = { 0 };

char op[] =  "a" "i" "j" "r" "c" "n" "m" "q" "x" "\0";
int del[] = { 1   1   1   2   2   2   3   1   1 };

mach buildmach(char *str){
    mach m;
    char *opp;
    char *end;
    int code;
    int arity;
    int i;
    opp = strchr(op,str[0]);
    if (!opp) return fail;
    while (str && isspace(str[0])) ++str;
    code = opp-op;
    arity = del[code];
    m.opp = opp;
    m.class = strtol(str, &end, 10);
    str = end;
    while (str && isspace(str[0])) ++str;
    m.n = arity;
    for (i=0;i<arity;i++){
        m.link[i] = malloc(sizeof m);
        *m.link[i] = buildmach(str);
    }
}

int runmach(mach m, char *input){
}

void process(char *str){
    if (str[0]==';') return;
    if (isdigit(str[0])){
        defcharclass(str);
        return;
    }
    while (str && isspace(str[0])) ++str;
    if (islower(str[0])){
        mach m = buildmach(str);
        return;
    }
    return;
}

int main(int argc, char **argv){
    int nbuf = 100;
    char *buf = malloc(nbuf);
    while(fgets(buf, nbuf, stdin))
        process(buf);
    return 0;
}

