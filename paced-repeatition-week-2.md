# paced-repeatition-week-2



#### Binary-Tree-Inorder-Traversal-94

```cpp
//
// Created by 张达 on 2020/8/21.
//
//Follow up: Recursive solution is trivial, could you do it iteratively?

#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  void helper(TreeNode *root, vector<int>& result) {
      if (!root) {
          return;
      }
      helper(root->left, result);
      result.push_back(root->val);
      helper(root->right, result);
  }
  vector<int> inorderTraversal(TreeNode* root) {
      vector<int> result;
      helper(root, result);
      return result;
  }
};
```



#### Binary-Tree-Preorder-Traversal-144

```cpp
//
// Created by 张达 on 2020/8/21. 2/5 09:35
//

#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  void helper(TreeNode *root, vector<int>& result) {
      if (!root) {
          return;
      }
      result.push_back(root->val);
      helper(root->left, result);
      helper(root->right, result);
  }
  vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
      helper(root, result);
    return result;
  }
};
```



#### Group-Anagrams-49

```cpp
//
// Created by 张达 on 2020/8/19. 2/5 13:00-13:10
//

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// method1: hash map
class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
      vector<vector<string>> result;
      unordered_map<string, vector<string>> map;
      for (int i = 0; i < strs.size(); ++i) {
          string str = strs[i];
          sort(str.begin(), str.end());
          if (map.find(str) == map.end()) {
              vector<string> vec = {strs[i]};
              map.emplace(str, vec);
          } else {
              map[str].push_back(strs[i]);
          }
      }
      for (const auto &item : map) {
          result.push_back(item.second);
      }
      return result;
  }
};
```



#### lc-76

#### lc-263



#### Longest-Palindrome-409

```cpp
//
// Created by 张达 on 2020/8/18. 09:12 2/5
//

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  int longestPalindrome(string s) {
      unordered_map<char, int> map;
      int flag = 0;
      int sum = 0;
      for (int i = 0; i < s.size(); ++i) {
          if (map.find(s[i]) == map.end()) {
              map[s[i]] = 1;
          } else {
              map[s[i]]++;
          }
      }

      for (auto map_iterator = map.begin(); map_iterator != map.end(); ++map_iterator) {
          if (map_iterator->second % 2) { // even
                flag = 1;
                sum += map_iterator->second - 1;
          } else {
              sum += map_iterator->second;
          }
      }
      return sum + flag;
  }
};

class Solution2 {
 public:
  int longestPalindrome(string s) {
      int arr[128] = {0};
      int flag = 0;
      int sum = 0;
      for (int i = 0; i < s.size(); ++i) {
          arr[s[i]]++;
      }

      for (int i = 0; i < 128; ++i) {
          if (arr[i] % 2) { // even
              flag = 1;
              sum += arr[i] - 1;
          } else {
              sum += arr[i];
          }
      }
      return sum + flag;
  }
};
```



#### Longest-Substring-Without-Repeating-Characters-3

```cpp
//
// Created by 张达 on 2020/8/19. 2/5
//
// 经典的字符串滑动窗口问题，需要练得滚瓜烂熟

#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
using namespace std;

// method1: exhaustive enumeration O(n^2)
// 双指针同时遍历，每次移动一位，判断新元素是否已经出现，
// 如果已经出现，则跳过。
// 如果没有出现，则num+1
class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
      if (s.empty()) return 0;
      if (s == " ") return 1;

      int cnt = 0;
      int res = 0;
      set<char> set;
      for (int i = 0; i < s.size(); ++i) {
          cnt = 0;
          set.clear();
          for (int j = i; j < s.size(); ++j) {
              if (set.find(s[j]) == set.end()) {
                  set.insert(s[j]);
                  cnt++;
              } else {
                  break;
              }
          }
          res = max(res, cnt);
      }
      return res;
  }
};

// 维护窗口 O(n)

class Solution2 {
 public:
  int lengthOfLongestSubstring(string s) {
      int arr[128] = {0};
      int result = 0;
      string word;
      int i = 0;
      for (int j = 0; j < s.size(); ++j) {
          arr[s[j]]++;
          if (arr[s[j]] == 1) { // only once
              word += s[j];
              result = max(result, (int) word.length());
          } else {
              while (i < j and arr[s[j]] > 1) {
                  arr[s[i]]--;
                  i++;
              }
              word = "";
              word = s.substr(i, j - i + 1); // 每次切出来的string
              result = max(result, (int) word.length()); // 这里加上也没毛病
          }
      }
      return result;
  }
};


// 解法2的精简版
class Solution3 {
 public:
  int lengthOfLongestSubstring(string s) {
      int arr[128] = {0};
      int result = 0, i = 0, cnt = 0;
      for (int j = 0; j < s.size(); ++j) {
          arr[s[j]]++;
          if (arr[s[j]] == 1) { // only once
              cnt++;
              result = max(result, cnt);
          } else {
              while (i < j and arr[s[j]] > 1) {
                  arr[s[i]]--;
                  i++;
              }
              cnt = j - i + 1; // 每次切出来的string
              result = max(result, cnt);
          }
      }
      return result;
  }
};


// 经典的滑动窗口问题模板，自创解法，真香
class Solution4 {
 public:
  int lengthOfLongestSubstring(string s) {
      set<char> set;
      int res = 0, i = 0;
      for (int j = 0; j < s.size(); ++j) {
          if (set.find(s[j]) == set.end()) {
              set.insert(s[j]);
              res = max(j - i + 1, res);
          } else {
              while (s[i] != s[j]) {
                  set.erase(s[i++]);
              }
              ++i; // if s[i] == s[j], then skip
              res = max(j - i + 1, res);
          }
      }
      return res;
  }
};

/*
 Do these leetcode questions to understand the same concept:

`Minimum Size Subarray Sum`
`Minimum Window Substring`
`Longest Substring with K most Distict`
 */


int main() {
    Solution solve;
    string str = "abcabcbb";
    int res = solve.lengthOfLongestSubstring(str);
};
```



#### Minimum-Window-Substring-76

```cpp
//
// Created by 张达 on 2020/8/20. 1/5
//

#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {

  }
};
```



#### N-ary-Tree-Level-Order-Traversal-429

```cpp
//
// Created by 张达 on 2020/8/21. 2/5  09:40
//

#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node {
 public:
  int val;
  vector<Node *> children;

  Node() {}

  Node(int _val) {
      val = _val;
  }

  Node(int _val, vector<Node *> _children) {
      val = _val;
      children = _children;
  }
};

// 多叉树的层序遍历：利用队列的先进先出的特性
// 层序遍历要背的滚瓜烂熟
class Solution {
 public:
  vector<vector<int>> levelOrder(Node *root) {
      vector<vector<int>> result;
      if (!root) return result;

      queue<Node *> queue;
      queue.push(root);
      while (!queue.empty()) {
          int len = queue.size(); // 需要记录当前层的节点个数
          vector<int> vec;
          for (int i = 0; i < len; ++i) {
              auto top = queue.front();
              queue.pop();
              vec.push_back(top->val);
              for (auto i : top->children) {
                   if (!i) queue.push(i);
              }
          }
          result.push_back(vec);
      }
      return result;
  }
};

class Solution2 {
 public:
  void helper(Node* root, int depth, vector<vector<int>>& result) {
      if (!root) return;
      if (depth == result.size()) {
          result.emplace_back();
      }
      result[depth].push_back(root->val);
      for (int i = 0; i < root->children.size(); ++i) {
          if (root->children[i]) {
              helper(root->children[i], depth + 1, result);
          }
      }
  }

  vector<vector<int>> levelOrder(Node* root) {
      vector<vector<int>> result;
      helper(root, 0, result);
      return result;
  }
};
```



#### N-ary-Tree-Postorder-Traversal-590

```cpp
//
// Created by 张达 on 2020/8/21. 2/5 10:20
//

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node {
 public:
  int val;
  vector<Node *> children;

  Node() {}

  Node(int _val) {
      val = _val;
  }

  Node(int _val, vector<Node *> _children) {
      val = _val;
      children = _children;
  }
};

class Solution {
 public:
  void helper(Node *root, vector<int>& result) {
      if (!root) {
          return;
      }
      for (int i = 0; i < root->children.size(); ++i) {
          helper(root->children[i], result);
      }
      result.push_back(root->val);
  }

  vector<int> postorder(Node *root) {
      vector<int> result;
      helper(root, result);
      return result;
  }
};
```



#### N-ary-Tree-Preorder-Traversal-589

```cpp
//
// Created by 张达 on 2020/8/21. 2/5 09:00
//

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node {
 public:
  int val;
  vector<Node *> children;

  Node() {}

  Node(int _val) {
      val = _val;
  }

  Node(int _val, vector<Node *> _children) {
      val = _val;
      children = _children;
  }
};

class Solution {
 public:
  void helper(Node *root, vector<int> &result) {
      // recursion terminator
      if (!root) {
          return;
      }
      // process current level
      result.push_back(root->val);
      // drill down 所谓下探，即一步步向递归终止条件逼近，直到触发递归的反弹（即归）
      for (int i = 0; i < root->children.size(); ++i) {
          Node *child = root->children[i];
          helper(child, result);
      }
      // reverse if needed
  }
  vector<int> preorder(Node *root) {
      // why we need the help of helper function?
      // 函数的返回值为vector<int>，每一次递归都需要对它进行修改，因此需要将它加入参数列表，携带进下一次递归
      // 如果直接用preorder进行递归，则vector<int>无法作为参数传入

      vector<int> result;
      helper(root, result);
      return result;
  }
};
```



#### Repeated-DNA-Sequences-187

```cpp
//
// Created by 张达 on 2020/8/19. 2/5  09:50 - 10:00
//

#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  vector<string> findRepeatedDnaSequences(string s) {
      vector<string> result;
      if (s.size() < 10) {
          return result;
      }

      unordered_map<string, int> map;
      for (int i = 0; i <= s.size() - 10; ++i) {
          string substr = s.substr(i, 10);
          if (map.find(substr) == map.end()) {
              map[substr] = 1;
          } else {
              map[substr]++;
          }
      }

      for (auto & map_iterator : map) {
          if (map_iterator.second > 1) {
              result.push_back(map_iterator.first);
          }
      }
      return result;
  }
};

```



#### Two-Sum-1

```cpp
//
// Created by 张达 on 2020/8/19. 4/5
//

#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;


// sort and double pointer
// 行不通，因为排序后下标会变化
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
      vector<int> result;
      if (nums.size() < 2) return result;
      sort(nums.begin(), nums.end());
      int i = 0, j = nums.size() - 1;
      while (i < j) {
          int s = nums[i] + nums[j];
          if (s == target) {
              return {nums.};
          } else if (s < target) {
              ++i;
          } else {
              --j;
          }
      }
      return result;
  }
};
```



#### Word-Pattern-290

```cpp
//
// Created by 张达 on 2020/8/19. 2/5  09:22-09:42
//
// 切分单词的经典框架，需要练得滚瓜烂熟

#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

// method 1:
// first: split word in str
class Solution {
 public:
  bool wordPattern(string pattern, string str) {
      vector<string> vec = getStringVector(str);
      if (vec.size() != pattern.size()) return false;

      unordered_map<string, char> map;
      set<char> used_set;
      for (int i = 0; i < vec.size(); ++i) {
          if (map.find(vec[i]) == map.end()) {
              if (used_set.find(pattern[i]) != used_set.end()) {
                  return false;
              } else {
                  map[vec[i]] = pattern[i];
                  used_set.insert(pattern[i]);
              }
          } else if (map[vec[i]] != pattern[i]) {
              return false;
          }
      }
      return true;
  }

  vector<string> getStringVector(string &str) const {
      str.push_back(' ');
      string word;
      vector<string> vec;

      for (int i = 0; i < str.size(); ++i) {
          if (str[i] == ' ') {
              vec.push_back(word);
              word.clear();
          } else {
              word += str[i];
          }
      }
      return vec;
  }
};

//int main() {
//    Solution solve;
//    string parttern = "abba";
//    string str = "dog cat cat dog";
//    solve.wordPattern(parttern, str);
//}
```

