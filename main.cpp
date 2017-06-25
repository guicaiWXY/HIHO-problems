//
// Created by wxy on 17.6.15.
//

#include <cstdio>
#include "problem.h"
//#include "weekly-challenges/week154.h"
#include "weekly-challenges/week155.h"
//#include "weekly-challenges/week154_AC1.h"
//#include "coding-challenges/ms_6_17_p1.h"
#include "coding-challenges/ms_6_17_p2.h"
#include "problem-set/_1015_kmp.h"

int main() {
//    Problem *problem = new week154_AC1();
//    Problem *problem = new week154();
//    Problem *problem = new ms_6_17_p1();
//    Problem *problem = new ms_6_17_p2();
    Problem *problem = new week155();
    if (int res = problem->run()) {
        printf("Problem not passed.\n");
    } else
        printf("Done");
}