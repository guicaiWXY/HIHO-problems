//
// Created by 11206 on 2017/6/23.
//

#include "_1015_kmp.h"
#include <cstdio>
#include <cstring>

int N;
char pattern[20][10000];
char input[20][1000000];
char next[10000];

void construct_next() {
    // TODO

}
void get_currence(int i) {
    char *pat = pattern[i];
    char *in = input[i];
    /*
     * 1. construct a <next> array
     * 2. scan input according to <next>
     * */
    // TODO
    construct_next();
    int len_pattern = strlen(pat);
    int len_input = strlen(in);
    for (int i = 0; i < len_input; ++i) {

    }
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
