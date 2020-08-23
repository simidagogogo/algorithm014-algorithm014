# [DSA] training camp week-2

> 2020/08/17-2020/08/23



## 完成情况

| Number                                            | Keywords                    | Rounds |
| :------------------------------------------------ | --------------------------- | ------ |
| 3. Longest Substring Without Repeating Characters | Slide window/Hashmap/String | 1/5    |
| 76. Minimum Window Substring                      | Slide window/Hashmap/String | 1/5    |
| 49. Group-Anagrams                                | Hashmap                     | 1/5    |
| 187. Repeated DNA Sequences                       | Hashmap                     | 1/5    |
| 290. Word Pattern                                 | Hashmap/String              | 1/5    |
| 409. Longest Palindrome                           | Hashmap                     | 1/5    |
| 242. Valid Anagram                                | Hashmap                     | 1/5    |
| 94. Binary Tree Inorder Traversal                 | Tree/Recrsion               | 2/5    |
| 144. Binary Tree Preorder Traversal               | Tree/Recrsion               | 2/5    |
| 429. N-ary Tree Level Order Traversal             | Tree/Queue                  | 2/5    |
| 589. N-ary Tree Preorder Traversal                | Tree/Recrsion               | 2/5    |
| 590. N-ary Tree Postorder Traversal               | Tree/Recrsion               | 2/5    |
| 102. Binary Tree Level Order Traversal            | Tree/Recrsion               | 1/5    |
| 450. Delete Node in a BST                         | BST/Recrsion                | 1/5    |
| 700. Search in a Binary Search Tree               | BST/Recrsion                | 1/5    |
| 701. Insert into a Binary Search Tree             | BST/Recrsion                | 1/5    |
| 938. Range Sum of BST                             | BST/Recrsion                | 1/5    |



## Codes

**3. Longest Substring Without Repeating Characters**

```cpp
class Solution {
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
              ++i;
              res = max(j - i + 1, res);
          }
      }
      return res;
  }
};
```



**76. Minimum Window Substring**

```cpp
class Solution {
 public:
  static bool contain(int arrs[128], int arrt[128]) {
      for (int i = 0; i < 128; ++i) {
          if (arrs[i] < arrt[i]) return false;
      }
      return true;
  }

  static string minWindow(string s, string t) {
      string result;
      int arrt[128] = {0}, arrs[128] = {0};
      for (char i : t) {
          arrt[i]++;
      }
      int i = 0;
      for (int j = 0; j < s.size(); ++j) {
          arrs[s[j]]++;
          while (i < j) {
              if (arrt[s[i]] == 0) { //如果s[i]不在t中出现，直接跳过
                  ++i;
              } else if (arrs[s[i]] > arrt[s[i]]) { // 如果t中的字符在s中出现1次以上，则跳过
                  arrs[s[i]]--;
                  ++i;
              } else {
                  if (contain(arrs, arrt)) {
                      int cnt = j - i + 1;
                      if (result.empty() or result.size() > cnt) {
                          result = s.substr(i, cnt);
                      }
                  }
                  break;
              }
              if (i == 0) {
                  return s;
              }
          }
      }
      return result;
  }
};
```



**49. Group-Anagrams**

```cpp
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



**187. Repeated-DNA-Sequences**

```cpp
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



**290. Word-Pattern**

```cpp
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
```



**409. Longest Palindrome**

```cpp
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



**242. Valid-Anagram**

```cpp
class Solution {
 public:
  bool isAnagram(string s, string t) {
      int arr[128] = {0};
      for (char i : s) {
          arr[i]++;
      }
      for (char i : t) {
          arr[i]--;
      }
      for (int i : arr) {
          if (i) {
              return false;
          }
      }
      return true;
  }
};
```



**94. Binary-Tree-Inorder-Traversal**

```cpp
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



**144. Binary-Tree-Preorder-Traversal**

````cpp
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
````



**429. N-ary-Tree-Level-Order-Traversal**

```cpp
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
              vec.push_back(top->val);
              queue.pop();
              for (auto i : top->children) {
                  queue.push(i);
              }
          }
          result.push_back(vec);
      }
      return result;
  }
};
```



**589. N-ary-Tree-Preorder-Traversal**

```cpp
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



**590. N-ary-Tree-Postorder-Traversal**

```cpp
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



**102. Binary Tree Level Order Traversal**

```cpp
class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
      vector<vector<int>> result;
      if (!root) return result;

      queue<TreeNode *> q;
      q.push(root);
      while (!q.empty()) {
          vector<int> vec;
          int len = q.size();
          while (len--) {
              auto node = q.front();
              q.pop();
              vec.push_back(node->val);
              if (node->left) {
                  q.push(node->left);
              }
              if (node->right) {
                  q.push(node->right);
              }
          }
          result.push_back(vec);
      }
      return result;
  }
};
```



**450. Delete Node in a BST**

```cpp
class Solution {
 public:
  TreeNode *deleteNode(TreeNode *root, int val) {
      if (!root) {
          return root;
      }
      if (val < root->val) {
          root->left = deleteNode(root->left, val);
      } else if (val > root->val) {
          root->right = deleteNode(root->right, val);
      } else {
          /* leaf node case */
          if (!root->left && !root->right) {
              delete root;
              root = nullptr;
              return nullptr;
          }
          /* 1 child case */
          if (!root->left or !root->right) {
              TreeNode* ret = root->left? root->left:root->right;
              delete root;
              root = nullptr;
              return ret; // the new root node
          }
          /* 2 child case */
          if (root->left && root->right) {
              TreeNode* temp = root->right;
              while (temp->left) {
                  temp = temp->left; // temp节点为target节点的右子树的最左叶子节点
              }
             swap(root->val, temp->val);
             root->right = deleteNode(root->right, temp->val); // 这里的 val == temp->val
          }
      }
      return root;
  }
};
```



**700. Search in a Binary Search Tree**

```cpp
class Solution {
 public:
  TreeNode* searchBST(TreeNode* root, int val) {
      if (!root) {
          return nullptr;
      }
      if (val == root->val) {
          return root;
      } else if (val < root->val) {
          return searchBST(root->left, val);
      } else {
          return searchBST(root->right, val);
      }
      return nullptr;
  }
};
```



**701. Insert into a Binary Search Tree**

```cpp
class Solution {
 public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
      if (!root) return new TreeNode(val);
      if (val >= root->val)
          root->right = insertIntoBST(root->right, val);
      else
          root->left = insertIntoBST(root->left, val);
      return root;
  }
};
```



**938. Range Sum of BST**

```cpp
class Solution {
 public:
  TreeNode* searchBST(TreeNode* root, int val) {
      if (!root) {
          return nullptr;
      }
      if (val == root->val) {
          return root;
      } else if (val < root->val) {
          searchBST(root->left, val);
      } else if (val > root->val){
          searchBST(root->right, val);
      }
      return nullptr;
  }
};
```
