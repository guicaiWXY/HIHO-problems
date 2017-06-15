//
// Created by wxy on 17.6.15.
//

#include "week154.h"
//using namespace std;
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
        int j;

        for (j=0; j < N; j++) {
            scanf("%d %d %d", x+j, y+j, r+j);
            getchar();
        }
        if(judge(N)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int week154::judge(int N) {
    int i = 0;
    // define a structure to store already identified intersected circles
    vector<vector<int>> klasses;
    int indices[1000];
    memset(indices, -1, sizeof(int) * 1000);

    for (; i < N; i++) {
        int j = i-1;
        for (; j >= 0; j--) {
            if (INTERSECTED(i,j)) {
                if (indices[i] >= 0) {
                    // merge
                }
            }
        }
    }
}
