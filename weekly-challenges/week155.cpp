//
// Created by wxy on 17.6.23.
//

/*
 * Problem 1309: Task Distribution
 * Description
 *  Given N tasks with starting time and end time ( S1, E1 ), ( S2, E2 ), ..., ( SN, EN ), try to distribute and finish them with the minimum number of machines.
 *  At the same time there is at most one running task on each machine and one task should keep running on one machine.
 *
 * Input
 *  The first line contains 1 integer N (1 ≤ N ≤ 100000), the number of tasks.
 *  The following N lines each contain 2 integers Si and Ei，(0 ≤ Si < Ei ≤ 1000000000), the starting and end time of i-th task.
 *
 * Output
 *  The minimum number of machine needed.
 * */
#include "week155.h"
#include "../util/debug.h"
#include <cstdio>
#include <algorithm>
struct time {
    int t;
    int type;
};
bool compare(const struct time &a, const struct time &b) {
    if (a.t == b.t)
        return b.type < a.type;
    return a.t < b.t;
}

int week155::run() {
    int N = 0;  // 1 ~ 100000
    struct time timestamp[200000];
    scanf("%d", &N);
    getchar();
    int ts, te;
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &ts, &te);
        timestamp[2 * i] = {ts, 0};
        timestamp[2 * i + 1] = {te, 1};
        getchar();
    }

    // NOTICE: parameter 'last' should > end_item (timestamp[2N-1])
    std::sort(timestamp, timestamp + 2 * N, compare);
    int n = 0;      // current # of intervals at this time
    int MAX = 1;
    for (int i = 0; i < 2*N; ++i) {
        DEBUG("t[%d]={%d,%c} ", i, timestamp[i].t, timestamp[i].type ? 'e' : 's');
        if (timestamp[i].type == 0)
            n++;
        else
            n--;
        if (n > MAX)
            MAX = n;
    }
    printf("%d\n", MAX);
    return 0;
}