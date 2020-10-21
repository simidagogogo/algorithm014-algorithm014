# [DSA] training camp week-9

> 2020/10/12 - 2020/10/18



## 完成情况

| Title                                   | Keywords | Rounds |
| --------------------------------------- | -------- | ------ |
| 387. First Unique Character in a String | String   | 1      |
| 541. Reverse String II                  | String   | 1      |

##### 387. First Unique Character in a String

```C++
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



##### 541. Reverse String II

```C++
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
