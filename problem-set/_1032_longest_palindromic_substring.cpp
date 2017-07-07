//
// Created by wxy on 17.7.7.
//

#include "_1032_longest_palindromic_substring.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MIN(x, y) ((x) < (y)? (x): (y))

//预处理字符串，abc预处理后变成$#a#b#c#^
string preProcess(const string &s) {
    int n = s.size();
    string res;
    res.push_back('$');//把$放到字符串头部
    res.push_back('#');//以#作为原来字符串中每个字符的间隔
    for (int i = 0; i < n; i++) {
        res.push_back(s[i]);
        res.push_back('#');
    }
    res.push_back('^');//以^作为字符串的结尾
    return res;
}

int longestPalindrome(string s) {
    const int len = s.size();
    if (len <= 1)return 1;
    //Manncher算法 ，o（n）
    string str = preProcess(s);
    int n = str.size(), id = 0, mx = 0;
    vector<int> p(n, 0);
    for (int i = 1; i < n - 1; i++) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        //if(mx <= i || (mx > i && p[2*id-i] == mx - i)) //根据正文斜体部分的注释，这里可要可不要
        while (str[i + p[i]] == str[i - p[i]])p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }

    //遍历p，寻找最大回文长度
    int maxLen = 0, index = 0;
    for (int i = 1; i < n - 1; i++)
        if (p[i] > maxLen) {
            maxLen = p[i];
            index = i;
        }
    //printf("%d\n", maxLen-1);
//    return s.substr((index - maxLen) / 2, maxLen - 1);
    return maxLen - 1;
}
int my_version(char *txt) {
    static char text[2000010];
    static int f[2000010];
    int len = strlen(txt);
//    DEBUG("len=%d\n", len);
    if (len == 1) {
        return 1;
    }
    text[0] = 2;
    text[1] = txt[0];
        DEBUG("%s\n", txt);

    for (int i = len; i >= 1; i--) {
        text[(i << 1)+1] = txt[i];
        text[(i << 1)] = 1;
    }
    int n_len = (len << 1);
    text[n_len] = 0;
//        DEBUG("%s\n", text);

    // J for current index with max right boundary
    int J = 1;
    int fJ = 1;
    f[0] = 1;
    f[1] = 1;
    int max_j = 0;
    int max = 0;
    for (int j = 2; j < n_len; j++) {
        int auxilary;
        if (j >= J + fJ / 2) {
            int tmp = 1;
            while (text[j - tmp] == text[j + tmp])
                tmp++;
            auxilary = tmp * 2 - 1;
        } else {
            int sym = 2 * J - j;
            int aux1 = f[sym];
            int aux2 = fJ - 2 * (j - J);
            if (aux1 != aux2) {
                auxilary = MIN(aux1, aux2);
            } else {
                int tmp = aux1 / 2 + 1;
                while (text[j - tmp] == text[j + tmp]) {
                    tmp++;
                }
                auxilary = 2 * tmp - 1;
            }
        }
        if (auxilary > max) {
            max_j = j;
            max = auxilary;
        }
        if (j + auxilary / 2 > J + fJ / 2) {
            J = j;
            fJ = auxilary;
        }
        f[j] = auxilary;
//            DEBUG("f[%d]= %d ", j, auxilary);
    }
//        DEBUG("\n");
//    DEBUG("max=%d\n", max);

    if (max == 1) {
        return 1;
    }
    if (text[max_j] != 1 && text[max_j - max / 2] == 1)
        return (max - 1) / 2;
    else if (text[max_j] != 1) {
        return (max + 1) / 2;
    } else if (text[max_j - max / 2] == 1) {
        return (max - 1) / 2;
    } else {
        return (max + 1) / 2;
    }
}

int _1032_longest_palindromic_substring::test() {
    const int L = 10000;
    char text[L];
    text[L-1] = 0;
    for (int i = 0; i < 10; i++) {
        srand((unsigned)time(NULL) + i);
        for (int t=0; t < L-1; t++) {
            text[t] = (rand() % ('g'-'a')) + 'a';
        }
        int result1 = my_version(text);
        int result2 = longestPalindrome(string(text));
        if (result1 != result2) {
            DEBUG("\nError: text=[%s], res1=%d, res2=%d\n", text, result1, result2);
        } else
            DEBUG("result=%d ", result1);
    }
}
int _1032_longest_palindromic_substring::run() {
    int N;
    std::cin >> N;
    static char text[2000010];
    static int f[2000010];
    for (int turn = 0; turn < N; turn++) {
        scanf("%s", text + 1);

        longestPalindrome(string(text + 1));
//        continue;

        int len = strlen(text + 1);
        if (len == 1) {
            printf("1\n");
            continue;
        }
        text[0] = 2;
//        DEBUG("%s\n", text);

        /*
         * Step1: adding '$'
         * */
        for (int i = len; i > 1; i--) {
            text[(i << 1) - 1] = text[i];
            text[(i << 1) - 2] = 1;
        }
        int n_len = (len << 1);
        text[n_len] = 0;
//        DEBUG("%s\n", text);

        // J for current index with max right boundary
        int J = 1;
        int fJ = 1;
        f[0] = 1;
        f[1] = 1;
        int max_j = 0;
        int max = 0;
        for (int j = 2; j < n_len; j++) {
            int auxilary;
            if (j >= J + fJ / 2) {
                int tmp = 1;
                while (text[j - tmp] == text[j + tmp])
                    tmp++;
                auxilary = tmp * 2 - 1;
            } else {
                int sym = 2 * J - j;
                int aux1 = f[sym];
                int aux2 = fJ - 2 * (j - J);
                if (aux1 != aux2) {
                    auxilary = MIN(aux1, aux2);
                } else {
                    int tmp = aux1 / 2 + 1;
                    while (text[j - tmp] == text[j + tmp]) {
                        tmp++;
                    }
                    auxilary = 2 * tmp - 1;
                }
            }
            if (auxilary > max) {
                max_j = j;
                max = auxilary;
            }
            if (j + auxilary / 2 > J + fJ / 2) {
                J = j;
                fJ = auxilary;
            }
            f[j] = auxilary;
//            DEBUG("f[%d]= %d ", j, auxilary);
        }
//        DEBUG("\n");

        if (max == 1) {
            printf("1\n");
            continue;
        }
        if (text[max_j] != 1 && text[max_j - max / 2] == 1)
            printf("%d\n", (max - 1) / 2);
        else if (text[max_j] != 1) {
            printf("%d\n", (max + 1) / 2);
        } else if (text[max_j - max / 2] == 1) {
            printf("%d\n", (max - 1) / 2);
        } else {
            printf("%d\n", (max + 1) / 2);
        }
    }

    return 0;
}