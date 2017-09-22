//
// Created by wxy on 17.6.15.
//

#include <cstdio>
#include "problem.h"
//#include "weekly-challenges/week154.h"
//#include "weekly-challenges/week155.h"
//#include "weekly-challenges/week156.h"
//#include "weekly-challenges/week157.h"
//#include "weekly-challenges/week154_AC1.h"
//#include "coding-challenges/ms_6_17_p1.h"
//#include "coding-challenges/ms_6_17_p2.h"
#include "coding-challenges/ms_6_17_p3.h"
#include "coding-challenges/ms_6_17_p4.h"
#include "problem-set/_1014_trie_tree.h"
//#include "problem-set/_1015_kmp.h"
//#include "problem-set/_1032_longest_palindromic_substring.h"

int main() {
//    Problem *problem = new week154_AC1();
//    Problem *problem = new week154();
//    Problem *problem = new week155();
//    Problem *problem = new week157();
    Problem *problem = new _1014_trie_tree();
//    Problem *problem = new ms_6_17_p1();
//    Problem *problem = new ms_6_17_p4();
    if (int res = problem->run()) {
//    if (int res = problem->test()) {
        printf("Problem not passed.\n");
    } else
        printf("Done");
}