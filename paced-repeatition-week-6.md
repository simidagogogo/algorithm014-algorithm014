# paced-repeatition-week-6



#### Longest-Common-Subsequence-1143

```
//
// Created by 张达 on 2020/9/20. 1/5  23:12
//

#include <string>
#include <vector>
using namespace std;

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



#### recursion-template

```
//
// Created by 张达 on 2020/9/20.
//


using namespace std;

void recur(int level, int param) {
    // recursion terminator
    if (level > MAX_LEVEL) {
        return;
    }

    // process current level

    // drill down
    process(level + 1, param);

    // reverse states
}
```

