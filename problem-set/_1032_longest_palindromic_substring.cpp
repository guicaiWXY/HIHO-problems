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
    const char del = '\1';
    int len = strlen(txt);
//    DEBUG("len=%d\n", len);
    if (len == 1) {
        return 1;
    }
    text[0] = 2;
    text[1] = del;
    DEBUG("%s\n", txt);

    for (int i = 0; i < len; i++) {
        text[(i << 1)+2] = txt[i];
        text[(i << 1)+3] = del;
    }

    int n_len = 2 * len + 2;
    text[n_len] = 0;
    DEBUG("%s\n", text);

    // J for current index with max right boundary
    int id = 0;
    f[0] = 0;
    int mx = 0;
    int max = 0;
    for (int i = 1; i < n_len; i++) {
        int auxilary;
        if (i >= id + f[id]) {
            auxilary = 1;
        } else {
            int j = 2 * id - i;
            int aux1 = f[j];
            int aux2 = mx - i;
            auxilary = MIN(aux1, aux2);
        }
        while (text[i+auxilary] == text[i-auxilary])
            auxilary++;
        if (auxilary > max) {
            max = auxilary;
        }
        if (i + auxilary > mx) {
            id = i;
            mx = i+auxilary;
        }
        f[i] = auxilary;
        DEBUG("f[%d]= %d ", i, auxilary);
    }
    DEBUG("\n");
    DEBUG("max=%d\n", max);

    return max-1;
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
    return 0;
}
int _1032_longest_palindromic_substring::run() {
    int N;
    std::cin >> N;
    static char text[2000010];
    static int f[2000010];
    for (int turn = 0; turn < N; turn++) {
        scanf("%s", text);

//        longestPalindrome(string(text + 1));
//        continue;

        int longest = my_version(text);
        printf("%d\n", longest);
    }

    return 0;
}