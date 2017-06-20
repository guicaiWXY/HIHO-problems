//
// Created by wxy on 17.6.15.
//

#include <cstdio>
#include "problem.h"
#include "weekly-challenges/week154.h"
//#include "weekly-challenges/week154_AC1.h"

int main() {
//    Problem *problem = new week154_AC1();
    Problem *problem = new week154();
    if (int res = problem->run()) {
        printf("Problem not passed.\n");
    } else
        printf("Done");
}