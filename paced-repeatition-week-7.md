# paced-repeatition-week-7



#### trie-template

```
//
// Created by 张达 on 2020/9/25. 09:52
//

#include <map>
#include <string>
using namespace std;


struct TrieNode {
  map<char, TrieNode *> child_table;
  int end;
  TrieNode() : end(0) {}
};


class Trie {
 public:
  TrieNode* root;

  /* Initialize your data structure here */
  Trie() {
      root = new TrieNode();
  }

  /* Inserts a word into the trie. */
  void insert(string word) {
      TrieNode* curr = root;
      for (int i = 0; i < word.size(); ++i) {
          if (curr->child_table.count(word[i]) == 0) {
              curr->child_table[word[i]] = new 
          }
      }
  }

};
```

