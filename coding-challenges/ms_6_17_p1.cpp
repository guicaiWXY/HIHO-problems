//
// Created by wxy on 17.6.21.
//

#include "ms_6_17_p1.h"
#include "../util/debug.h"
#include <cmath>
#include <cstdio>

int P, Q, N;

inline int power_of_2(int l) {
    return (int)pow(2, l);
}

double got(int l, int n);
double n_got(int l, int n);
// if last query brings an item
double got(int l, int n) {
    // if enough
    // return current level
    // recursive termination
    if (n == N) {
        DEBUG("return this level:%d\n", l);
        return (double)l;
    }

    // current p
    int p = P / power_of_2(n);
    if (p == 0) {
        double right = n_got(l+1, n);
        DEBUG("p=0, return right=%lf * 100\n", right);
        // just right calculated
        return right;
    }
    double left = got(l+1, n+1);
    double right = n_got(l+1, n);
    DEBUG("return leftnode left=%lf * %d right=%lf * %d\n", left, p, right, 100-p);
    return (left * (double)p + right * (100.0 - p)) / 100.0;
}

// if last query doesn't bring an item
double n_got(int l, int n) {
    // l: current level#
    // n: current item#
    int p = P / power_of_2(n) + Q;
    if (p >= 100) {
        p = 100;
        // add left
        double left = got(l+1, n+1);
        DEBUG("p=100, return left=%lf * 100\n", left);
        return left;
    }
    double left = got(l+1, n+1);
    double right = n_got(l+1, n);
    DEBUG("return rightnode left=%lf * %d right=%lf * %d\n", left, p, right, 100-p);
    return (left * (double)p + right * (100.0 - p)) / 100.0;
}

double calculate_recursive() {
    return (got(1, 1) * (double)P + n_got(1, 0) * (100.0 - P)) / 100.0;
}

/*
 * E(i) for expected steps to get i'th legendary item
 *      since you've got i-1'th legendary item
 * because E(i) is independent of  E(i+1)
 * E = E(1) + E(2) + E(3) + ... + E(N)
 *
 * */
double E[101];
int f[101];

// compute E with start probability prob
double expection(int prob) {
    if (prob == 100) {
        return 1.0;
    }

    f[0] = prob;
    int x = (100 - prob + Q - 1) / Q;
    DEBUG("prob=%d x=%d  ",prob, x);
    for (int i = 1; i < x; i++) {
        f[i] = prob + Q;
        prob += Q;
    }
    f[x] = 100;
    double buf[101];
    buf[x] = x+1;
    DEBUG("buf[%d] = %.4lf  ", x, buf[x]);
    for (int i = x-1; i >= 0; --i) {
        buf[i] = ((double)(i+1) * f[i] + (100 - f[i]) * buf[i+1]) / 100.0;
        DEBUG("buf[%d] = %.4lf  ", i, buf[i]);
    }
    DEBUG("\n");
    return buf[0];
}

double calculate_dynamic_programming() {
    double e = 0.0;
    // prepare E: double[101]
    for (int i = 0; i <= 100; ++i) {
        E[i] = expection(i);
    }
    // accumulate exception
    for (int i = 1; i <= N; ++i) {
        int prob = P / power_of_2(i-1);
        e += E[prob];
    }
    return e;
}

int ms_6_17_p1::run() {
    scanf("%d %d %d", &P, &Q, &N);
    getchar();
//    P = 50;
//    Q = 2;
//    N = 2000;
//    double result = calculate_recursive();
    double result_1 = calculate_dynamic_programming();

//    printf("%.2lf\n", result);
    printf("%.2lf\n", result_1);
    return 0;
}
