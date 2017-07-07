//
// Created by wxy on 17.7.6.
//

#include "week156.h"
#include "../util/debug.h"
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

static char map[50][50];
static bool visited[50][50] = {false};
static int N;
static int M;
static int fx[4] = {-1, 0, 1, 0};
static int fy[4] = {0, 1, 0, -1};

struct point {
    int x;
    int y;
};
struct island {
    vector<struct point> land;
    bool area_equal;
    bool shape_equal;
};
struct island buf;
vector<struct island> area;

void dfs(int n, int m) {
    if (0 <= n && n < N && 0 <= m && m < M) {
        if (map[n][m] != '#' || visited[n][m])
            return;
        visited[n][m] = true;
        buf.land.push_back({n, m});
        for (int i = 0; i < 4; i++) {
            dfs(n + fx[i], m + fy[i]);
        }
    } else
        return;
}

int week156::run() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        scanf("%s", map[i]);
        getchar();
    }
    buf.area_equal = false;
    buf.shape_equal = false;
    int land_count = 0, area_count = 0, shape_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '#' && !visited[i][j]) {
//                land_count++;
                buf.land.clear();
                // explore island's info
                dfs(i, j);
                area.push_back(buf);
            }
        }
    }
    land_count = area.size();
    for (int i = 0; i < land_count; i++) {
        struct island land_i = area[i];
        if (!land_i.area_equal) {
            area_count++;
            int size_i = land_i.land.size();
            for (int j = i+1; j < land_count; j++) {
                struct island land_j = area[j];
                if (land_j.area_equal)
                    continue;
                int size_j = land_j.land.size();
                if (size_i == size_j)
                    area[j].area_equal = true;
            }
        }
        if (!land_i.shape_equal) {
            shape_count++;
            int size_i = land_i.land.size();
            for (int j = i+1; j < land_count; j++) {
                struct island land_j = area[j];
//                if (land_j.area_equal)
//                    continue;
                int size_j = land_j.land.size();
                if (size_i == size_j) {
                    // judge if shape equals
                    bool compare = true;
                    for (int x = 1; x < size_i; x++) {
                        vector<point> il_a = (land_i.land);
                        vector<point> il_b = (land_j.land);
                        if (    (il_a[x].x - il_a[x-1].x) == (il_b[x].x - il_b[x-1].x) &&
                                (il_a[x].y - il_a[x-1].y) == (il_b[x].y - il_b[x-1].y)
                            ) {}
                        else {
                            compare = false;
                            break;
                        }
                    }
                    if (compare) {
                        area[j].shape_equal = true;
                        DEBUG("shape euqals for %d %d\n", i, j);
                    }
                }
            }
        }
        else {
            continue;
        }
    }
    cout << land_count << " " << area_count << " " << shape_count << endl ;
}
