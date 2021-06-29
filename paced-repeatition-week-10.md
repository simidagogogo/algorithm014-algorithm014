# paced-repeatition-week-10



#### trapping-rain-water-42

```
//
// Created by 张达 on 2020/10/25 23:39.
//

#include <vector>
using namespace std;

class Solution {
 public:
  int trap(vector<int> &height) {
      int res = 0;
      int n = height.size();
      int left = 0, right = n - 1;
      int maxleft = 0, maxright = 0;
      while (left <= right) {
          if (height[left] <= height[right]) {
              maxleft = max(height[left], maxleft);
              res += maxleft - height[left++];
          } else {
              maxright = max(height[right], maxright);
              res += maxright - height[right--];
          }
      }
      return res;
  }
};

class Solution2 {
 public:
  int trap(vector<int> &height) {
      const int n = height.size();
      int ans = 0;
      auto begin_it = height.begin();
      auto end_it = height.end();
      for (int i = 0; i < n; ++i) {
          int l = *max_element(begin_it, begin_it + i + 1);
          int r = *max_element(begin_it + i, end_it);
          ans += min(l, r) - height[i];
      }
      return ans;
  }
};

class Solution3 {
 public:
  int trap(vector<int> &height) {
      const int n = height.size();
      vector<int> l(n, 0);
      vector<int> r(n, 0);
      int res = 0;
      for (int i = 0; i < n; ++i) {
          l[i] = (i == 0) ? height[i] : min(height[i], l[i - 1]);
      }
      for (int i = n - 1; i >= 0; --i) {
          r[i] = (i == n - 1) ? height[i] : min(height[i], r[i + 1]);
      }
      for (int i = 0; i < n; ++i) {
          res += min(l[i], r[i]) - height[i];
      }
      return res;
  }
};
```
