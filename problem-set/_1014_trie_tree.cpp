//
// Created by wxy on 17.7.8.
//

#include "_1014_trie_tree.h"
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

struct Node {
    LL count;
    vector<Node *> kids;

    char sym;
    bool end;
    Node(LL _count, char _sym, bool _end):
            count(_count), sym(_sym), end(_end){}

};
vector<struct Node*> trees;

void trie_tree_count(string prefix) {

}

void trie_tree_add(string word) {
    char x = word[0];
    int n = trees.size();
    int which;
    for (which = 0; which < n; which++) {
        if (trees[which]->sym == x) {
            break;
        }
    }
    if (which == n) {
        // adding a trie tree
        int node_count = word.length();
        Node *new_root;
        Node *cur;
        cur = new Node(1, word[0], 0);
        new_root = cur;
        for (int i = 1; i < node_count; i++) {
            Node *new_node = new Node(1, word[i], (i==node_count ? 1 : 0));
            cur->kids.push_back(new_node);
            cur = new_node;
        }
        trees.push_back(new_root);
    }
    else {
        // append to an existing trie tree
        Node *node = trees[which];
        int str_len = word.length();
        node->count ++;
        for (int i = 1; i < str_len; i++) {
            // search a node in node->kids
            int cnt = node->kids.size();
            int j;
            for(j = 0; j < cnt; j++) {
                if (node->kids[j]->sym == word[i]) {
                    node->kids[j]->count ++;
                    node = node->kids[j];
                    break;
                }
            }
            if (j == cnt) {
                // not found
            }
        }
    }

}

int _1014_trie_tree::run() {
    int N = 5;
//    scanf("%d", &N);
//    getchar();
    char input[100010];
    string a[5] = {"abcdefg", "1234567", "!@#$%^&", "a999", "bbb"};
    for (int i = 0; i < N; i++) {
//        scanf("%s", input);
        trie_tree_add(a[i]);
//        trie_tree_add(string(input));
    }
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", input);
        trie_tree_count(string(input));
    }
}
