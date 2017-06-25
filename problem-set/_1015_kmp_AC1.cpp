//
// Created by 11206 on 2017/6/25.
//
#include "_1015_kmp.h"
#include "../util/debug.h"
#include <iostream>
#include <string>
using namespace std;

void calNext(string str, int idx, int* next) {
  if (idx > str.size())
      return;

  int q = next[idx - 1];
  while (q != -1) {
      if (str[q] == str[idx - 1]) {
          next[idx] = q + 1;
          break;
      }
      q = next[q];
  }
  if (q == -1)
      next[idx] = 0;
  calNext(str, idx + 1, next);
}

int kmp(string str, string pattern) {
  // resolve the NEXT array
  int* next = new int[pattern.size() + 1];
  next[0] = -1;
  calNext(pattern, 1, next);
  int _index = 0;
  for (; _index < pattern.size() + 1; ++_index) {
      DEBUG("next[%d]=%d ", _index, next[_index]);
  }

  // pattern match
  int m = 0;
  int i = 0, j = 0;
  for (; i < str.size();) {
      if (j == -1) {
          i++;
          j = 0;
          continue;
      }
      int k = j;
      for (; k < pattern.size(); k++)
          if (str[i + k - j] != pattern[k])
              break;
      if (k == pattern.size())
          m++;
      i += k - j;
      j = next[k];
  }

  return m;
}

int _1015_kmp::run() {
  int N = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
      string pattern, str;
      cin >> pattern >> str;

      cout << kmp(str, pattern) << endl;
  }

  return 0;
}