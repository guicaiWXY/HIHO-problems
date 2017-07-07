//
// Created by wxy on 17.7.5.
//

#include "ms_6_17_p4.h"
#include "../util/debug.h"
#include <cmath>
#include <cstdio>

//#include <stack>
static const long long MOD = 1000000007;

long long permutation(int n, int k) {
    // C n+k-1 k
    if (n == 1) {
        return 1;
    }

    long long perm = 1;
    int N = n + k;
    for (int i = n; i < N; i++)
        perm = perm * i % MOD;
    for (int i = k; i > 1; i--)
        perm /= i;
//    DEBUG("per(%d, %d)= %d\n", n, k, perm);
    return perm % MOD;
}

long long DP_solve(int size, int left, int *pos_stack, int len) {
    long long result1 = 1, result2 = 1;
    /*
     * Step 1: deal with redundant right parentheses
     * */
    if (left == 0);
    else {

        // construct f1[N1][N1] f2[N2][N2] N1=left N2=size-left
        int **f1 = new int *[left];
        for (int i = 0; i < left; i++) {
            f1[i] = new int[left];
        }

//        DEBUG("left = %d\n", left);
        // DP f1(n, k) = Xn * f1(n-1, k-1) + f(n-1, k)
        // f(n, k) for permutation number for adding k+1 '(' in first n+1 parentheses
        for (int j = 0, n1 = pos_stack[0] / 2 + 1; j < left; j++) {
            f1[0][j] = permutation(n1, j + 1);
        }
        for (int i = 1; i < left; i++) {
            for (int j = i; j < left; j++) {
                int n1 = (pos_stack[i] - pos_stack[i - 1] + 1) / 2;
                f1[i][j] = ((n1 * f1[i - 1][j - 1] % MOD) + f1[i - 1][j]) % MOD;
            }
        }

//        DEBUG("f1:\n");
//        for (int i = 0; i < left; i++) {
//            for (int j = 0; j < left; j++) {
//                if (j < i)
//                    DEBUG("%d ", 0);
//                else
//                    DEBUG("%d ", f1[i][j]);
//            }
//            DEBUG("\n");
//        }

        result1 = f1[left - 1][left - 1];
        // free
        for (int i = 0; i < left; i++) {
            delete[]f1[i];
        }
        delete[]f1;
    }

    /*
     * Step 2: deal with redundant left parentheses
     *         similar to right parentheses, just take a reverse order
     * */
    if (size - left == 0);
    else {
        int **f2 = new int *[size - left];
        for (int i = 0; i < size - left; i++) {
            f2[i] = new int[size - left];
        }

        // DP f(n, k) =
        for (int j = 0, n2 = (len-pos_stack[size-1]+1)/2; j < size-left; j++) {
            f2[0][j] = permutation(n2, j+1);
        }
        for (int i = 1; i < size-left; i++) {
            for (int j = i; j < size-left; j++) {
                int n2 = (pos_stack[size-i] - pos_stack[size-1-i]) / 2 + 1;
                f2[i][j] = ((n2 * f2[i-1][j-1] % MOD) + f2[i-1][j]) % MOD;
            }
        }
//        DEBUG("f2:\n");
//        for (int i = 0; i < size-left; i++) {
//            for (int j = 0; j < size-left; j++) {
//                if (j < i)
//                    DEBUG("%d ", 0);
//                else
//                    DEBUG("%d ", f2[i][j]);
//            }
//            DEBUG("\n");
//        }
        result2 = f2[size-left-1][size-left-1];

        // clean work
        for (int i = 0; i < size - left; i++) {
            delete[]f2[i];
        }
        delete[]f2;
    }

    // TODO how to correctly calculate this value since res1 and res2 could be huge.
    return (result1 * result2) % MOD;
}

int ms_6_17_p4::test() {
    char stack[1000];
    int pos_stack[1000];
    int len = 1000;
    int size = 1000;
    for (int i = 0; i < 1000; i++) {
        pos_stack[i] = i;
    }
    long long result = DP_solve(size, 1000, pos_stack, len);
    DEBUG("%lld", result);
}

int ms_6_17_p4::run() {
//    test();
//    getchar();

    char str[1001];
    scanf("%s", str);
    getchar();
    char stack[1001];
    int pos_stack[1001];
    int size = 0;
    int len = 0;
    for (int i = 0; i <= 1000; i++) {
        if (str[i] == '(') {
            stack[size] = 0;
            pos_stack[size] = i;
            size++;
        } else if (str[i] == ')') {
            if (size > 0) {
                char top = stack[size - 1];
                if (top == 0) {
                    size--;
                } else if (top == 1) {
                    stack[size] = 1;
                    pos_stack[size] = i;
                    size++;
                }
            } else {
                stack[size] = 1;
                pos_stack[size] = i;
                size++;
            }
        } else if (str[i] == '\0') {
            len = i;
            break;
        }
    }
//    DEBUG("stack: ");
//    for (int i = 0; i < size; i++) {
//        DEBUG("%d ", stack[i]);
//    }
//    DEBUG("\n");
//
//    DEBUG("posit: ");
//    for (int i = 0; i < size; i++) {
//        DEBUG("%d ", pos_stack[i]);
//    }
//    DEBUG("\n");

    int out1 = size;
    long long out2 = 0;

    int left = size;
    for (int i = 0; i < out1; i++) {
        int left_or_right = stack[i];
        int position = pos_stack[i];
        if (left_or_right == 0) {
            left = i;
            break;
        }
    }

    out2 = DP_solve(size, left, pos_stack, len);

    printf("%d %lld\n", out1, out2);
    return 0;
}