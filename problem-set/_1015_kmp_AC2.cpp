//
// Created by wxy on 17.6.25.
//
#include "_1015_kmp.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> kmpProcess(string t) {
    int n = t.length();
    vector<int> lps(n, 0);
    for (int i = 1, len = 0; i < n; ) {
        if (t[i] == t[len])
            lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }
    return lps;
}

int kmp(string s, string t) {
    int m = s.length(), n = t.length(), cnts = 0;
    vector<int> lps = kmpProcess(t);
    for (int i = 0, j = 0; i < m; ) {
        if (s[i] == t[j]) {
            i++;
            j++;
        }
        if (j == n) cnts++;
        if (i < m && s[i] != t[j]) {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
    return cnts;
}

//int main(void) {
int _1015_kmp::run() {
    int cases;
    scanf("%d", &cases);
    for (int i = 0; i < cases; i++) {
        string s, t;
        cin >> t;
        cin >> s;
        printf("%d\n", kmp(s, t));
    }
    return 0;
}