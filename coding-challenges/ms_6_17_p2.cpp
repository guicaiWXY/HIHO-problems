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
int dis[101][101];      // l1 = K, l2 = K
int leaf[100];          // l = K
int vertical[101];
int horizontal[101];

using namespace std;

void print_info() {
    DEBUG("nodes\n");
    for (int i = 0; i < M; i++) {
        DEBUG("line %d: ", i);
        for (int j = 0; j < len[i]; j++) {
            DEBUG("%d ", nodes[i][j]);
        }
        DEBUG("\n");
    }
    DEBUG("distance\n");
    for (int i = 1; i <= N; i++) {
        DEBUG("line %d: ", i);
        for (int j = 1; j <= N ; j++) {
            DEBUG("%d ", dis[i][j]);
        }
        DEBUG("\n");
    }
    DEBUG("parent\n");
    for (int i = 1; i <= N; i++) {
        DEBUG("%d ", p[i]);
    }
    DEBUG("\n");
}

int find_left_most_nonleaf(int node, int level) {
    for (int i = 0; i < len[level]; ++i) {
        int tmp = nodes[level][i];
        if (!is_leaf[tmp] && dis[node][tmp] == 0)
            return i;
    }
}

void attach_siblings(int i, int j, int node) {
    int parent = p[node];
    // update distance with parent
    for (int k = 1; k <= N; k++) {
//        if (vertical[k] > i)
//            break;
        if (k == node || k == parent)
            continue;
        int dist = dis[k][node];
        if (dist == 0) continue;    // have not got this info
        dis[k][parent] = dist-1;
        dis[parent][k] = dist-1;
        if (dist == 2) {
            // deal with 2-distance nodes at same level
            if (vertical[k] == i) {
                DEBUG("find sibling %d %d\n", node, k);
                p[k] = parent;
            } else if (vertical[k] == i-2) {
                DEBUG("find grand parent %d %d %d\n", k, parent, node);
                p[parent] = k;
            }
        }
    }
}

void attach_to_leftmost(int i, int j, int node) {
    // level = i
    // index = j
    int last_level = i-1;
    int left_most_nonleaf = find_left_most_nonleaf(node, last_level);
    p[node] = nodes[last_level][left_most_nonleaf];

    attach_siblings(i, j, node);
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
    for (int i = M-1; i > 0; --i) {
        // deal with line i
        for (int j = 0; j < len[i]; ++j) {
            // deal with [i,j]
            int node = nodes[i][j];
            if (p[node] != 0) {
                // has been restored
                DEBUG("node %d has been restored.\n", node);
                continue;
            }
//            if (is_leaf[node]) {
                // if leaf: attach to a parent
            attach_to_leftmost(i, j, node);
//            }
            // for each node in level[i]
        }
        // for each level
    }
//    print_info();
    for (int i = 1; i <= N; ++i) {
        cout << p[i] << " ";
    }
    cout << endl;
}

int ms_6_17_p2::run() {
    memset(dis, 0, sizeof(int) * 101 * 101);
    cin >> N >> M >> K;
    getchar();
    for (int i = 0; i < M; ++i) {
        cin >> len[i];
    }
    getchar();
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < len[i]; ++j) {
            int node = 0;
            cin >> node;
            nodes[i][j] = node;
            vertical[node] = i;
            horizontal[node] = j;
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
            cin >> dis[leaf[i]][leaf[j]];
        }
        getchar();
    }
    memset(p, 0, sizeof(int) * 101);

    restore();
    return 0;
}