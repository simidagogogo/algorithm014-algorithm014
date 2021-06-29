# paced-repeatition-week-9

> 2020/10/12 - 2020/10/18



#### First-Unique-Character-in-a-String-387

```cpp
//
// Created by 张达 on 2020/10/19 08:48.
//

#include <string>
using namespace std;

// TODO 未看最优解

// 1. 构建字符哈希
// 2. 遍历s，寻找第一个出现的value为1的key
// time O(n), space O(n)
class Solution {
 public:
  int firstUniqChar(string s) {
      int char_map[128] = {0};
      for (const auto &c:s) {
          char_map[c]++;
      }

      for (int i = 0; i < s.size(); ++i) {
          if (char_map[s[i]] == 1)
              return i;
      }
      return -1;
  }
};
```



#### kmp-search

```cpp
//
// Created by 张达 on 2020/10/29 21:01.
//

#include <string>
#include <vector>

using namespace std;
class Solution {
 public:
  void prefix_table(string &pattern, vector<int> &prefix, int n) {
      prefix[0] = 0;
      int i = 1;
      int len = 0;
      while (i < n) {
          if (pattern[i] == pattern[len]) {
              len++;
              prefix[i++] = len;
          } else {
              if (len > 0) {
                  len = prefix[--len];
              } else {
                  prefix[i++] = len;
              }
          }
      }
  }

  void move_prefix_table(vector<int> &prefix, int n) {
      for (int i = n - 1; i > 0; --i) {
          prefix[i] = prefix[i - 1];
      }
      prefix[0] = -1;
  }

  void kmp_serach(string text, string pattern) {
      // text[i]      , len(text)    = m
      // pattern[j]   , len(pattern) = n
      int n = pattern.size();
      int m = text.size();
      vector<int> prefix(n);
      prefix_table(pattern, prefix, n);
      move_prefix_table(prefix, n);

      int i = 0, j = 0;
      while (i < m) {
          if (j == n - 1 && text[i] == pattern[j]) {
              printf("find pattern at %d\n", i - j);
              j = prefix[j];
          }
          if (text[i] == pattern[j]) {
              i++; j++;
          } else {
              j = prefix[j];
              if (j == -1)
                  i++; j++;
          }
      }
  }
};

int main() {
    Solution solve;

    string pattern = "ABABCABAA";
    string text = "ABABABCABAABABABAB";

    vector<int> prefix(9);
    int n = 9;
    solve.prefix_table(pattern, prefix, n);
    solve.move_prefix_table(prefix, n);
    int i;
    for (int i = 0; i < n; ++i) {
        printf("%d\n", prefix[i]);
    }
    solve.kmp_serach(text, pattern);
    return 0;
}
```



#### Reverse-Only-Letters-917

```cpp
//
// Created by 张达 on 2020/10/29 23:37.
//

#include <string>
using namespace std;

class Solution {
 public:
  string reverseOnlyLetters(string s) {
      for (int i = 0, j = s.size() - 1; i < j;) {
          while (i < j and !isalpha(s[i])) i++;
          while (i < j and !isalpha(s[j])) j--;
          swap(s[i++], s[j--]);
          1 + "ds";
      }
      return s;
  }
};

class Solution1 {
 public:
  string reverseOnlyLetters(string s) {
      for (int i = 0, j = s.size() - 1; i <= j;) {
          if (!(('a' <= s[i] and s[i] <= 'a' + 25) or ('A' <= s[i] and s[i] <= 'A' + 25))) {
              i++;
          } else if (!(('a' <= s[j] and s[j] <= 'a' + 25) or ('A' <= s[j] and s[j] <= 'A' + 25))) {
              j--;
          } else {
              swap(s[i++], s[j--]);
          }
      }
      return s;
  }
};
```



#### Reverse-String-II-541

```cpp
//
// Created by 张达 on 2020/10/19 09:24.
//

// self-developed algorithm

#include <string>
using namespace std;

class Solution {
 public:
  void reverseString(string& s, int begin, int end) {
      for (int i = begin, j = end; i < j; ++i, --j) {
        swap(s[i], s[j]);
      }
  }

  string reverseStr(string s, int k) {
      int len = s.size();
      for (int i = 0; i < len; i = i + 2 * k) {
          // 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
          if (i + k - 1 <= len - 1) {
            reverseString(s, i, i + k - 1);
          }

          // 如果剩余字符少于 k 个，则将剩余字符全部反转。
          if (i < (len - 1) and (len - 1) < (i + k - 1)) {
              reverseString(s, i, len - 1);
          }
      }
      return s;
  }
};
```



#### Reverse-Words-in-a-String-151

```cpp
//
// Created by 张达 on 2020/10/19 09:01.
//

#include <string>
using namespace std;

// 1. rearrange_string 去掉多余的空格
// 2. reverse_words 完成翻转操作
class Solution {
 public:
  string reverseWords(string s) {
      reverse_words(s);
      return rearrange_string(s);
  }

  // time O(n)
  string rearrange_string(string &s) {
      string res;
      int i = 0, j = s.size() - 1;
      while (i < j and s[i] == ' ') i++;
      while (i < j and s[j] == ' ') j--;
      while (i <= j) {
          if (s[i] != ' ') {
              res += s[i++];
          } else {
              res += ' ';
              while (i < j and s[i] == ' ') i++;
          }
      }
      return res;
  }

  // time O(n^2)
  void reverse_words(string &s) {
      reverse(s.begin(), s.end());
      int j = s.size();
      for (int i = s.size() - 1; i >= 0; --i) {
          if (s[i] == ' ') {
              reverse(s.begin() + i + 1, s.begin() + j);
              j = i;
          }
          if (i == 0) reverse(s.begin(), s.begin() + j);
      }
  }
};
```



#### Reverse-Words-in-a-String-III-557

```cpp
//
// Created by 张达 on 2020/10/29 23:29.
//
#include <string>
using namespace std;

class Solution {
 public:
  string reverseWords(string s) {
      int j = s.size();
      for (int i = s.size() - 1; i >= 0; --i) {
          if (s[i] == ' ') {
              reverse(s.begin() + i + 1, s.begin() + j);
              j = i;
          }
          if (i == 0) reverse(s.begin() + i, s.begin() + j);
      }
      return s;
  }
};
```



#### string-match

```cpp
//
// Created by 张达 on 2020/10/16 09:28.
//

// 字符串匹配算法
// 1. 暴力匹配法
// 2. rabin_karp算法

#include <string>
using namespace std;
class Solution {
 private:
  static const int D = 256;
  static const int Q = 10003;

 public:
  int brute_force(string text, string pattern) {
      int M = text.size();
      int N = pattern.size();
      for (int i = 0; i <= M - N; ++i) {
          int j;
          for (j = 0; j < N; ++j) {
              if (pattern[j] != text[i + j])
                  break;
          }
          if (j == N) {
              return i;
          }
      }
      return -1;
  }

  int rabin_karp_search(const string& text, const string& pattern) {
      int M = text.size();
      int N = pattern.size();

      int text_hash = 0;
      int pattern_hash = 0;
      for (int i = 0; i < N; ++i) {
        text_hash =  (text_hash * D + text[i]) % Q;
        pattern_hash =  (pattern_hash * D + pattern[i]) % Q;
      }

      int heightest_power = 1;
      for (int i = 0; i < N - 1; ++i) {
          heightest_power = (heightest_power * D) % Q;
      }

      for (int i = 0; i <= M - N; ++i) {
          if (text_hash == pattern_hash) {
              int j;
              for (j = 0; j < N; ++j) {
                  if (text[i + j] != pattern[j]) {
                      break;
                  }
              }
              if (j == N) {
                  return i;
              }
          }
          // 若哈希值不相等，则更新text_hash
          if (i < M - N) {
              text_hash = ((text_hash - heightest_power * text[i]) * D + text[i + N]) % Q;
              if (text_hash < 0) {
                  text_hash += Q;
              }
          }
      }

      return -1;
  }
};

int main() {
    Solution solve;
    string text = "simida lianmeng wangluyue";
    string pattern = "lianmeng";
//    auto res = solve.brute_force(text, pattern);
    auto res = solve.rabin_karp_search(text, pattern);
    printf("%d\n", res);
}
```

