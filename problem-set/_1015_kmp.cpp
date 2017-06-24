//
// Created by 11206 on 2017/6/23.
//

#include "_1015_kmp.h"
#include "../util/debug.h"
#include <cstdio>
#include <cstring>

int N;
char pattern[20][10000];
char input[20][1000000];
int next[10001];

void compute_prefix(int *next, char *p)
{
    int     i, n, k;

    n = strlen(p);
    next[1] = next[0] = 0;
    k = 0;      /* 第i次迭代开始之前，k表示next[i-1]的值 */
    for (i = 2; i <= n; i++) {
        for (; k != 0 && p[k] != p[i-1]; k = next[k]);
        if (p[k] == p[i-1]) k++;
        next[i] = k;
    }
}

void kmp_match(char *text, char *p, int *next)
{
    int     m, n, s, q, cnt=0;

    m = strlen(p);
    n = strlen(text);
    q = s = 0;  /* q表示上一次迭代匹配了多少个字符，
                   s表示这次迭代从text的哪个字符开始比较 */
    while (s < n) {
        for (q = next[q]; q < m && p[q] == text[s]; q++, s++);
        if (q == 0) s++;
        else if (q == m) {
//            printf("pattern occurs with shift %d\n", s-m);
            cnt++;
        }
    }
    printf("%d\n", cnt);
}

void construct_next(char *patt, int len) {
    // TODO
    next[0] = -1;
    next[1] = 0;
    for (int i = 1; i < len; i++) {
        int last_next = next[i];
        while (patt[i] != patt[last_next]) {
            last_next = next[last_next];
            if (last_next < 0) {
                break;
            }
        }
        next[i+1] = last_next + 1;
//        DEBUG("next[%d]=%d ", i+1, next[i+1]);
    }
//    DEBUG("\n");
}
void get_currence(int indx) {
    char *pat = pattern[indx];
    char *in = input[indx];
    /*
     * 1. construct a <next> array
     * 2. scan input according to <next>
     * */
    int len_pattern = strlen(pat);
    long long len_input = strlen(in);
    construct_next(pat, len_pattern);
    int count = 0;
    int position = 0;
    for (long long i = 0; i < len_input; ++i) {
        while (position >= 0) {
            if (in[i] == pat[position]) {
                position ++;
                break;
            }
            else
                position = next[position];

        }
        // 1 match
        if (position == len_pattern) {
            position = next[position];
            count ++;
        }
    }
    printf("%d\n", count);
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
//        get_currence(i);
        compute_prefix(next, pattern[i]);
        kmp_match(input[i], pattern[i], next);
    }

    return 0;
}
