**1143. Longest Common Subsequence**

```cpp
class Solution {
 public:
  int longestCommonSubsequence(string text1, string text2) {
      if (text1.empty() || text2.empty()) return 0;

      int m = text1.length();
      int n = text2.length();

      vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
      for (int i = 1; i <= m; ++i) {
          for (int j = 1; j <= n; ++j) {
              if (text1[i-1] == text2[j-1]) {
                  dp[i][j] = 1 + dp[i - 1][j - 1];
              } else {
                  dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
              }
          }
      }
      return dp[m][n];
  }
};
```



**70. Climbing Stairs**

```cpp
class Solution {
 private:
  int helper(int n, vector<int> &memo) {
      if (n <= 3) return n;
      if (memo[n] > 0) return memo[n];
			memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
      return memo[n];
  }
  
 public:
  int climbStairs(int n) {
      vector<int> memo(n + 1, 0);
      return helper(n, memo);
  }
};
```
