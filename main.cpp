//
// Created by wxy on 17.6.15.
//

#include <cstdio>
#include "problem.h"
#include "weekly-challenges/week154.h"
int main() {
    Problem *week_154 = new week154();
    if (int res = week_154->run()) {
        printf("Problem not passed.\n");
    } else
        printf("Done");
}