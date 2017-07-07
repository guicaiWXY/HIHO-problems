//
// Created by wxy on 17.7.7.
//

#include "week157.h"
#include "../util/debug.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

struct BigNum {
    char fuck[100];
    int size;

    BigNum(int x) {
        if (x == 0)
            size = 0;
        else if (x < 10) {
            fuck[0] = x - '0';
            size = 1;
        }
    }

    friend void multiply(const int k) {

    }
};

/*
 *  X = x1*1/2 + x2*1/4 + ... + xi*(1/2)^i
 *  judge xi = {0,1} for each i
 * */
void buggy_solution(char *X, char *bin_frac) {
    int len = strlen(X);
    int remainder = 0;
    int comp = 1;
    if (X[len - 1] != '5') {
        printf("NO\n");
        return;
    }
    for (int j = 2; j < len; j++) {
        int x = X[j] - '0';
        // FIXME: how to deal with comp too large (such as 5^99) ?
        if (remainder + x >= comp * 5) {
            remainder = remainder + x - comp * 5;
            remainder *= 10;
            bin_frac[j] = '1';
        } else {
            //
            remainder = remainder + x;
            remainder *= 10;
            bin_frac[j] = '0';
        }
        comp *= 5;
    }
    bin_frac[len] = 0;
    if (remainder)
        printf("NO\n");
    else
        printf("%s\n", bin_frac);
}

/*
 * continously X 2 and retrieve the head 1
 * */
void solution(char *X, char *bin_frac) {
    int len = strlen(X);
    for (int i = 0; i < len; i++) {
        // multiply by 2
        int carry = 0;
        if (X[len-i-1] != '5') {
            printf("NO\n");
            return;
        }
        for (int j = len - i -1; j >= 0; j--) {
            int x = X[j]-'0';
            X[j] = ((x * 2 + carry) % 10) + '0';
            if (x >= 5)
                carry =  1;
            else
                carry = 0;
        }
        bin_frac[i+2] = carry+'0';
    }
    bin_frac[len+2] = 0;
    printf("%s\n", bin_frac);
}
int week157::run() {
    int N;
    cin >> N;
    char X[10][105];
    char bin_frac[105] = {0};
    bin_frac[0] = '0';
    bin_frac[1] = '.';

    for (int i = 0; i < N; i++) {
        scanf("%s", X[i]);
        solution(X[i]+2, bin_frac);
    }
    return 0;
}