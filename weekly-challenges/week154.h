//
// Created by wxy on 17.6.15.
//
#ifndef HIHO_PROBLEMS_WEEK154_H
#define HIHO_PROBLEMS_WEEK154_H

#include "../problem.h"
#include <cstdio>

#define SQR(x) ((x) * (x))
#define INTERSECTED(i, j) (SQR(x[(i)] - x[(j)]) + SQR(y[(i)] - y[(j)])) <= SQR(r[(i)] + r[(j)])

int x[1000];
int y[1000];
int r[1000];

class week154: public Problem {
    // need to publicly inherit from Problem
public:
    int run();

private:
   int judge(int N);
};

#endif //HIHO_PROBLEMS_WEEK154_H
