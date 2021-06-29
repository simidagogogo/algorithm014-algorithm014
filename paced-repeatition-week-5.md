# paced-repeatition-week-5



#### 4Sum-18

```cpp
//
// Created by 张达 on 2020/9/12. 1/5 18:43
//

//最牛逼之处在于：K数之和的通用模板

#include <vector>
using namespace std;

// K数之和的通用模板
class Solution {
 private:
  const int K = 4;
  int size;

  void search(const vector<int> &nums, int pos, int k, int target, vector<int> &v, vector<vector<int>> &result) {
      if (k == 2) {
          int l = pos, r = size - 1;
          while (l < r) {
              int t = nums[l] + nums[r];
              if (t > target) r--;
              else if (t < target) l++;
              else {
                  v.push_back(nums[l++]);
                  v.push_back(nums[r--]);
                  result.push_back(v);
                  v.pop_back(), v.pop_back();
                  while (l < r && nums[l] == nums[l - 1]) l++;
                  while (l < r && nums[r] == nums[r + 1]) r--;
              }
          }
      } else {
          for (int j = pos; j <= size - k; ++j) {
              int sum = 0;
              for (int i = j; i < k + j; ++i) sum += nums[i];
              if (sum > target) break;
              sum = nums[j];
              for (int i = 0; i < k - 1; ++i) sum += nums[size - 1 - i];
              if (sum < target) continue;
              v.push_back(nums[j]);
              search(nums, j + 1, k - 1, target - nums[j], v, result);
              v.pop_back();
              while (j <= size - k && nums[j + 1] == nums[j]) j++;
          }
      }
  }

 public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
      sort(nums.begin(), nums.end());
      size = nums.size();
      vector<int> v;
      vector<vector<int>> result;
      search(nums, 0, K, target, v, result);
      return result;
  }
};


/*
General Idea
If you have already read and implement the 3sum and 4sum by using the sorting approach: reduce them into 2sum at the end, you might already got the feeling that, all ksum problem can be divided into two problems:

2sum Problem
    Reduce K sum problem to K – 1 sum Problem
Therefore, the ideas is simple and straightforward. We could use recursive to solve this problem. Time complexity is O(N^(K-1)).
*/

public class Solution {
  int len = 0;
 public List<List<Integer>> fourSum(int[] nums, int target) {
      len = nums.length;
      Arrays.sort(nums);
      return kSum(nums, target, 4, 0);
  }
 private ArrayList<List<Integer>> kSum(int[] nums, int target, int k, int index) {
      ArrayList<List<Integer>> res = new ArrayList<List<Integer>>();
      if(index >= len) {
          return res;
      }
      if(k == 2) {
          int i = index, j = len - 1;
          while(i < j) {
              //find a pair
              if(target - nums[i] == nums[j]) {
                  List<Integer> temp = new ArrayList<>();
                  temp.add(nums[i]);
                  temp.add(target-nums[i]);
                  res.add(temp);
                  //skip duplication
                  while(i<j && nums[i]==nums[i+1]) i++;
                  while(i<j && nums[j-1]==nums[j]) j--;
                  i++;
                  j--;
                  //move left bound
              } else if (target - nums[i] > nums[j]) {
                  i++;
                  //move right bound
              } else {
                  j--;
              }
          }
      } else{
          for (int i = index; i < len - k + 1; i++) {
              //use current number to reduce ksum into k-1sum
              ArrayList<List<Integer>> temp = kSum(nums, target - nums[i], k-1, i+1);
              if(temp != null){
                  //add previous results
                  for (List<Integer> t : temp) {
                      t.add(0, nums[i]);
                  }
                  res.addAll(temp);
              }
              while (i < len-1 && nums[i] == nums[i+1]) {
                  //skip duplicated numbers
                  i++;
              }
          }
      }
      return res;
  }
}


class Solution5 {
 public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
      vector<vector<int>> res;
      if (nums.empty() || nums.size() < 4) return res;

      sort(nums.begin(), nums.end());
      for (int i = 0; i < nums.size() - 3; i++) {
          // case 1
          if (i > 0 && nums[i - 1] == nums[i]) continue;

          // case 2
          for (int j = i + 1; j < nums.size() - 2; j++) {
              // also case 1
              if (j > i + 1 && nums[j] == nums[j - 1]) continue;

              // alse case 2
              int left = j + 1, right = nums.size() - 1;
              while (left < right) {
                  int curr = nums[i] + nums[j] + nums[left] + nums[right];
                  if (curr > target) {
                      right--;
                  } else if (curr < target) {
                      left++;
                  } else {
                      res.push_back({nums[i], nums[j], nums[left], nums[right]});
                      left++;
                      right--;
                      while (left < right && nums[left] == nums[left - 1]) left++;
                      while (left < right && nums[right] == nums[right + 1]) right--;
                  }
              }
          }
      }
      return res;
  }
};
```



#### Best-Time-to-Buy-and-Sell-Stock-II-122

```cpp
//
// Created by 张达 on 2020/9/9.
//

#include <vector>
using namespace std;

// 思路，只要后面的数比前面大，即可相加
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int result = 0;
      for (int i = 1; i < prices.size(); ++i) {
          if (prices[i] > prices[i - 1]) {
              result += prices[i] - prices[i - 1];
          }
      }
      return result;
  }
};

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/discuss/208241/Explanation-for-the-dummy-like-me.
// 相似的给出了，买入的价格，卖出的价格
public int maxProfit(int[] prices) {
    int i = 0, buy, sell, profit = 0, N = prices.length - 1;
    while (i < N) {
        while (i < N && prices[i + 1] <= prices[i]) i++;
        buy = prices[i];

        while (i < N && prices[i + 1] > prices[i]) i++;
        sell = prices[i];

        profit += sell - buy;
    }
    return profit;
}
```



#### Cousins-in-Binary-Tree-993

```cpp
//
// Created by 张达 on 2020/9/8. 1/5 10:30
//

#include <iostream>
#include <queue>
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

// 处于同一层，但是父节点不相同（树中的每个节点的值都是不同的）
// 思路：如何判断两个子节点的父节点不相同？
class Solution {
 public:
  bool isCousins(TreeNode *root, int A, int B) {
      if (root == nullptr) return false;
      queue<TreeNode *> queue;
      queue.push(root);
      while (!queue.empty()) {
          int size = queue.size();
          //进入每层之前，先初始化为falses
          bool isAexist = false;
          bool isBexist = false;
          while (size--) {
              auto cur = queue.front();
              queue.pop();
              if (cur->val == A) isAexist = true;
              if (cur->val == B) isBexist = true;

              // 这段代码用于判断是否为相同父节点
              if (cur->left != nullptr && cur->right != nullptr) { // cur的左右子树都不为空，即cur为父节点
                  if ((cur->left->val == A && cur->right->val == B) ||
                      (cur->left->val == B && cur->right->val == A)) { // 如果A和B为curr的左右子树, 则返回false
                      return false;
                  }
              }

              if (cur->left != nullptr) {
                  queue.push(cur->left);
              }
              if (cur->right != nullptr) {
                  queue.push(cur->right);
              }
          }
          if (isAexist && isBexist) return true;
      }
      return false;
  }
};

// 非常简洁和优雅的代码
// 我还是更喜欢递归的写法
class Solution2 {
 public:
  bool isCousins(TreeNode *root, int x, int y) {
      unordered_map<int, pair<int, int>> m; // 记录节点val和节点对应的深度和父节点的值
      helper(root, 0, -1, m);
      return m[x].first == m[y].first && m[x].second != m[y].second; //深度相同，但是父节点不相同
  }

  // node 当前节点
  // depth 深度
  // 父节点的值
  // 节点值对应的深度和父节点的值
  void helper(TreeNode *node, int depth, int parent, unordered_map<int, pair<int, int>> &m) {
      if (!node) return;
      m[node->val] = {depth, parent};
      helper(node->left, depth + 1, node->val, m);
      helper(node->right, depth + 1, node->val, m);
  }
};
```



#### Find-All-Duplicates-in-an-Array-442

```cpp
//
// Created by 张达 on 2020/9/12.
//

class Solution {
 public:
  vector<int> findDuplicates(vector<int>& nums) {

  }
};
```



#### Jump-Game-55

```cpp
//
// Created by 张达 on 2020/9/10. 1/5 09:47
//

#include <vector>
using namespace std;

// time O(n) space O(1)
// 思路：如果能往前跳，就记录能跳到的最远位置，比较最远位置是否到达末尾，只要到达末尾，即return true
class Solution {
 public:
  bool canJump(vector<int> &nums) {
      int max_i = 0;
      for (int i = 0; i < nums.size() and i <= max_i; ++i) {
          max_i = max(max_i, i + nums[i]);
          if (max_i >= nums.size() - 1) {
              return true;
          }
      }
      return false;
  }
};

// 这个写法更简单，但时间复杂度也更高
class Solution2 {
 public:
  bool canJump(vector<int> &nums) {
      int max_i = 0;
      for (int i = 0; i < nums.size() and i <= max_i; ++i) {
          max_i = max(max_i, i + nums[i]);
      }
      return max_i >= (nums.size() - 1);
  }
};
```



#### Jump-Game-II-45

```cpp
//
// Created by 张达 on 2020/9/13.
//
#include <vector>
using namespace std;

// 贪心思想：尽可能多的往前走，如果无法继续往前走了，就必须跳了
class Solution {
 public:
  int jump(vector<int>& nums) {
      if (nums.size() < 2) return 0;

      int current = nums[0], max_i = nums[0], jump = 1;
      for (int i = 0; i < nums.size(); ++i) {
          if (i > current) {
              jump++;
              current = max_i;
          }
          max_i = max(nums[i] + i, max_i);
      }
      return jump;
  }
};
```



#### Merge-Sorted-Array-88

```cpp
//
// Created by 张达 on 2020/9/12.
//

#include <vector>
#include <iostream>
using namespace std;

// 最简洁的写法
class Solution {
 public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
      int i = m - 1, j = n - 1, last = m + n - 1;
      while (j >= 0) {
          if (i < 0 or nums1[i] <= nums2[j]) {
              nums1[last--] = nums2[j--];
          } else {
              nums1[last--] = nums1[i--];
          }
      }
  }
};

// 从后往前移动，谁大谁先上
class Solution2 {
 public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
      int i = m - 1;
      int j = n - 1;
      int k = m + n - 1;
      while (i >= 0 and j >= 0) {
          if (nums1[i] <= nums2[j]) {
              nums1[k--] = nums2[j--];
          } else {
              nums1[k--] = nums1[i--];
          }
      }
      //如果nums1中的元素都要比num2中的元素大，最后要把所有nums2中的元素拽到nums1中
      while (j >= 0) {
          nums1[k--] = nums2[j--];
      }
  }
};

// 此方法不推荐
// 开辟一个O(n)的空间，从前往后比较，谁小就选谁
class Solution3 {
 public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
      vector<int> tmp;
      int i = 0, j = 0, k = 0;
      while (i < m and j < n) {
          if (nums1[i] <= nums2[j]) {
              tmp.push_back(nums1[i++]);
          } else {
              tmp.push_back(nums2[j++]);
          }
      }
      while (i < m) tmp.push_back(nums1[i++]);
      while (j < n) tmp.push_back(nums2[j++]);
      nums1 = tmp;
  }
};

inline ostream operator<<(ostream cout, vector<int> nums) {
    for (int i = 0; i < nums.size(); ++i) {

    }
}

int main() {
    Solution3 solve;
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    int m = 3, n = 3;
    solve.merge(nums1, m, nums2, n);
//    cout << nums1 <<
}

```



#### Minimum-Path-Sum-64

```cpp
//
// Created by 张达 on 2020/9/11. 1/5 08:30 - 09:15
//

// 非常经典的动态规划题，需要写的滚瓜烂熟

#include <vector>
using namespace std;

// recursion + memorization (from top to bottom)
// time O(mn) space O(mn)
class Solution {
 private:
  vector<vector<int>> memo;

  int recurse(const vector<vector<int>> &grid, int x, int y) {
      if (x == 0 and y == 0) return grid[x][y];
      if (x < 0 or y < 0) return INT_MAX;
      if (memo[x][y] > 0) return memo[x][y];
      int ans = grid[x][y] + min(recurse(grid, x - 1, y), recurse(grid, x, y - 1));
      return memo[x][y] = ans;
  }
 public:
  int minPathSum(vector<vector<int>> &grid) {
      int m = grid.size();
      if (m == 0) return 0;
      int n = grid[0].size();
      memo = vector<vector<int>>(m, vector<int>(n, 0));
      return recurse(grid, m - 1, n - 1);
  }
};

class Solution2 {
 private:
  int recurse(const vector<vector<int>> &grid, vector<vector<int>>& memo, int x, int y) {
      if (x == 0 and y == 0) return grid[x][y];
      if (x < 0 or y < 0) return INT_MAX;
      if (memo[x][y] > 0) return memo[x][y];
      int ans = grid[x][y] + min(recurse(grid, memo, x - 1, y), recurse(grid, memo, x, y - 1));
      return memo[x][y] = ans;
  }

 public:
  int minPathSum(vector<vector<int>> &grid) {
      int m = grid.size();
      if (m == 0) return 0;
      int n = grid[0].size();
      vector<vector<int>> memo(m, vector<int>(n, 0));
      return recurse(grid, memo, m - 1, n - 1);
  }
};

// dp (from bottom to top)
// dp[i][j] min path sum to (i, j)
// dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1])
// bounder

// 通过overwrite grid 将空间复杂度降到O(1)
class Solution3 {
 public:
  int minPathSum(vector<vector<int>> &grid) {
    int m = grid.size();
    if (m == 0) return 0;
    int n = grid[0].size();
      for (int i = 0; i < m; ++i) {
          for (int j = 0; j < n; ++j) {
              if (i == 0 and j ==0) continue;
              else if (i == 0) {
                  grid[i][j] += grid[i][j - 1];
              } else if (j == 0) {
                  grid[i][j] += grid[i - 1][j];
              } else {
                  grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
              }
          }
      }
      return grid[m - 1][n - 1];
  }
};
```



#### Number-of-Steps-to-Reduce-a-Number-to-Zero-1342

```cpp
//
// Created by 张达 on 2020/9/12.
//

#include <vector>
using namespace std;

class Solution {
 public:
  int numberOfSteps (int num) {
      int cnt = 0;
      if (!num) return 0;
      while (num) {
          if (num & 1) {
              num = num - 1;
              cnt++;
          }
          num = num >> 1;
          cnt++;
      }
      return cnt - 1;
  }
};
```



#### Shuffle-String-1528

```cpp
//
// Created by 张达 on 2020/9/12.
//

#include <string>
#include <vector>
using namespace std;

// time O(n) + space O(n)
class Solution {
 public:
  string restoreString(string s, vector<int> &indices) {
      string result(s);
      for (int i = 0; i < s.size(); ++i) {
          result[indices[i]] = s[i];
      }
      return result;
  }
};

// cyclic sort 循环排序
// time O(n) + space O(1)
class Solution2{
 public:
  string restoreString(string s, vector<int> &indices) {
      for (int i = 0; i < indices.size(); i++) {
          while (indices[i] != i) {
              swap(s[i], s[indices[i]]);
              swap(indices[i], indices[indices[i]]);
          }
      }
      return s;
  }
};

int main() {
    Solution2 solve;
    string str = "codeleet";
    vector<int> indices = {4,5,6,7,0,2,1,3};
    string s = solve.restoreString(str, indices);
    printf("%s\n", s.c_str());
}

```



##### Sort-Colors-75

```cpp
//
// Created by 张达 on 2020/9/12.
//

#include <vector>
namespace lc75 {
using namespace std;


class Solution {
 public:
  void sortColors(vector<int>& nums) {
      int l = 0, r = nums.size() - 1 ;
      for (int i = 0; i <= r; i++) {
          if (nums[i] == 0) swap(nums[i], nums[l++]);
          if (nums[i] == 2) swap(nums[i--], nums[r--]); // 切记，i要进行退格操作
      }
  }
};

}
```



#### Top-K-Frequent-Elements-347

```cpp
//
// Created by 张达 on 2020/9/8. 1/5 00:30
//

#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  static bool cmp(pair<int, int> a, pair<int, int> b) {
      return a.second > b.second;
  }

  vector<int> topKFrequent(vector<int> &nums, int k) {
      vector<int> result;
      map<int, int> tmp;
      for (const auto &i : nums) {
          tmp[i]++;
      }
      vector<pair<int, int>> vec(tmp.begin(), tmp.end());
      sort(vec.begin(), vec.end(), cmp);

      for (const auto &iter: vec) {
          if (k-- > 0) result.emplace_back(iter.first);
      }
      return result;
  }
};

// 这是最差的方法，time O(nlogn)，需要对整个数组进行排序，当数据量特别大时，不是最高效的算法
class Solution1 {
 public:
  // 如果这里不用static，下面sort就会报错，原因不明
  static bool cmp(pair<int, int> a, pair<int, int> b) {
      return a.second > b.second;
  }

  vector<int> topKFrequent(vector<int> &nums, int k) {
      vector<int> result;
      map<int, int> tmp;
      for (const auto &i : nums) {
          tmp[i]++;
      }
      vector<pair<int, int>> vec(tmp.begin(), tmp.end());
      sort(vec.begin(), vec.end(), cmp);
      vec.erase(vec.begin() + k, vec.end());
      for (const auto &iter: vec) {
          result.emplace_back(iter.first);
      }
      return result;
  }
};

// 优先队列
// 最大堆
class Solution2 {
 public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
      unordered_map<int, int> map;
      for (int num : nums) map[num]++;

      vector<int> result;
      // 大顶堆
      priority_queue<pair<int, int>, vector<pair<int, int>>, less<>> pq; // pair<first, second>: first is frequency,  second is number
      for (auto it = map.begin(); it != map.end(); it++) {
          pq.emplace(it->second, it->first);
          if (pq.size() > (int) map.size() - k) {
              result.emplace_back(pq.top().second); // 将堆的顶部元素放入result中，同时弹出
              pq.pop();
          }
      }
      return result;
  }
};


// 非常好的方法：桶排序
// space O(n) time O(n)?
class Solution3 {
 public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
      unordered_map<int, int> map_num; // 存储数字，以及对应的出现次数（出现零次的，不会有记录，极端情况为10个数，其中1出现了10次）
      for (int num : nums) {
          ++map_num[num];
      }

      vector<vector<int>> buckets(nums.size() + 1); // 按照出现次数分为size + 1个桶
      for (auto p : map_num) {
          buckets[p.second].push_back(p.first); // 表示将num放入它对应的出现频次的桶中
      }

      vector<int> result;
      for (int i = buckets.size() - 1; i >= 0; --i) {
          for (int num : buckets[i]) {
              result.push_back(num);
              if (result.size() == k) return result;
          }
      }
      return result;
  }
};

// 注意仔细比较和体会以下两种方法的区别
// 如果使用vector<string, int> 这种二元的堆，就需要自己定义cmp函数了
//Solution 4: Using a min heap. O(nlogk) 时间复杂度如何分析？
class Solution11 {
 public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
      unordered_map<int, int> counts;
      for (const auto& i : nums) {
          ++counts[i];
      }

      priority_queue<int, vector<int>, greater<int>> max_k; // 小顶堆
      for (const auto &i : counts) {
          max_k.push(i.second);
          // Size of the min heap is maintained at equal to or below k
          while (max_k.size() > k) max_k.pop();
      }

      vector<int> result;
      for (const auto &i : counts) {
          if (i.second >= max_k.top()) {
              result.push_back(i.first);
          }
      }
      return result;
  }
};


// 我不懂为什么a.second > b.second表示最小堆，为什么是反着的？
class Solution111 {
 private:
  struct cmp{
    cmp(){}
    ~cmp(){}
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
  };

 public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
      unordered_map<int, int> counts;
      for (const auto &i : nums) {
          ++counts[i];
      }

      priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> max_k; // 小顶堆
      for (const auto &i : counts) {
          max_k.push(i);
          // Size of the min heap is maintained at equal to or below k
          while (max_k.size() > k) max_k.pop();
      }

      vector<int> result;
      while (!max_k.empty()) {
          result.push_back(max_k.top().first);
          max_k.pop();
      }
      reverse(result.begin(), result.end());
      return result;
  }
};
```



#### Top-K-Frequent-Words-692

```cpp
//
// Created by 张达 on 2020/9/9. 1/5 08:43
//

#include <string>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>
using namespace std;

// 错误的写法，只能挑选出topK的word，但是无法保证相同频次word的次序
// priority queue
class Solution {
 public:
  vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> map_word;
      for (const auto &word: words) {
          ++map_word[word];
      }

      vector<string> result;
      priority_queue<int, vector<int>, greater<>> heap;
      for (const auto &m: map_word) {
          heap.push(m.second);
          while (heap.size() > k) {
              heap.pop();
          }
      }
      for (const auto &m: map_word) {
          if (m.second >= heap.top()){
              result.push_back(m.first);
          }
      }
      return result;
  }
};

class Solution2 {
 private:
  struct cmp{
    cmp(){}
    ~cmp(){}
    bool operator() (const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);
    }
  };

 public:
  vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> dict;
      for (const auto &word: words) {
          ++dict[word];
      }

      priority_queue<pair<string, int>, vector<pair<string, int>>, cmp> pq;
      for (const auto &d: dict) {
          pq.emplace(d); // 注意这种写法，极其简练
          if (pq.size() > k) pq.pop();
      }

      vector<string> result;
      while (!pq.empty()) {
          result.emplace_back(pq.top().first);
          pq.pop();
      }
      // 因为是小顶堆，所以如果直接输出result则是小到大。为了满足题意，必须逆转数组
      reverse(result.begin(), result.end());
      return result;
  }
};

class Solution3 {
 public:
  vector<string> topKFrequent(vector<string> &words, int k) {
      unordered_map<string, int> freq;
      for (const auto &w : words) {
          freq[w]++;
      }

      auto comp = [&](const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);
      };
      typedef priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(comp)> my_priority_queue_t;
      my_priority_queue_t pq(comp);

      for (auto w : freq) {
          pq.emplace(w.first, w.second);
          if (pq.size() > k) pq.pop();
      }

      vector<string> output;
      // 注意，这种写法不好，相当于插入output这个vector时，每次都把新元素插入第一个位置，会操作所有后续元素向后群移
      while (!pq.empty()) {
          output.insert(output.begin(), pq.top().first);
          pq.pop();
      }
      return output;
  }
};


// 没看懂
// using map & bucket sort, O(nlogn)
class Solution4 {
 public:
  vector<string> topKFrequent(vector<string>& words, int k) {
      map<string, int> cnt;
      for (auto& w : words)
          ++cnt[w];

      vector<vector<string>> bucket(words.size());
      for (auto it : cnt)
          bucket[it.second].push_back(it.first);

      vector<string> res;
      for (int i = (int)bucket.size() - 1; k > 0 && i >= 0; i--) {
          if (bucket[i].empty())
              continue;
          int n = min(k, (int)bucket[i].size());
          res.insert(res.end(), bucket[i].begin(), bucket[i].begin() + n);
          k -= n;
      }
      return res;
  }
};
```



#### Triangle-120

```cpp
//
// Created by 张达 on 2020/9/11. 1/5
//

// 非常经典的题目（不是很好理解）

#include <vector>
using namespace  std;

// dp
// f[i][j] = min(f[i-1][j], f[i-1][j-1]) + triangle[i-1][j-1]
// 状态定义：f[i][j] = minTotalOf(i, j)
class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
      int n = triangle.size();
      vector<vector<int>> f(n + 1, vector<int>(n + 1, INT_MAX));

      for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= i; ++j) {
              f[i][j] = triangle[i - 1][j - 1];
              if (i == 1 and j == 1) continue;
              if (j == 1) f[i][j] += f[i - 1][j];
              else if (j == i) f[i][j] += f[i - 1][j - 1];
              else f[i][j] += min(f[i - 1][j], f[i - 1][j - 1]);
          }
      return *min_element(f[n].cbegin(), f[n].cend());
  }
};

// 直接丢掉f数组，overwrite原始grid，即破坏掉了原始数据，从而将空间复杂度降到O(1)

// top-down
int minimumTotal1(vector<vector<int>>& triangle) {
    vector<int> res(triangle.size(), triangle[0][0]);
    for (unsigned int i = 1; i < triangle.size(); i++)
        for (int j = i; j >= 0; j--) {
            if (j == 0)
                res[0] += triangle[i][j];
            else if (j == i)
                res[j] = triangle[i][j] + res[j-1];
            else
                res[j] = triangle[i][j] + min(res[j-1], res[j]);
        }
    return *min_element(res.begin(), res.end());
}

// bottom-up
int minimumTotal(vector<vector<int>>& triangle) {
    vector<int> res = triangle.back();
    for (int i = triangle.size()-2; i >= 0; i--)
        for (unsigned int j = 0; j <= i; j++)
            res[j] = triangle[i][j] + min(res[j], res[j+1]);
    return res[0];
}
```
