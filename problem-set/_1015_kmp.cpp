//
// Created by 11206 on 2017/6/23.
//

#include "_1015_kmp.h"
#include "../util/debug.h"
#include <cstdio>
#include <cstring>
#include <string>

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

void construct_next1(char *pat, int n) {
    next[0] = -1;
    for (int i = 1; i <= n; ++i) {
        int p = next[i-1];
        while (p != -1) {
            if (pat[i-1] == pat[p]) {
                next[i] = p + 1;
                break;
            }
            p = next[p];
        }
        if (p == -1) {
            next[i] = 0;
        }
    }
}
void construct_next(char *patt, int len) {
    next[0] = -1;
    next[1] = 0;
    int k = 0; // k = next[1]
    for (int i = 2; i <= len; i++) {
        while (patt[i-1] != patt[k]) {
            k = next[k];
            if (k == 0)
                break;
        }
        if (patt[i-1] == patt[k])
            k++;
        next[i] = k; // next[i+1] judge from this k
    }
}

void get_currence(int indx) {
    char *pat = pattern[indx];
    char *in = input[indx];
    /*
     * 1. construct a <next> array
     * 2. scan input according to <next>
     * */
    int len_pattern = strlen(pat);
    int len_input = strlen(in);
//    construct_next(pat, len_pattern);
    construct_next1(pat, len_pattern);
    DEBUG("%s\n", pat);
    for (int i = 0; i < len_pattern+1; ++i) {
        DEBUG("next[%d]=%d ", i, next[i]);
    }
    DEBUG("\n");
/*
    int position = 0;
    int count = 0;
    for (int i = 0; i < len_input; ) {
        position = next[position];
//        while (position > 0) {
//            if (in[i] == pat[position]) {
//                position ++;
//                break;
//            }
//            else
//                position = next[position];

//        }
        while (position < len_pattern && in[i] == pat[position]) {
            ++i;
            ++position;

        }
        if (position == 0) {
            ++;
        }
        if (pat != in[i]) {

        }
        // 1 match
        if (position == len_pattern) {
            position = next[position];
            count ++;
        }
    }
*/
    int p, i, j, cnt;
    i = j = cnt = 0;
    // i for compared chars in text
    // j for current matched chars in pattern and text
    for (; i < len_input;) {
        // p for current index to compare starting from i-j
        if (j == -1) {
            // even the first char doesn't match
            j = 0;
            i++;
        }
        p = j;
        for (; p < len_pattern; ++p) {
            // find the first index p not match
            if (in[i + p - j] != pat[p])
                break;
        }
        // move i to i-j+p
        i = i + p - j;
        j = next[p];
        if (p == len_pattern)
            cnt++;
    }
    printf("%d\n", cnt);
}

int _1015_kmp::run() {
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; ++i) {
        scanf("%s", pattern[i]);
        getchar();
        scanf("%s", input[i]);
        getchar();
        // NOTICE: should calculate at once after reading two lines
        get_currence(i);
    }

    return 0;
}
