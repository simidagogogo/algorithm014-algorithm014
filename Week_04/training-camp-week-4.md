# [DSA] training camp week-4

> 2020/08/31-2020/09/06



## 完成情况

| Title                                           | Keywords               | Rounds |
| ----------------------------------------------- | ---------------------- | ------ |
| 455. Assign-Cookies                             | Greedy                 | 3/5    |
| 121. Best-Time-to-Buy-and-Sell-Stock            | DP                     | 1/5    |
| 102. Binary-Tree-Level-Order-Traversal          | BFS                    | 3/5    |
| 107. Binary-Tree-Level-Order-Traversal-II       | BFS                    | 3/5    |
| 322. Coin-Change                                | Recursion/Pruning      | 1/5    |
| 108. Convert-Sorted-Array-to-Binary-Search-Tree | Recurion/BST           | 1/5    |
| 91. Decode-Ways                                 | Recursion              | 1/5    |
| 509. Fibonacci-Number                           | Recursion/Memorization | 4/5    |
| 515. Find-Largest-Value-in-Each-Tree-Row        | BFS                    | 1/5    |
| 153. Find-Minimum-in-Rotated-Sorted-Array       | Binary search          | 1/5    |
| 22. Generate-Parentheses                        | Recursion/Pruning      | 3/5    |
| 860. Lemonade-Change                            | Greedy                 | 1/5    |
| 53. Maximum-Subarray                            | DP                     | 1/5    |
| 746. Min-Cost-Climbing-Stairs                   | Recursion/Memorization | 1/5    |
| 433. Minimum-Genetic-Mutation                   | BFS                    | 1/5    |
| 51. N-Queens                                    | DFS                    | 2/5    |
| 200. Number-of-Islands                          | DFS                    | 2/5    |
| 74. Search-a-2D-Matrix                          | Binary search          | 1/5    |
| 240. Search-a-2D-Matrix-II                      | Binary search          | 1/5    |
| 33. Search-in-Rotated-Sorted-Array              | Binary search          | 3/5    |
| 62. Unique-Paths                                | Recursion/Memorization | 1/5    |
| 63. Unique-Paths-II                             | Recursion/Memorization | 1/5    |
| 980. Unique-Paths-III                           | Recursion/Memorization | 1/5    |
| 127. Word-Ladder                                | BFS                    | 1/5    |



**455. Assign-Cookies**

```cpp
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



**121. Best-Time-to-Buy-and-Sell-Stock**

```cpp
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



**102. Binary-Tree-Level-Order-Traversal**

```cpp
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
```



**107. Binary-Tree-Level-Order-Traversal-II**

```cpp
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
```



**322. Coin-Change**

```cpp
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
```



**108. Convert-Sorted-Array-to-Binary-Search-Tree**

```cpp
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



**91. Decode-Ways**

```cpp
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
```



**509. Fibonacci-Number**

```cpp
// time O(n) + space O(n)
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



**515. Find-Largest-Value-in-Each-Tree-Row**

```cpp
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
```



**153. Find-Minimum-in-Rotated-Sorted-Array**

```cpp
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



**22. Generate-Parentheses**

```cpp
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



**860. Lemonade-Change**

```cpp
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
      int price = 5; 
      map<int, int, greater<>> m;
      for (int i = 0; i < bills.size(); ++i) {
          m[bills[i]]++;
          if (bills[i] == price) {
              continue;
          } else {
              int change = bills[i] - price;
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
```



**53. Maximum-Subarray**

```cpp
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
```



**746. Min-Cost-Climbing-Stairs**

```cpp
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



**433. Minimum-Genetic-Mutation**

```cpp
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



**51. N-Queens**

```cpp
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



**200. Number-of-Islands**

```cpp
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
                  dfs(grid, i, j); // bfs(grid, i, j);
              }
          }
      }
      return count;
  }
};
```



**74. Search-a-2D-Matrix**

```cpp
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



**240. Search-a-2D-Matrix-II**

```cpp
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



**33. Search-in-Rotated-Sorted-Array**

```cpp
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
```



**62. Unique-Paths**

```cpp
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



**63. Unique-Paths-II**

```cpp
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



**980. Unique-Paths-III**

```cpp
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



**127. Word-Ladder**

```cpp
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
```
