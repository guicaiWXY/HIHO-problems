//
// Created by wxy on 17.6.20.
//

#ifndef HIHO_PROBLEMS_ABSTRACT_PROBLEM_H
#define HIHO_PROBLEMS_ABSTRACT_PROBLEM_H

#include "../problem.h"

class AbstractProblem: public Problem{
public:
    AbstractProblem() {}
    ~AbstractProblem() {}
    int run(){ return -1;}
    int run(int, char **) { return -1;}
    int test() { return -1;}
};
#endif //HIHO_PROBLEMS_ABSTRACT_PROBLEM_H
