//
// Created by wxy on 17.6.15.
//

// Get Wrong Answer now.
// TODO: don't know why...

#include <vector>
#include <cstring>
#include "week154.h"
#include <cstdio>

//#define SQR(__x) ((__x) * (__x))
//#define INTERSECTED(i, j) ((long long)SQR(x[(i)] - x[(j)]) + SQR(y[(i)] - y[(j)])) <= (long long)SQR(r[(i)] + r[(j)])

int x[1000];
int y[1000];
int r[1000];
int indices[1002];
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
        judge(N);
    }
    return 0;
}

void dump(int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");
}
long long SQR(int x) {
    return ((long long)x) * x;
}

// get N as number of radar zones
// judge if any component(of the connection graph)'s upper/lower bounds cover H
int week154::judge(int N) {
    int i = 0;
    // define a structure to store already identified intersected circles
    for (i = 0; i < N+2; i++) {
        indices[i] = i;
    }

    // construct connection graph
    for (i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if ((long long)(r[i] + r[j]) * (r[i] + r[j]) >= (long long)(x[i] - x[j]) * (x[i] - x[j]) + (long long)(y[i] - y[j]) * (y[i] - y[j]))
            {
                // merge
                quick_union(i, j);
            }
        }
    }
//    dump(N+2);

    // judge any set's height > H
    for (i = 0; i < N; ++i) {
        if (y[i] <= r[i]) {
            // lower bound class
            quick_union(i, N);
        }
        // bug here!!!
        // can not use else if because r can be large enough
        if (y[i] >= H - r[i])
            quick_union(i, N+1);
    }

//    dump(N+2);
    if (find(N) == find(N+1))
        printf("NO\n");
    else
        printf("YES\n");

    return 0;
}

void week154::quick_union(int i, int j) {
//    int root_i = find(i);
//    int root_j = find(j);
//    if (root_i == root_j) return;
//    if (size[root_i] < size[root_j]) {
//        indices[root_i] = root_j;
//        size[root_j] += size[root_i];
//    } else {
//        indices[root_j] = root_i;
//        size[root_i] += size[root_j];
//    }
//    count--;
    indices[find(i)] = find(j);
}

int week154::find(int q) {
    while (q != indices[q]) {
        // compass the path
        indices[q] = indices[indices[q]];
        q = indices[q];
    }
    return q;
}
