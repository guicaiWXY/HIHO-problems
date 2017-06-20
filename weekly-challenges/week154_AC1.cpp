//
// Created by wxy on 17.6.20.
//

#include "week154_AC1.h"
#include <cstdio>

const int MAXN = 1005;
int W, H, N, father[MAXN], x[MAXN], y[MAXN], r[MAXN];

int findFather(int x) {
	return father[x] == x ? x : father[x] = findFather(father[x]);
}

void Union(int x, int y) {
	father[findFather(x)] = findFather(y);
}

int week154_AC1::run() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &W, &H, &N);
		for (int i = 0; i < N; ++i)
			scanf("%d%d%d", x + i, y + i, r + i);
		for (int i = 0; i <= N + 1; ++i) father[i] = i;
		for (int i = 0; i < N; ++i)
			for (int j = i + 1; j < N; ++j)
				if ((long long)(r[i] + r[j]) * (r[i] + r[j]) >= (long long)(x[i] - x[j]) * (x[i] - x[j]) + (long long)(y[i] - y[j]) * (y[i] - y[j]))
					Union(i, j);

		for (int i = 0; i < N; ++i) {
			if (y[i] <= r[i])
				Union(i, N);
			if (H - y[i] <= r[i])
				Union(i, N + 1);
		}
		printf("%s\n", findFather(N) == findFather(N + 1) ? "NO" : "YES");
	}
	return 0;
}