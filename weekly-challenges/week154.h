//
// Created by wxy on 17.6.15.
//
#ifndef HIHO_PROBLEMS_WEEK154_H
#define HIHO_PROBLEMS_WEEK154_H

#include "abstract_problem.h"

class week154: public AbstractProblem {
    // need to publicly inherit from Problem
public:
    week154() {}
    ~week154() {}
    int run();

private:
    int judge(int N);
    void quick_union(int i, int j);
    int find(int i);
};

#endif //HIHO_PROBLEMS_WEEK154_H
