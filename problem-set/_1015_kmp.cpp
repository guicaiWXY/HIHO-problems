//
// Created by 11206 on 2017/6/23.
//

#include "_1015_kmp.h"
#include <cstdio>

int N;
char pattern[20][10000];
char input[20][1000000];
char next[10000];

void get_currence(int i) {
    char *pat = pattern[i];
    char *in = input[i];
    /*
     * 1. construct a <next> array
     * 2. scan input according to <next>
     * */
    // TODO
}

int _1015_kmp::run() {
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; ++i) {
        scanf("%s", pattern[i]);
        getchar();
        scanf("%s", input[i]);
        getchar();
    }
    for (int i = 0; i < N; ++i) {
        get_currence(i);
    }

    return 0;
}
