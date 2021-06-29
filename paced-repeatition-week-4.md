# paced-repeatition-week-4



#### Assign-Cookies-455

```cpp
//
// Created by 张达 on 2020/9/5.
//

#include <vector>
using namespace std;


// 贪心算法
//
class Solution {
 public:
  int findContentChildren(vector<int>& g, vector<int>& s) {
      int result = 0;
      sort(g.begin(), g.end());
      sort(s.begin(), s.end());
      for (int i = 0, j = 0; i < s.size() and j < g.size();) {
          if (s[i] >= g[j]) {
              result++;
              j++;
          }
          i++;
      }
      return result;
  }
};
```



#### Best-Time-to-Buy-and-Sell-Stock-121

```cpp
//
// Created by 张达 on 2020/9/6. 1/5 09:30
//

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// 每一步都是最优的，自底向上递推
// 动态规划，没有好办法，多练

// brute force，遍历i和j，寻找i之后的最大的j, time O(n^2)
// Time Limit Exceeded 199/200
class Solution {
 public:
  int maxProfit(vector<int> &prices) {
      int res = 0;
      for (int i = 0; i < prices.size() - 1; ++i) {
          for (int j = i + 1; j < prices.size(); ++j) {
              res = max(res, prices[j] - prices[i]);
          }
      }
      return res;
  }
};

// 可以变形到53
class Solution2 {
 public:
  int maxProfit(vector<int> &prices) {
      const int n = prices.size();
      if (n < 1) return 0;
      vector<int> min_price(n);
      vector<int> max_profit(n);

      // 定义初始状态
      min_price[0] = prices[0];
      max_profit[0] = 0;
      for (int i = 1; i < n; ++i) {
          min_price[i] = min(min_price[i - 1], prices[i]);
          max_profit[i] = max(max_profit[i - 1], prices[i] - min_price[i - 1]);
      }
      return max_profit[n - 1];
  }
};
```



#### BFS-template

```cpp
//
// Created by simida on 2020/09/01 10:03
//

// BFS的模板，递归形式和非递归形式，超哥说一定要练得滚瓜烂熟

#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

struct Node {
  int val;
  vector<Node *> children;
  Node(int val) : val(val) {}
};

class BFSTemplate {
 public:
  void bfs(Node *root) {
      map<int, int> visited;
      if (!root) return;

      queue<Node *> queue_node;
      queue_node.push(root);

      while (!queue_node.empty()) {
          Node *node = queue_node.front();
          queue_node.pop();

          // 以下两行代码很关键
          if (visited.count(node->val)) continue;
          visited[node->val] = 1;

          for (int i = 0; i < node->children.size(); ++i) {
              queue_node.push(node->children[i]);
          }
      }
      return;
  }
};

class BFSTemplate2 {
 public:
  void bfs(Node *root) {
      map<int, int> visited;
      if (!root) return;

      queue<Node *> queue_node;
      queue_node.push(root);

      while (!queue_node.empty()) {
          Node *node = queue_node.front();
          queue_node.pop();

          // 以下两行代码很关键
          if (!visited.count(node->val)) {
              visited[node->val] = 1;
              for (int i = 0; i < node->children.size(); ++i) {
                  queue_node.push(node->children[i]);
              }
          }
      }
      return;
  }
};
```



#### Binary-Tree-Level-Order-Traversal-102

```cpp
//
// Created by 张达 on 2020/9/1. 2/5 09:36
//

#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
      vector<vector<int>> result;
      if (!root) {
          return result;
      }
      queue<TreeNode *> q;
      q.push(root);

      while (!q.empty()) {
          int len = q.size();
          vector<int> vec;
          while (len--) {
              auto top = q.front();
              q.pop();
              vec.push_back(top->val);

              if (top->left) {
                  q.push(top->left);
              }
              if (top->right) {
                  q.push(top->right);
              }
          }
          result.push_back(vec);
      }
      return result;
  }
};

// dfs
class Solution2 {
 public:
  void preorder(TreeNode *root, int level, vector<vector<int>> &result) {
      // recursion terminator
      if (!root) return;

      // process current level
      if (result.size() == level) {
//          result.push_back(vector<int>());
          result.emplace_back(); //推荐使用这种方式
      }
      result[level].push_back(root->val);

      // drill down
      preorder(root->left, level + 1, result);
      preorder(root->right, level + 1, result);
  }

  vector<vector<int>> levelOrder(TreeNode *root) {
      vector<vector<int>> result;
      preorder(root, 0, result);
      return result;
  }
};
```



#### Binary-Tree-Level-Order-Traversal-II-107

```cpp
//
// Created by 张达 on 2020/9/1.
//

#include <vector>
#include <queue>
#include <stack>
#include <search.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

// 利用一个栈进行顺序的颠倒
class Solution1 {
 public:
  vector<vector<int>> levelOrderBottom(TreeNode* root) {
      vector<vector<int>> result;
      stack<vector<int>> s;

      if (!root) {
          return result;
      }
      queue<TreeNode *> q;
      q.push(root);

      while (!q.empty()) {
          int len = q.size();
          vector<int> vec;
          while (len--) {
              auto top = q.front();
              q.pop();
              vec.push_back(top->val);

              if (top->left) {
                  q.push(top->left);
              }
              if (top->right) {
                  q.push(top->right);
              }
          }
          s.push(vec);
      }

      while (!s.empty()) {
          result.push_back(s.top());
          s.pop();
      }
      return result;
  }
};


// 利用一个栈进行顺序的颠倒
// dfs
class Solution {
 public:
  void preorder(TreeNode* root, int level, vector<vector<int>>& result) {
      // recursion terminator
      if (!root) return ;

      // process current level logic
      if (level == result.size()) {
          result.emplace_back();
      }
      result[level].push_back(root->val);

      // drill down
      preorder(root->left, level + 1, result);
      preorder(root->right, level + 1, result);
  }

  vector<vector<int>> levelOrderBottom(TreeNode* root) {
      vector<vector<int>> result;
      preorder(root, 0, result);
      reverse(result.begin(), result.end());
      return result;
  }
};
```



#### Coin-Change-322

```cpp
//
// Created by 张达 on 2020/9/5.
//

#include <vector>
using namespace std;

// DFS + 倒序排序+ 强剪枝
class Solution {
 private:
  // s 相当于索引
  // amount 还剩多少
  // count 当前使用了多少个硬币
  // ans 最少使用的硬币数
  void coinChange(const vector<int> &coins, int s, int amount, int count, int &ans) {
      const int coin = coins[s]; // 当前最大的硬币

      // last element
      if (s == coins.size() - 1) {
          if (amount % coin == 0) {
              ans = min(ans, count + amount / coin);
          }
      } else { // 不是最后一个元素
          // 当前使用的硬币数量+即将使用的硬币数量 < ans
          // k-- 表示使用k枚，一直到0枚
          for (int k = amount / coin; k >= 0 and count + k < ans; k--) {
              // s+1 表示使用次大，次次大，次次次大，依次往后推
              coinChange(coins, s + 1, amount - k * coin, count + k, ans);
          }
      }
  }

 public:
  int coinChange(vector<int> &coins, int amount) {
      sort(coins.rbegin(), coins.rend());
      int ans = INT_MAX;
      coinChange(coins, 0, amount, 0, ans);
      return ans == INT_MAX ? -1 : ans;
  }
};



// (interesting but won't pass all tests),
// variant: inspired by the question that asks the number of combinations that can make the amount change happen
// however, this is DFS, time exceeds (no clear how to do memoization with this, but it's fun)
public int min = Integer.MAX_VALUE;
public int coinChange(int[] coins, int amount) {
    helper(coins, amount, coins.length-1, 0);
    return min==Integer.MAX_VALUE?-1:min;
}
public void helper(int[] coins, int amount, int i, int count)
{
    if(i<0||amount<0) return;
    if(amount==0) min = Math.min(min, count);
    helper(coins, amount-coins[i], i, count+1);
    helper(wcoins, amount, i-1, count);
}
```



#### Convert-Sorted-Array-to-Binary-Search-Tree-108

```
//
// Created by 张达 on 2020/9/3. 22:00 1/5
//


#include <vector>
#include <string>
#include <unordered_map>
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
  TreeNode* preorder(vector<int>& nums, int left, int right) {
    // recursion terminator
    if (left > right) return nullptr; // attention! here is not left >= right

    // process current level logic
    int mid = (left + right) / 2;
    TreeNode* root = new TreeNode(nums[mid]);

    // drill down
    root->left = preorder(nums, left, mid - 1);
    root->right = preorder(nums, mid + 1, right);
    return root;
  }

  TreeNode* sortedArrayToBST(vector<int>& nums) {
      if (nums.empty()) return nullptr;
      return preorder(nums, 0, nums.size() - 1);
  }
};
```



#### Decode-Ways-91

```cpp
//
// Created by 张达 on 2020/9/3. 1/5 08:06
//
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// recursion O(2^n)
// 思路：1只拆出头一个， 2只拆出头2个
class Solution {
 public:
  int recursion(const string &s, unordered_map<string, int> &map_str) {
      // recursion terminator
      if (s[0] == '0') return 0; // question requirement 注意，这个必须在最前面，因为和s.size() == 1条件有冲突
      if (s == "" || s.size() == 1) return 1;
      if (map_str.count(s)) return map_str[s]; // already exist

      // drill down
      int cnt = recursion(s.substr(1), map_str);
      if (stoi(s.substr(0, 2)) <= 26) {
          cnt += recursion(s.substr(2), map_str);
      }

      // memorization
      map_str[s] = cnt;
      return cnt;
  }

  int numDecodings(string s) {
      if (s.empty()) return 0;
      unordered_map<string, int> map_str;
      map_str.emplace("", 1);
      return recursion(s, map_str);
  }
};

// manipulate index instead of string copy
// O(n) + O(n)
class Solution2 {
 public:
  int recursion(string& s, unordered_map<int, int>& map_str, int left, int right) {
      if (s[left] == '0') return 0;
      if (left >= right) return 1; // Single digit(left == right) or empty(left > right)
      if (map_str.count(left)) return map_str[left];

      int count = recursion(s, map_str, left + 1, right);

      int prefix = (s[left] - '0') * 10 + (s[left + 1] - '0');
      if (prefix <= 26) {
          count += recursion(s, map_str, left + 2, right);
      }

      map_str[left] = count;
      return count;
  }

  int numDecodings(string s) {
      if (s.empty()) return 0;
      unordered_map<int, int> map_str;
      return recursion(s, map_str, 0, s.size() - 1);
  }
};

int main() {
    Solution solve;
    solve.numDecodings("12");
}
```



#### DFS-template

```cpp
//
// Created by simida on 2020/09/01 08:03
//

// dfs的模板，递归形式和非递归形式，超哥说一定要练得滚瓜烂熟

#include <map>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

struct Node {
  int val;
  vector<Node *> children;
  Node(int val) : val(val) {}
};

class TemplateRecursion {
 public:
  map<int, int> visited;
  void dfs(Node *root) {
      // recursion terminator
      if (!root) {
          return;
      }
      if (visited.count(root->val)) {
          // already visited
          return;
      }

      visited[root->val] = 1;

      // process current node here

      // drill down
      for (int i = 0; i < root->children.size(); ++i) {
          dfs(root->children[i]);
      }
      return;
  }
};

class TemplateIteration {
 public:
// 非递归写法
  void dfs(Node *root) {
      map<int, int> visited;
      if (!root) return;

      stack<Node *> stack_node;
      stack_node.push(root);

      while (!stack_node.empty()) {
          Node * node = stack_node.top();
          stack_node.pop();
          if (visited.count(node->val)) {
              continue;
          }
          visited[node->val] = 1;
          for (int i = node->children.size() - 1; i >= 0; --i) {
              stack_node.push(node->children[i]);
          }
      }
      return;
  }

  int main() {
      std::cout << "Hello, World!" << std::endl;
      return 0;
  }
};
```



#### Fibonacci-Number-509

```cpp
//
// Created by 张达 on 2020/9/4. 1/5  09:16
//

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// time O(n) + space O(logn)
class Solution {
 private:
  unordered_map<int, int> map_n;
 public:
  int fib(int n) {
      // recursion terminator
      if (n == 0 or n == 1) return n;
      if (map_n.count(n)) {
          return map_n[n];
      }

      map_n[n] = fib(n - 1) + fib(n - 2);
      return map_n[n];
  }
};

// time O(n) + space O(1)
class Solution2 {
 public:
  int fib(int n) {
      if (n <= 1) return n;

      int f0 = 0, f1 = 1, f2 = 1;
      for (int i = 2; i <= n; ++i) {
          f2 = f0 + f1;
          f0 = f1;
          f1 = f2;
      }
      return f2;
  }
};
```



#### Find-Largest-Value-in-Each-Tree-Row-515

```cpp
//
// Created by 张达 on 2020/9/1. 22:21
//

#include <vector>
#include <queue>
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

// level-traversal
class Solution {
 public:
  vector<int> largestValues(TreeNode *root) {
      vector<int> result;
      if (!root) return result;
      queue<TreeNode *> q;
      q.push(root);
      while (!q.empty()) {
          int len = q.size();
          int max_v = INT_MIN;
          while (len--) {
              auto top = q.front();
              q.pop();
              max_v = max(max_v, top->val);
              if (top->left) {
                  q.push(top->left);
              }
              if (top->right) {
                  q.push(top->right);
              }
          }
          result.push_back(max_v);
      }
      return result;
  }
};

// DFS
class Solution2 {
 public:
  void preorder(TreeNode *root, int level, vector<vector<int>> &result) {
      // recursion terminator
      if (!root) return;

      // process current level logic
      if (level == result.size()) {
          result.emplace_back();
      }
      result[level].push_back(root->val);

      // drill down
      preorder(root->left, level + 1, result);
      preorder(root->right, level + 1, result);
  }

  vector<int> largestValues(TreeNode *root) {
      vector<vector<int>> result;
      vector<int> res;
      preorder(root, 0, result);
      for (int i = 0; i < result.size(); ++i) {
          res.push_back(*max_element(result[i].begin(), result[i].end()));
      }
      return res;
  }
};

// DFS
class Solution3 {
 public:
  void preorder(TreeNode *root, int level, vector<int> &result) {
      // recursion terminator
      if (!root) return;

      // 比较：如果当前访问的节点的值大于result[i]则更新
      // process current level logic
      if (level == result.size()) {
          result.emplace_back(root->val);
      } else {
          if (result[level] < root->val) {
              result[level] = root->val;
          }
      }

      // drill down
      preorder(root->left, level + 1, result);
      preorder(root->right, level + 1, result);
  }

  vector<int> largestValues(TreeNode *root) {
      vector<int> result;
      preorder(root, 0, result);
      return result;
  }
};
```



#### Find-Minimum-in-Rotated-Sorted-Array-153

```cpp
//
// Created by 张达 on 2020/9/6. 1/5 14:21
//

#include <vector>
using namespace std;

class Solution {
 public:
  int findMin(vector<int> &nums) {
      int len = nums.size();
      int begin = 0, end = len - 1;
      if (nums[len - 1] >= nums[begin]) return nums[begin];

      while (begin <= end) {
          int mid = (begin + end) / 2;
          if (nums[mid] > nums[mid + 1]) {
              return nums[mid + 1];
          } else if (nums[mid] < nums[begin]) { // 说明旋转数组在左半边
              end = mid - 1;
          } else {
              begin = mid + 1;
          }
      }
      return -1;
  }
};
```



#### Generate-Parentheses-22

```cpp
//
// Created by 张达 on 2020/9/1. 3/5 21:52-22:08
//

#include <vector>
#include <string>
using namespace std;

class Solution {
 public:
  void preorder(int left, int right, int n, vector<string>& result, string str) {
        // recursion terminator
        if (left == n and right == n) {
            result.push_back(str);
            return;
        }

        // process current level logic
        // drill down
        if (left < n) {
            preorder(left + 1, right, n, result, str + "(");
        }
        if (right < left) {
            preorder(left, right + 1, n, result, str + ")");
        }
  }

  vector<string> generateParenthesis(int n) {
      vector<string> result;
      preorder(0, 0, n, result, "");
      return result;
  }
};
```



#### Lemonade-Change-860

```cpp
//
// Created by 张达 on 2020/9/5. 1/5 17:57
//

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// if
class Solution {
 public:
  bool lemonadeChange(vector<int> &bills) {
      int coin5 = 0;
      int coin10 = 0;
      for (int i = 0; i < bills.size(); ++i) {
          if (bills[i] == 5) coin5++;
          if (bills[i] == 10) coin10++, coin5--;
          if (bills[i] == 20) {
              if (coin10 > 0) coin10--, coin5--;
              else coin5 -= 3;
          }
          if (coin5 < 0) return false;
      }
      return true;
  }
};

// 思考如何泛化？面值有5，10，20，50，100，500
// 通过一个Map存储面值和个数的对应关系
// 如何对map中按照key大小排序？map本身有序，按照key从小到大
class Solution2 {
 public:
  bool lemonadeChange(vector<int> &bills) {
      map<int, int, greater<>> m;
      for (int i = 0; i < bills.size(); ++i) {
          m[bills[i]]++;
          if (bills[i] == 5) {
              continue;
          } else {
              int change = bills[i] - 5;
              auto iter = m.begin();
              while (change > 0 and iter != m.end()) {
                  int max_bill = iter->first;
                  if (change / max_bill > 0 and m[max_bill] > 0) {
                      change -= max_bill;
                      m[max_bill]--;
                  } else {
                      iter++;
                  }
              }
              if (change != 0 or m[5] < 0) return false;
          }
      }
      return true;
  }
};


class Solution22 {
 public:
  bool lemonadeChange(vector<int> &bills) {
      map<int, int, greater<>> m;
      for (int i = 0; i < bills.size(); ++i) {
          printf("bills[%d] = %d\n", i, bills[i]);
          m[bills[i]]++;
          if (bills[i] == 5) {
              continue;
          } else {
              int change = bills[i] - 5;
              printf("change = %d\n", change);
              auto iter = m.begin();
              while (change > 0 and iter != m.end()) {
                  int max_coin = iter->first;
                  printf("max_coin = %d, and m[max_coin] = %d\n", max_coin, m[max_coin]);
                  int num = change / max_coin;
                  if (num > 0 and m[max_coin] > 0) {
                      change = change - max_coin;
                      m[max_coin]--;
                  } else {
                      iter++;
                  }
              }
              printf("change = %d\n", change);
              if (!(change == 0 and m[5] >= 0)) return false;
          }
      }
      return true;
  }
};
```



#### Maximum-Product-Subarray-152

```cpp
//
// Created by 张达 on 2020/9/6. 1/5 11:15
//

#include <vector>
#include <stack>
using namespace std;


// solution 1 : force brute O(N^2)
// Time Limit Exceeded: 186 / 187 test cases passed.
class Solution {
 public:
  int maxProduct(vector<int>& nums) {
      int max_val = INT_MIN;
      for (int i = 0; i < nums.size(); ++i) {
          for (int j = i; j < nums.size(); ++j) {
              int pro = nums[i];
              for (int k = i+1; k <= j; ++k) {
                  pro *= nums[k];
              }
              max_val = max(max_val, pro);
          }
      }
      return max_val;
  }
};


// DP: time O(n) + space O(n)
// 定义状态: dp[i] 表示以i结尾最大子串
class Solution2 {
 public:
  int maxProduct(vector<int>& nums) {
      int n = nums.size();
      if (n == 0) return 0;
      vector<int> dp(n, 0);
      dp[0] = nums[0];
  }
};

// solution3: recursion + memorizaition
class Solution3 {
 public:
  int maxProduct(vector<int>& nums) {
      Integer[][] table = new Integer[nums.length][2];
      memo(nums.length - 1, nums, table);
      int max = nums[0];

      for (Integer[] t : table)
      for (Integer val : t)
          max = Math.max(val, max);

      return max;
  }

  Integer[]
  memo(int i, int[] nums, Integer[][] dp) {
      if (i == 0)
          dp[i] = new Integer[]{nums[0], nums[i]};
      if (dp[i][0] == null) {
          dp[i][0] =
              Math.min(memo(i - 1, nums, dp)[1] * nums[i], Math.min(memo(i - 1, nums, dp)[0] * nums[i], nums[i]));
          dp[i][1] =
              Math.max(memo(i - 1, nums, dp)[1] * nums[i], Math.max(memo(i - 1, nums, dp)[0] * nums[i], nums[i]));

      }
      return dp[i];
  }
};


// 还没有看
// https://leetcode.com/problems/maximum-product-subarray/discuss/48230/Possibly-simplest-solution-with-O(n)-time-complexity
int maxProduct(int A[], int n) {
    // store the result that is the max we have found so far
    int r = A[0];

    // imax/imin stores the max/min product of
    // subarray that ends with the current number A[i]
    for (int i = 1, imax = r, imin = r; i < n; i++) {
        // multiplied by a negative makes big number smaller, small number bigger
        // so we redefine the extremums by swapping them
        if (A[i] < 0)
            swap(imax, imin);

        // max/min product for the current number is either the current number itself
        // or the max/min by the previous number times the current one
        imax = max(A[i], imax * A[i]);
        imin = min(A[i], imin * A[i]);

        // the newly computed max value is a candidate for our global result
        r = max(r, imax);
    }
    return r;
}
```



#### Maximum-Subarray-53

```cpp
//
// Created by 张达 on 2020/9/6. 1/5 10:35
//

#include <vector>
#include <stack>
using namespace std;

// brute force O(N^2)
// Time Limit Exceeded: 200 / 202 test cases passed.
class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
      int max_val = INT_MIN;
      for (int i = 0; i < nums.size(); ++i) {
          for (int j = i; j < nums.size(); ++j) {
              int sum = 0; // 必须初始化，否则结果错误并且随机
              for (int k = i; k <= j; ++k) {
                  sum += nums[k];
              }
              max_val = max(sum, max_val);
          }
      }
      return max_val;
  }
};

// 动态规划
// 将问题转换为: 求以第n个数字结尾的最大字段和
// 再找出这n个结果中最大的，即为结果
// 定义状态： dp[i]表示以第i个数字结尾的最大字段和
// if dp[i-1] > 0 -> dp[i] = dp[i-1] + nums[i]
// else dp[i] = nums[i]
class Solution2 {
 public:
  int maxSubArray(vector<int>& nums) {
      int n = nums.size();
      if (n == 0) return 0;
      vector<int> dp(n, 0);
      dp[0] = nums[0];
      int max_val = dp[0];
      for (int i = 1; i < n; ++i) {
          dp[i] = max(dp[i-1] + nums[i], nums[i]);
          max_val = max(max_val, dp[i]);
      }
      return max_val;
  }
};

class Solution3 {
 public:
  int maxSubArray(vector<int>& nums) {
      int n = nums.size();
      if (n == 0) return 0;
      vector<int> dp(n, 0);
      dp[0] = nums[0];
      int max_val = dp[0];
      for (int i = 1; i < n; ++i) {
          if (dp[i - 1] > 0) {
              dp[i] = dp[i - 1] + nums[i];
          } else {
              dp[i] = nums[i];
          }
          max_val = max(max_val, dp[i]);
      }
      return max_val; // time O(n)
  }
};

class Solution4 {
 public:
  int maxSubArray(vector<int>& nums) {
      int n = nums.size();
      if (n == 0) return 0;
      vector<int> dp(n, 0);
      dp[0] = nums[0];
      int max_val = dp[0];
      for (int i = 1; i < n; ++i) {
          if (dp[i - 1] > 0) {
              dp[i] = dp[i - 1] + nums[i];
          } else {
              dp[i] = nums[i];
          }
      }
      return *max_element(dp.begin(), dp.end()); // time O(n) + O(n)
  }
};
```



#### Min-Cost-Climbing-Stairs-746

```cpp
//
// Created by 张达 on 2020/9/6. 1/5 09:07
//

#include <vector>
using namespace std;

// 非常经典的题目，需要做的滚瓜烂熟
// 可以先归纳，再推演， 即数学归纳法

// time O(n) +  space O(n)
// 使用了记忆化递归，避免了重复计算。用于记忆化的数组本身占用O(n)时间复杂度

// 题目定义为：跳到第n阶台阶需要花多少钱
class Solution {
 private:
  int recursion(vector<int> &cost, vector<int> &memo, int n) {
      // recursion terminator
      if (n <= 1) return 0; // 可以理解为，从未知的地方到第0或者第1阶台阶不花钱
      if (memo[n]) return memo[n];
      // drill down
      memo[n] = min(recursion(cost, memo, n - 1) + cost[n - 1], recursion(cost, memo, n - 2) + cost[n - 2]);
      // 跳到第n阶台阶的价钱 = min(跳到第n-1阶台阶价钱 + 第n-1阶台阶自身的价钱，或者跳到第n-2阶台阶价钱 + 第n-2阶台阶自身的价钱)
      return memo[n];
  }

 public:
  int minCostClimbingStairs(vector<int> &cost) {
      int n = cost.size();
      vector<int> memo(n + 1, 0);
      return recursion(cost, memo, n);
  }
};

```



#### Minimum-Genetic-Mutation-433

```cpp
//
// Created by 张达 on 2020/9/1. 1/5 22:08 - 09:05
//

#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <string>
using namespace std;

// 本题即为求最短路径
// 本题可以用127的解法进行，可能速度快
class Solution {
 public:
  int minMutation(string start, string end, vector<string> &bank) {
      if (start == end) return 0;

      // 将vector中的所以元素全部放入set中
      set<string> bank_set(bank.begin(), bank.end());

      char char_set[] = {'A', 'C', 'G', 'T'};
      int level = 0; // 表示层级
      set<string> visited; // 用于记录已访问过的元素，去重
      queue<string> q;

      q.push(start);
      visited.insert(start);

      while (!q.empty()) {
          int len = q.size();
          while (len--) {
              string curr = q.front();
              q.pop();
              // 找到了
              if (curr == end) {
                  return level;
              }
              for (int i = 0; i < curr.size(); ++i) {
                  // 每次替换一个字符，每个字符有4种选择
                  string next = curr;
                  for (const char &c: char_set) {
                      next[i] = c;
                      // 如果没有访问过（为了去掉自己），并且在bank_set中，则说明路径是同的
                      if (!visited.count(next) and bank_set.count(next)) {
                          visited.insert(next);
                          q.push(next);
                      }
                  }
              }
          }
          level++;
      }
      return -1;
  }
};
```



#### N-Queens-51

```cpp
//
// Created by 张达 on 2020/9/5. 2/5 12:31
//
#include <vector>
#include <string>
using namespace std;


class Solution {
 private:
  const vector<int> dx = {-1, 1, 0, 0, -1, -1, 1, 1};
  const vector<int> dy = {0, 0, -1, 1, -1, 1, -1, 1};
  void printChessBoard(vector<string> &location) {
      for (int m = 0; m < location.size(); ++m) {
          for (int n = 0; n < location[0].size(); ++n) {
              printf("%c ", location[m][n]);
          }
          printf("\n");
      }
      printf("\n");
  }

 public:
  void put_down_the_queen(int x, int y, vector<string>& mark) {
      for (int i = 0; i < mark.size(); ++i) {
          for (int j = 0; j < 8; ++j) {
              int new_x = x + i * dx[j];
              int new_y = y + i * dy[j];
              if (new_x >= 0 && new_x < mark.size() &&
                  new_y >= 0 && new_y < mark.size()) {
                  mark[new_x][new_y] = 'Q';
              }
          }
      }
  }

  void generate(int k, int n, vector<string> &location, vector<vector<string>> &result, vector<string> &mark) {
      if (k == n) {
          result.push_back(location);
          return;
      }
      for (int i = 0; i < n; ++i) {
          if (mark[k][i] == '.') {
              auto tmp = mark;
              location[k][i] = 'Q';
              put_down_the_queen(k, i, mark);
              printChessBoard(location);
              generate(k + 1, n, location, result, mark);

              location[k][i] = '.';
              mark = tmp;
          }
      }
  }

  vector<vector<string>> solveNQueens(int n) {
      vector<vector<string>> result;
      vector<string> location; // store a certain position result.
      vector<string> mark;
      for (int i = 0; i < n; ++i) {
          location.emplace_back("");
          location[i].append(n, '.');
          mark.emplace_back("");
          mark[i].append(n, '.');
      }
      generate(0, n, location, result, mark);
      return result;
  }
};
```



#### Number-of-Islands-200

```cpp
//
// Created by 张达 on 2020/9/1. 1/5  08:48
//

#include <vector>
#include <queue>
using namespace std;

class Solution {
 private:
  vector<int> dx = {-1, 1, 0, 0};
  vector<int> dy = {0, 0, -1, 1};

 public:
  void dfs(vector<vector<char>> &grid, int x, int y) {
      // recurion terminator
      if (x < 0 || y < 0 ||
          x >= grid.size() || y >= grid[0].size() ||
          '0' == grid[x][y]) {
          return;
      }

      // process current level
      grid[x][y] = '0';

      // drill down
      for (int k = 0; k < 4; ++k) {
          dfs(grid, dx[k] + x, dy[k] + y);
      }
  }

  void bfs(vector<vector<char>> &grid, int x, int y) {
      queue<pair<int, int>> q;
      q.emplace(x, y);
      grid[x][y] = '0';
      while (!q.empty()) {
          int xx = q.front().first;
          int yy = q.front().second;
          q.pop();
          for (int k = 0; k < 4; ++k) {
              int new_x = dx[k] + xx;
              int new_y = dy[k] + yy;
              if (!(new_x < 0 || new_y < 0 || new_x >= grid.size() || new_y >= grid[0].size() ||
                  '0' == grid[new_x][new_y])) {
                  grid[new_x][new_y] = '0';
                  q.emplace(new_x, new_y);
              }

          }
      }
  }

  int numIslands(vector<vector<char>> &grid) {
      int count = 0;
      for (int i = 0; i < grid.size(); ++i) {
          for (int j = 0; j < grid[i].size(); ++j) {
              if ('1' == grid[i][j]) {
                  ++count;
                  dfs(grid, i, j);
              }
          }
      }
      return count;
  }
};
```



#### Search-a-2D-Matrix-74

```cpp
//
// Created by 张达 on 2020/9/6.
//

#include <vector>
#include <stack>
using namespace std;

// 经典题目：需要做的滚瓜烂熟

// O(n^2) 遍历整个矩阵
// 题目特点是下一行的头元素都要比上一上的尾元素大，即串在一起为排序数组
// n * m matrix convert to an array => matrix[x][y] => a[x*m + y]
// an array convert to n * m matrix => a[x] => matrix[x/m][x%m]
class Solution {
 public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
      int m = matrix.size();
      int n = matrix[0].size();
      int begin = 0, end = m * n - 1;
      while (begin <= end) {
          int mid = (begin + end) / 2;
          if (matrix[mid / n][mid % n] == target) {
              return true;
          }
          if (matrix[mid / n][mid % n] < target) {
              begin = mid + 1;
          } else {
              end = mid - 1;
          }
      }
      return false;
  }
};
```



#### Search-a-2D-Matrix-II-240

```cpp
//
// Created by 张达 on 2020/9/6. 1/5 21:10
//

// 非常经典的题目，需要做的滚瓜烂熟。

#include <vector>
#include <stack>
using namespace std;

// time O(m+n)
// 题目特点是从右上角出发，左边递减，下边递增。
class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
      if (matrix.empty()) return false;
      int right = matrix[0].size() - 1;
      int top = 0;

      while (right >= 0 and top < matrix.size()) {
          if (matrix[top][right] == target) {
              return true;
          } else if (matrix[top][right] < target) {
              top++;
          } else{
              right--;
          }
      }
      return false;
  }
};
```



#### Search-in-Rotated-Sorted-Array-33

```cpp
//
// Created by 张达 on 2020/9/6. 3/5 15:35
//

// 虽然简单，但是容易出错，需要反复过遍数
// 注意判断旋转数组的位置

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <string>
using namespace std;

// 思路：二分查找，关键在于判断旋转点所在partition
// time O(logN)
// 返回索引，如果找不到就返回-1
// 题目条件：数组一定是被旋转过的，即一定不是正常的数组

class Solution {
 public:
  int search(vector<int> &nums, int target) {
      int begin = 0, end = nums.size() - 1;
      while (begin <= end) {
          int mid = (begin + end) / 2;
          if (nums[mid] == target) {
              return mid;
          } else if (nums[begin] > nums[mid]) { // 左旋转，右升序
              if (target < nums[mid] or target > nums[end]) { // 在左旋转
                  end = mid - 1;
              } else { //在右升序
                  begin = mid + 1;
              }
          } else {// 左升序，右旋转
              if (target > nums[mid] or target < nums[begin]) { //在左升序
                  begin = mid + 1;
              } else { // 在右旋转
                  end = mid - 1;
              }
          }
      }
      return -1;
  }
};

class Solution2 {
 public:
  int search(vector<int> &nums, int target) {
      int start = 0;
      int end = nums.size() - 1;
      while (start <= end) {
          int mid = (start + end) / 2;
          if (nums[mid] < target) {
              // 判断是否旋转数组，并确定旋转点所在分段
              if (nums[start] > nums[mid] && nums[end] < target) { // 左旋转，右升序
                  end = mid - 1; // 在左旋转
              } else { // 正常情况
                  start = mid + 1; // 在右升序
              }
          } else if (nums[mid] > target) {
              if (nums[end] < nums[mid] and nums[start] > target) { // 左升序，右旋转
                  start = mid + 1;
              } else { // 正常情况
                  end = mid - 1;
              }
          } else {
              return mid;
          }
      }
      return -1;
  }
};
```



#### Sqrt(x)-69

```cpp
//
// Created by 张达 on 2020/9/7. 1/5 09:10
//

#include <vector>
#include <stack>
using namespace std;
// 未AC

// 只返回整数部分，截断小数部分
// 这里面有技巧和trick
class Solution {
 public:
  int mySqrt(int x) {
      if (x < 2) return x;
      int begin = 0, end = x;

      while (begin <= end) {
          int mid = (begin + end) / 2;
          if (x / mid == mid) {
              return mid;
          } else if (x / mid < mid) {
              end = mid - 1;

          } else {
              begin = mid + 1;
          }
      }
      return 0;
  }
};

//Similar idea, a little cleaner implementation. I used the trick m=(l+r+1)/2, something I learned from others on Leetcode, basically to tilt the mid calculations towards to the right (instead of to the left from default c++ integer division flooring).

int mySqrt(int x) {
    int l = 0, r = x;
    while (l < r) {
        int m = (l + r + 1) / 2;
        // 这里的int可能越界
        if (m > x / m) r = m - 1;
        else l = m;
    }
    return r;
}

```



#### Unique-Paths-62

```cpp
//
// Created by 张达 on 2020/9/4.
//

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

class Solution {
 private:
  int help(int m, int n, vector<vector<int>> &memo) {
      // recursion terminator
      if (m < 1 or n < 1) return 0;
      if (m == 1 or n == 1) return 1;
      if (memo[m][n]) return memo[m][n]; // already exist

      memo[m][n] = help(m - 1, n, memo) + help(m, n - 1, memo);
      return memo[m][n];
  }

 public:
  int uniquePaths(int m, int n) {
      vector<vector<int>> memo(m + 1, vector<int>(n + 1, 0)); // 注意这种写法
      return help(m, n, memo);
  }
};
```



#### Unique-Paths-II-63

```cpp
//
// Created by 张达 on 2020/9/5.
//

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

class Solution {
 private:
  int help(int m, int n, vector<vector<int>> &memo, vector<vector<int>> &obstacleGrid) {
      if (m == 1 and n == 1) return 1 - obstacleGrid[0][0];
      if (m < 1 or n < 1) return 0;
      if (memo[m][n] != -1) return memo[m][n];
      if (obstacleGrid[m - 1][n - 1] == 1) {
          memo[m][n] = 0;
      } else {
          memo[m][n] = help(m - 1, n, memo, obstacleGrid) + help(m, n - 1, memo, obstacleGrid);
      }
      return memo[m][n];
  }

 public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
      if (obstacleGrid.empty()) return 0;
      int m = obstacleGrid.size();
      int n = obstacleGrid[0].size();
      vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
      return help(m, n, memo, obstacleGrid);
  }
};
```



#### Unique-Paths-III-980

```cpp
//
// Created by 张达 on 2020/9/5. 1/5 10:35
//

// 哈密尔顿路径
// 从起点到终点的路径，每个节点当且仅当遍历一次

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// 递归：从终点的四个方向的路径个数加在一起即为最终的路径数
class Solution {
 private:
  int dfs(vector<vector<int>> &grid, int x, int y, int n) {
      if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() ||
          grid[x][y] == -1) {
          return 0;
      }
      if (grid[x][y] == 2) return n == 0;
      grid[x][y] = -1; // mark to void dead loop
      int path = dfs(grid, x + 1, y, n - 1) +
          dfs(grid, x - 1, y, n - 1) +
          dfs(grid, x, y - 1, n - 1) +
          dfs(grid, x, y + 1, n - 1);
      grid[x][y] = 0;
      return path;
  }

 public:
  int uniquePathsIII(vector<vector<int>> &grid) {
      int sx = -1;
      int sy = -1;
      int n = 1; // 至少要走一步
      for (int i = 0; i < grid.size(); ++i) {
          for (int j = 0; j < grid[0].size(); ++j) {
              if (grid[i][j] == 0) {
                  n++;
              } else if (grid[i][j] == 1) {
                  sx = i;
                  sy = j;
              }
          }
      }
      return dfs(grid, sx, sy, n);
  }
};

class Solution2 {
 private:
  const vector<int> dx = {1, -1, 0, 0};
  const vector<int> dy = {0, 0, -1, 1};

  int dfs(vector<vector<int>> &grid, int x, int y, int n) {
      if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() ||
          grid[x][y] == -1) {
          return 0;
      }
      if (grid[x][y] == 2) return n == 0;
      grid[x][y] = -1; // mark to void dead loop
      int path = 0;
      for (int i = 0; i < 4; ++i) {
          path += dfs(grid, x + dx[i], y + dy[i], n - 1);
      }
      grid[x][y] = 0;
      return path;
  }

 public:
  int uniquePathsIII(vector<vector<int>> &grid) {
      int sx = -1, sy = -1;
      int n = 1;
      for (int i = 0; i < grid.size(); ++i) {
          for (int j = 0; j < grid[0].size(); ++j) {
              if (grid[i][j] == 0) {
                  n++;
              } else if (grid[i][j] == 1) {
                  sx = i; sy = j;
              }
          }
      }
      return dfs(grid, sx, sy, n);
  }
};
```



#### Valid-Perfect-Square-367

```cpp
//
// Created by 张达 on 2020/9/7. 1/5 09:10
//


#include <vector>
#include <stack>
using namespace std;

class Solution {
 public:
  bool isPerfectSquare(int num) {

  }
};
```



#### Word-Ladder-127

```cpp
//
// Created by 张达 on 2020/9/2. 1/5 18:50
//

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <string>
using namespace std;

// 这道题和基本最小变异，有区别么？
// 有区别的，基因变异是知道变异的所有可能性的结果(只能是ATCG中的一种)，但是这道题就不知道，需要自己构造
// 图的表示和构造
// BFS

// 简洁的代码
class Solution1 {
 public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
      set<string> set_word(wordList.begin(), wordList.end());
      set<string> visited;
      queue<string> q;
      q.emplace(beginWord);
      visited.emplace(beginWord);

      int ladder = 1;
      while (!q.empty()) {
          int len = q.size();
          while (len--) {
              string word = q.front();
              q.pop();
              if (word == endWord) {
                  return ladder;
              }
              for (int j = 0; j < word.size(); ++j) {
                  string next = word;
                  for (int k = 0; k < 26; ++k) {
                      next[j] = 'a' + k;
                      if (!visited.count(next) and set_word.count(next)) { // 未访问过，且在列表中
                          visited.emplace(next);
                          q.push(next);
                      }
                  }
              }
          }
          ladder++;
      }
      return 0;
  }
};


// 这种方法在复杂了，代码又臭又长，不利于快速写出
class Solution2 {
 public:
  bool connect(const string &word1, const string &word2) {
      int cnt = 0;
      for (int i = 0; i < word1.size(); ++i) {
          if (word1[i] != word2[i])
              cnt++;
      }
      return cnt == 1;
  }

  void construct_graph(string &begin_word, vector<string> &word_list, map<string, vector<string>> &graph) {
      word_list.push_back(begin_word); // 就算重复添加也没关系，后面或判重的
      for (int i = 0; i < word_list.size() - 1; ++i) {
          for (int j = i + 1; j < word_list.size(); ++j) {
              if (connect(word_list[i], word_list[j])) {
                  graph[word_list[i]].emplace_back(word_list[j]);
                  graph[word_list[j]].emplace_back(word_list[i]);
              }
          }
      }

  }

  int bfs(string &begin_word, string &end_word, map<string, vector<string>> &graph) {
      queue<string> q;
      set<string> visit;
      q.emplace(begin_word);
      int level = 1;
      while (!q.empty()) {
          int len = q.size();
          while (len--) {
              string node = q.front();
              q.pop();
              if (node == end_word) {
                  return level;
              }
              auto &neighbors = graph[node];
              for (int i = 0; i < neighbors.size(); ++i) {
                  // 保证每个word当且仅当被push一次
                  if (!visit.count(neighbors[i])) { // 为了去掉自己，或者已经走过的节点（因为这些节点已经添加进队列了），避免重复添加
                      q.push(neighbors[i]);
                      visit.insert(neighbors[i]);
                  }
              }
          }
          level++;
      }
      return 0;
  }

  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
      map<string, vector<string>> graph;
      construct_graph(beginWord, wordList, graph);
      return bfs(beginWord, endWord, graph);
  }
};
```

