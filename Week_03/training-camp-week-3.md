# [DSA] training camp week-3

> 2020/08/24-2020/08/31



## 完成情况

| Title                                                        | Keywords                 | Rounds |
| ------------------------------------------------------------ | ------------------------ | ------ |
| 70. Climbing Stairs                                          | recursion/LRU            | 4/5    |
| 77. Combinations                                             | recursion/backtracking   | 2/5    |
| 22. Generate-Parentheses                                     | recursion/backtracking   | 3/5    |
| 17. Letter-Combinations-of-a-Phone-Number                    | recursion/backtracking   | 1/5    |
| 112. Path-Sum                                                | recursion/backtracking   | 1/5    |
| 113. Path-Sum-II                                             | recursion/backtracking   | 2/5    |
| 46. Permutations                                             | recursion/backtracking   | 1/5    |
| 78. Subsets                                                  | recursion/backtracking   | 1/5    |
| 98. Validate-Binary-Search-Tree                              | recursion                | 2/5    |
| 105. Construct-Binary-Tree-from-Preorder-and-Inorder-Traversal | recursion                | 2/5    |
| 226. Invert-Binary-Tree                                      | recursion                | 2/5    |
| 236. Lowest-Common-Ancestor-of-a-Binary-Tree                 | recursion                | 2/5    |
| 104. Maximum-Depth-of-Binary-Tree                            | recursion                | 2/5    |
| 111. Minimum-Depth-of-Binary-Tree                            | recursion                | 1/5    |
| 297. Serialize-and-Deserialize-Binary-Tree                   | recursion                | 1/5    |
| 50. Pow                                                      | recursion/divide-conquer | 1/5    |



**70. Climbing Stairs**

```cpp
class Solution {
 private:
  int helper(int n, vector<int> &vec) {
      if (n <= 3) return n;
      if (vec[n] > 0) {
          return vec[n];
      } else {
          vec[n] = helper(n - 1, vec) + helper(n - 2, vec);
      }
      return vec[n];
  }
 public:

  int climbStairs(int n) {
      vector<int> vec(n + 1, 0);
      return helper(n, vec);
  }
};
```



**22. Generate Parentheses**

```cpp
class Solution {
 public:
  void help(int left , int right, int n, string s, vector<string>& result) {
      // recursion terminator
      if (left == n and right == n) {
          result.push_back(s);
          return;
      }
      if (left < n) {
        help(left + 1, right, n, s + "(", result);
      }
      if (right < left) {
          help(left, right + 1, n, s + ")", result);
      }
  }

  vector<string> generateParenthesis(int n) {
      vector<string> result;
       help(0, 0, n, "", result);
      return result;
  }
};
```



**77. Combinations**

```cpp
class Solution {
 public:
  vector<vector<int> > combine(int n, int k) {
      vector<vector<int> > result;
      vector<int> vec;
      recurion(result, vec, 1, n, k);
      return result;
  }

  void recurion(vector<vector<int> > &result, vector<int> &vec, int i, int& n, int& k) {
      if (vec.size() >= k) {
          result.push_back(vec);
          return;
      }
      if (i > n) return;
      vec.push_back(i);
      recurion(result, vec, i + 1, n, k); // 选
      vec.pop_back();
      recurion(result, vec, i + 1, n, k); // 不选
  }
};
```



**78. Subsets**

```cpp
// 利用递归去模拟每次放入和取出的操作, 即选还是不选
class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
      vector<vector<int>> result; 
      vector<int> item; 
      help(nums, 0, result, item);
      return result;
  }

  void help(vector<int>& nums, int i, vector<vector<int>>& res, vector<int>& item) {
      // recursion terminator
      if (i >= nums.size()) {
          res.push_back(item);
          return;
      }

      // drill down
      item.push_back(nums[i]);
      help(nums, i + 1, res, item); // 放入

      item.pop_back();
      help(nums, i + 1, res, item); // 不放入
  }
};
```



**46. Permutations**

```cpp
class Solution {
 public:
  void help(vector<int> &nums, int begin, vector<vector<int>> &result) {
      if (begin >= nums.size()) {
          result.push_back(nums);
          return;
      }

      for (int i = begin; i < nums.size(); i++) {
          swap(nums[i], nums[begin]); // 前序
          help(nums, begin + 1, result);
          swap(nums[i], nums[begin]); // 后续
      }
  }

  vector<vector<int>> permute(vector<int> &nums) {
      vector<vector<int>> result;
      help(nums, 0, result);
      return result;
  }
};
```



*17. Letter-Combinations-of-a-Phone-Number**

```cpp
class Solution {
 public:
  void recurion(const string& str,
                string &digits,
                int i,
                vector<string> &result,
                unordered_map<char, string> &map) {
      // recurison terminator
      if (i == digits.size()) {
          result.push_back(str);
          return;
      }
      // process
      string letters = map[digits[i]];
      for (int j = 0; j < letters.size(); ++j) {
          // drill down
          recurion(str + letters[j], digits, i + 1, result, map);
      }
  }
  vector<string> letterCombinations(string digits) {
      vector<string> result;
      if (digits.empty()) return result;

      unordered_map<char, string> map;
      map.emplace('2', "abc");
      map.insert(make_pair('3', "def"));
      map.emplace('4', "ghi");
      map.emplace('5', "jkl");
      map.emplace('6', "mno");
      map.emplace('7', "pqrs");
      map.emplace('8', "tuv");
      map.emplace('9', "wxyz");
      recurion("", digits, 0, result, map);
      return result;
  }
};
```



**112. Path-Sum**

```cpp
class Solution {
 private:
  bool preorder(TreeNode *node, int sum, int &val) {
      if (!node) return false;

      val += node->val;
      if (!node->left and !node->right and sum == val) {
          return true;
      }
      bool l = preorder(node->left, sum, val);
      bool r = preorder(node->right, sum, val);
      val -= node->val;
      return l or r; // 虽然node本身不是，但只要起左右子树中有一个满足，即为true
  }
 public:
  bool hasPathSum(TreeNode *root, int sum) {
      int val = 0;
      return preorder(root, sum, val);
  }
};
```



**113. Path-Sum-II**

```cpp
class Solution {
 private:
  // 既然是树的递归，就一定会用到preorder/inorder/postorder.递归函数名直接体现递归顺序即可
  void preorder(TreeNode *node, int sum, int &val, vector<vector<int>> &result, vector<int> &path) {
      // recursion terminator
      if (!node) return; // 如果为null，即不进入这层梦境，不对参数进行任何的改变

      // process current level logic
      val += node->val;
      path.push_back(node->val);
      if (!node->left && !node->right && val == sum) {
          result.push_back(path);
      }
      // drill down
      preorder(node->left, sum, val, result, path);
      preorder(node->right, sum, val, result, path);

      // reverse states
      val -= node->val;
      path.pop_back();
  }

 public:
  vector<vector<int>> pathSum(TreeNode *root, int sum) {
      vector<vector<int>> result;
      vector<int> path;
      int val = 0;
      preorder(root, sum, val, result, path);
      return result;
  }
};
```



**105. Construct-Binary-Tree-from-Preorder-and-Inorder-Traversal**

```cpp
class Solution {
 public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
      return create(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
  }

  TreeNode *create(vector<int> &preorder, vector<int> &inorder, int p_start, int p_end, int i_start, int i_end) {
      if (p_start > p_end) return nullptr;

      TreeNode *node = new TreeNode(preorder[p_start]); // 这是头结点
      int root_pos;
      for (int i = i_start; i < i_end; ++i) {
          if (inorder[i] == node->val) { // 如果中序的元素等于前序的元素，此时的索引i即为pos即为在中序中头结点的位置
              root_pos = i;
              break;
          }
      }
      node->left = create(preorder, inorder, p_start + 1, p_start + (root_pos - i_start), i_start + 0, root_pos - 1);
      node->right = create(preorder, inorder, p_end - (i_end - root_pos) + 1, p_end + 0, root_pos + 1, i_end + 0);
      return node;
  }
};
```



**226. Invert-Binary-Tree**

```cpp
class Solution {
 public:
  TreeNode *invertTree(TreeNode *root) {
      if (!root) return root;
      swap(root->left, root->right);
      invertTree(root->left);
      invertTree(root->right);
      return root;
  }
};
```



**236. Lowest-Common-Ancestor-of-a-Binary-Tree** 

```cpp
// 个人认为第一种解法不具有通用性，虽然很精妙，但是无法解决一类问题
class Solution1 {
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
      // recurison terminator
      if (!root) return nullptr;
      if (root == p or root == q) return root;

      auto l = lowestCommonAncestor(root->left, p, q); // 如果不满足上述条件，继续遍历左子树
      auto r = lowestCommonAncestor(root->right, p, q);// 如果不满足上述条件，继续遍历右子树
      // 递归的返回值，是从最下层传上来的

      if (!l and !r) return nullptr;
      else if (l and !r) return l;
      else if (r and !l) return r;
      else return root;
  }
};

class Solution2 {
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
      vector<TreeNode *> path;
      vector<TreeNode *> result_p;
      vector<TreeNode *> result_q;
      preorder(root, p, path, result_p);
      path.clear();
      preorder(root, q, path, result_q);

      TreeNode *res = NULL;
      int len = result_p.size() > result_q.size() ? result_q.size() : result_p.size();
      for (int i = 0; i < len; i++) {
          if (result_p[i] == result_q[i]) {
              res = result_q[i]; // 相等就更新，不相等就退出循环
          }
      }
      return res;
  }

  void preorder(TreeNode *node, TreeNode *search, vector<TreeNode *> &path, vector<TreeNode *> &result) {
      if (!node) return;

      path.push_back(node);
      if (node->val == search->val) {
          result = path;
      }
      preorder(node->left, search, path, result);
      preorder(node->right, search, path, result); 
      path.pop_back();
  }
};
```



**104. Maximum Depth of Binary Tree**

```cpp
class SolutionSimplify {
 public:
  int maxDepth(TreeNode *root) {
      if (!root) return 0;
      return max(maxDepth(root->left), maxDepth(root->right)) + 1;
  }
};
```



**111. Minimum-Depth-of-Binary-Tree**

```cpp
class Solution {
 public:
  int minDepth(TreeNode *root) {
      if (!root) {
          return 0;
      }
      if (!root->left and !root->right) {
          return 1;
      }
      int l = minDepth(root->left) + 1;
      int r = minDepth(root->right) + 1;
      if (!root->right) {
          return l;
      } else if (!root->left) {
          return r;
      } else {
          return min(l, r);
      }
  }
};
```



**50. Pow**

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) {
            return 1;
        }
        
        long N = n;
        if (N < 0) {
            N = -N;
        }
        double res = 1.0;
        for (int i = N; i != 0; i = i / 2) {
            if (i % 2) {
                res *= x;
            } 
            x *= x;
        }
        
        return n > 0 ? res : 1/res;
    }
};
```



**297. Serialize-and-Deserialize-Binary-Tree**

```cpp
class Codec2 {
 public:

  // Encodes a tree to a single string.
  string serialize(TreeNode *root) {
      if (!root) return "#";

      // 相当于前序遍历
      string str = to_string(root->val) + ","
          + serialize(root->left) + ","
          + serialize(root->right);
      printf("%s\n", str.c_str());
      return str;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data) {
      if (data == "#") return nullptr;
      stringstream s(data);
      return makeDeserialize(s);
  }

  TreeNode *makeDeserialize(stringstream &s) {
      string str;
      getline(s, str, ','); // read a string splited by ,
      if (str == "#") return nullptr;

      // 前序遍历，解码要和编码对应上
      TreeNode *root = new TreeNode(stoi(str));
      auto l = makeDeserialize(s);
      auto r = makeDeserialize(s);
      root->left = l;
      root->right = r;
      // 由于局部变量l和r不会被任何东西改变，可以直接4句合并为2句。
      return root;
  }
};
```



**98. Validate Binary Search Tree**

```cpp
class Solution2 {
 public:
  bool isValidBST(TreeNode *root) {
      return recurse(root, LONG_MIN, LONG_MAX);
  }

  bool recurse(TreeNode *root, long lower, long upper) {
      if (!root) return true;
    
      long val = root->val;
      if ((val <= lower) || (val >= upper)) {
          return false;
      }
      return recurse(root->left, lower, val) and recurse(root->right, val, upper);
  }
};
```
