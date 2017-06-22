//
// Created by wxy on 17.6.22.
//
#include <cstdio>
#include <iostream>
#include <cstring>

#include "ms_6_17_p2.h"
#include "../util/debug.h"

int K, N, M;
int len[100];           // l = M
int p[101];             // l = N
int is_leaf[101];       // l = N
int nodes[101][101];    // l1 = *, l2 = M
int dis[100][100];      // l1 = K, l2 = K
int leaf[100];          // l = K

using namespace std;

void print_info() {
    for (int i = 0; i < M; i++) {
        DEBUG("line %d: ");
        for (int j = 0; j < len[i]; j++) {
            DEBUG("%d ", nodes[i][j]);
        }
        DEBUG("\n");
    }
}

int find_level(int n) {
    int i;
    for (i = 0; i < M; i++) {
        if (nodes[i][0] > n)
            break;
    }
    return i-1;
}
void restore() {
    if (len[0] == 1)
        p[nodes[0][0]] = 0;
    if (N == 1) {
        printf("0\n");
        return;
    }
    for (int i = M-1; i >= 0; --i) {
        // deal with line i
        for (int j = 0; j < len[i]; ++j) {
            // deal with [i,j]
            int node = nodes[i][j];
            if (p[node] != 0) {
                // has been restored
                continue;
            }
            if (is_leaf[node]) {
                // if leaf: add to a parent
                int level = find_level(node);
                if (j == 0) {
                    // attach to last level's most left node
                    int last_level = level-1;
                    int last_len = len[last_level];
                    int index;
                    int father = -1;
                    for (index = 0; index < last_len; ++index ) {
                        father = nodes[last_level][index];
                        if (!is_leaf[father] && p[father] != 0) {
                            break;
                        }
                    }
                    p[node] = nodes[last_level][index];
                }
            }
        }
    }
}

int ms_6_17_p2::run() {
    cin >> N >> M >> K;
    getchar();
    for (int i = 0; i < M; ++i) {
        cin >> len[i];
    }
    getchar();
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < len[i]; ++j) {
            cin >> nodes[i][j];
        }
        getchar();
    }
    for (int i = 0; i < K; ++i) {
        cin >> leaf[i];
        is_leaf[leaf[i]] = 1;
    }
    getchar();
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            cin >> dis[i][j];
        }
        getchar();
    }
    memset(p, 0, sizeof(int) * 101);

    restore();
    return 0;
}