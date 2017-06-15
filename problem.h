//
// Created by wxy on 17.6.15.
//

#ifndef HIHO_PROBLEMS_PROBLEM_H
#define HIHO_PROBLEMS_PROBLEM_H


class Problem {
public:
    virtual int run(int argc, char**argv) = 0;
    virtual int run() = 0;
    virtual int test() = 0;
};


#endif //HIHO_PROBLEMS_PROBLEM_H
