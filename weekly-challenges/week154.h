//
// Created by wxy on 17.6.15.
//
#ifndef HIHO_PROBLEMS_WEEK154_H
#define HIHO_PROBLEMS_WEEK154_H

#include "../problem.h"

struct interval {
    int lower;
    int upper;
//    int root;
};
class week154: public Problem {
    // need to publicly inherit from Problem
public:
    int run(int, char **) { return 0;}
    int run();
    int test() { return 0;}

private:
    int judge(int N);
    void quick_union(int i, int j);
    int find(int i);
};

#endif //HIHO_PROBLEMS_WEEK154_H
