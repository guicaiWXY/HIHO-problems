//
// Created by wxy on 17.6.15.
//

// Get Wrong Answer now.
// TODO: don't know why...

#include <vector>
#include <cstring>
#include "week154.h"
#include <cstdio>

#define SQR(__x) ((__x) * (__x))
#define INTERSECTED(i, j) (SQR(x[(i)] - x[(j)]) + SQR(y[(i)] - y[(j)])) <= SQR(r[(i)] + r[(j)])

int x[1000];
int y[1000];
int r[1000];
int indices[1000];
int size[1000];
int count;
int H;

int week154::run() {
    int n;
    scanf("%d", &n);
    getchar();
    int i;
    int width;
    int height;
    int N;

    for (i=0; i < n; i++) {
        scanf("%d %d %d", &width, &height, &N);
        getchar();
        H = height;
        int j;

        for (j=0; j < N; j++) {
            scanf("%d %d %d", x+j, y+j, r+j);
            getchar();
        }
        if(judge(N) == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}

// get N as number of radar zones
// judge if any component(of the connection graph)'s upper/lower bounds cover H
int week154::judge(int N) {
    int i = 0;
    count = N;
    int checked[1000];
    memset(checked, -1, sizeof(int) * 1000);
    // define a structure to store already identified intersected circles
    for (i = 0; i < N; i++) {
        indices[i] = i;
        size[i] = 1;
    }

    // construct connection graph
    for (i = 0; i < N; i++) {
        int j = i-1;
        for (; j >= 0; j--) {
            if (INTERSECTED(i,j)) {
                // merge
                quick_union(i, j);
            }
        }
    }

    // judge any set's height > H
    std::vector<struct interval> intervals;
    for (i = 0; i < N; i++) {
        int root = find(i);

        int up = y[i] + r[i];
        int lo = y[i] - r[i];
        if (checked[root] >= 0) {
            // update this set's interval
            struct interval & original_itv = intervals[checked[root]];
            if (lo < original_itv.lower)
                original_itv.lower = lo;
            if (up > original_itv.upper)
                original_itv.upper = up;

        } else {
            // not in intervals, add this interval
            checked[root] = intervals.size();
            struct interval itv = {lo, up};
            intervals.push_back(itv);
        }
        struct interval & new_itv = intervals[checked[root]];
        if (new_itv.upper >= H && new_itv.lower <= 0) {
            return -1;
        }
    }
    return 0;
}

void week154::quick_union(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i == root_j) return;
    if (size[root_i] < size[root_j]) {
        indices[root_i] = root_j;
        size[root_j] += size[root_i];
    } else {
        indices[root_j] = root_i;
        size[root_i] += size[root_j];
    }
    count--;
}

int week154::find(int q) {
    while (q != indices[q]) {
        // compass the path
        indices[q] = indices[indices[q]];
        q = indices[q];
    }
    return q;
}
