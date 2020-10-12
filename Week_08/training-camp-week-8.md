# [DSA] training camp week-8

> 2020/09/28 - 2020/10/11



## 完成情况

| Title                     | Keywords         | Rounds |
| ------------------------- | ---------------- | ------ |
| 338. Counting-Bits        | Bit Manipulation | 1      |
| 190. Reverse-Bits         | Bit Manipulation | 1      |
| 191. Nunber-of-1-Bits     | Bit Manipulation | 1      |
| 50. Pow(x, n)             | Bit Manipulation | 4      |
| 231. Power-of-Two         | Bit Manipulation | 1      |
| 912. Sort-Array           | Sort             | 4      |
| 56. Merge-Intervals       | Sort             | 1      |
| 1122. Relative-Sort-Array | Sort             | 1      |
| 242. Valid-Anagram        | Sort             | 4      |
| 344. Reverse-String       | String           | 4      |



**338. Counting-Bits**

```c++
// 动态规划
// 打掉最后一个比特位1, 然后计数加1。使用 x &= x - 1 将该位设置为0
// f(x) = f(x & (x−1)) + 1;
// time complexity: O(n)
class Solution {
 public:
  vector<int> countBits(int num) {
      vector<int> res(num + 1, 0);
      for (int i = 1; i <= num; ++i) {
          res[i] = res[i & (i - 1)] + 1;
      }
      return res;
  }
};

// 递归 + 记忆化搜索
class Solution2 {
 public:
  vector<int> countBits(int num) {
      vector<int> res(num + 1, 0);
      vector<int> memo(num + 1, 0);
      for (int i = 1; i <= num; ++i) {
          res[i] = recur(i, memo);
      }
      return res;
  }

  int recur(int i, vector<int> &memo) {
      if (i == 0) return 0;
      if (memo[i]) return memo[i];
      memo[i] = recur(i & (i - 1), memo) + 1;
      return memo[i];
  }
};
```



**912. Sort-Array**

```c++
class Solution {
 public:
  vector<int> sortArray(vector<int> &arr) {
    quickSort(arr, 0, arr.size() - 1);
    return arr;
  }
  
  // 快速排序
  void quickSort(vector<int> &arr, int left, int right) {
      // recursion ternimator
      if (left >= right) return;

      // 一个partition + 两个sort
      int mid = partition(arr, left, right);
      // drill down
      quickSort(arr, left, mid - 1);
      quickSort(arr, mid + 1, right);
  }

  int partition(vector<int> &arr, int left, int right) {
      // 先从头部打出空缺，然后先从右向左扫荡，然后从左向右扫荡，最后要把空缺填上
      int pivot = arr[left];
      while (left < right) {
          while (left < right and arr[right] >= pivot) {
              right--;
          }
          if (left < right) {
              arr[left++] = arr[right];
          }

          while (left < right and arr[left] <= pivot) {
              left++;
          }
          if (left < right) {
              arr[right--] = arr[left];
          }
      }
      arr[left] = pivot; // 记得把空缺填上
      return left;
  }

  // 优化后的partition操作
  int partition2(vector<int>& arr, int left, int right) {
      // 将所有比最后一个元素小的元素放在最左边
      int pivot = right,  counter = left;
      for (int i = left; i < right; ++i) {
          if (arr[i] < arr[pivot]) {
              swap(arr[counter], arr[i]);
              counter++;
          }
      }
      swap(arr[counter], arr[pivot]);
      return counter;
  }
};
```

**190. Reverse-Bits**

```c++
class Solution {
 public:
  uint32_t reverseBits(uint32_t n) {
      uint32_t result = 0;
      for (int i = 0; i < 32; ++i) {
          result = (result << 1) + (n >> i & 1); // + 可以替换为|
      }
      return result;
  }
};

//recursive
class Solution2 {
 public:
  uint32_t recur(uint32_t n, int count){
      if(!n) return 0;
      return ((n & 1) << count) + recur(n >> 1, count - 1);
  }

  uint32_t reverseBits(uint32_t n) {
      return recur(n, 31);    
  }
};
```

**191. Nunber-of-1-Bits**

```c++
class Solution {
 public:
  int hammingWeight(uint32_t n) {
      int sum = 0;
      while (n) {
          sum++;
          n = n & (n - 1);
      }
      return sum;
  }
};
```

**50. Pow(x, n)**

```c++
class Solution {
 public:
  double myPow(double x, int n) {
      long N = labs(n); // Returns the absolute value of parameter n ( /n/ ).This is the long int version of abs.
      double res = 1.0;
      while (N) {
          if (N & 1) {
              res *= x;
          }
          x *= x;
          N = N >> 1;
      }
      return (n > 0) ? res : 1 / res;
  }
};

// 递归形式（类比加法）
class Solution2 {
 public:
  double myPow(double x, int n) {
      if (n == 0) return 1.0;
      long N = labs(n);
      double power = myPow(x * x, N >> 1) * (N & 1 ? x : 1);
      return n > 0 ? power : 1 / power;
  }
};
```

**231. Power-of-Two**

```c++
// 注意：2的幂次都是大于0的数
class Solution {
 public:
  bool isPowerOfTwo(int n) {
    return (n > 0) and (n & (n-1)) == 0;
  }
};
```

**912. Sort-Array**

```c++
class Solution {
  vector<int> sortArray(vector<int> &arr) {
      mergeSort(arr, 0, arr.size() - 1);
      return arr;
  }

  void mergeSort(vector<int>& arr, int left, int right) {
      if (left >= right) return;

      int mid = (left + right) >> 1;
      mergeSort(arr, left, mid);
      mergeSort(arr, mid + 1, right);
      merge(arr, left, mid, right);
  }

  void merge(vector<int>& arr, int left, int mid, int right) {
      vector<int> temp(right - left + 1);
      int l = left, r = mid + 1, k = 0;

      // 注意merge这种三段式的结构
      while (l <= mid and r <= right) {
          temp[k++] = (arr[l] <= arr[r]) ? arr[l++]: arr[r++];
      }
      while (l <= mid) {
          temp[k++] = arr[l++];
      }
      while (r <= right) {
          temp[k++] = arr[r++];
      }

      // 最后要把新开辟数组的内容移动回arr
      for (int i = 0; i < temp.size(); ++i) {
          arr[left + i] = temp[i];
      }
  }
};
```

**56. Merge-Intervals**

```c++
struct cmp {
 public:
  bool operator()(vector<int> &a, vector<int> &b) {
      return a[0] < b[0];
//      return *a.begin() < *b.begin(); // 这样可以，去掉*不可以，因为begin()得到的是类似于指针的迭代器
//      return a.front() < b.front();
  }
};

class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
      sort(intervals.begin(), intervals.end(), cmp());
      vector<vector<int>> res;
      for (int i = 0; i < intervals.size();) {
          int last_second = intervals[i][1];
          int j = i + 1;
          while (j < intervals.size() and intervals[j][0] < last_second) {
              last_second = max(last_second, intervals[j][1]);
              j++;
          }

          res.push_back({intervals[i][0], last_second});
          i = j;
      }
      return res;
  }
};

// 递归
// 如果不理解，可以尝试 N=3 的人肉递归，数学归纳法推理
class Solution2 {
 public:
  vector<vector<int>> recur(vector<vector<int>> intervals) {
      // recursion terminator
      if (intervals.size() <= 1) {
          return intervals;
      }

      // 下一个待merge元素
      auto next_ele = intervals[intervals.size() - 1];

      // drill down
      intervals.pop_back();
      auto merged = recur(intervals); // 已经完成merge的vector

      // 已经完成merge的vector中的最后一个元素
      auto last_ele = merged[merged.size() - 1];

      // 判断是否合并
      if (last_ele[1] >= next_ele[0]) {
          merged.pop_back();
          merged.push_back({last_ele[0], max(last_ele[1], next_ele[1])});
      } else {
          merged.push_back(next_ele);
      }
      return merged;
  }

  vector<vector<int>> merge(vector<vector<int>> &intervals) {
      sort(intervals.begin(), intervals.end(), cmp());
      return recur(intervals);
  }
};
```

**1122. Relative-Sort-Array**

```c++
class Solution {
 public:
  vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
      // 题目中有给数组元素的范围
      int hash_map[1001] = {0};

      for (const auto &it : arr1) {
          hash_map[it]++;
      }

      int i = 0;
      for (const auto &n : arr2) {
          while (hash_map[n]-- > 0) {
              arr1[i++] = n;
          }
      }

      for (int m = 0; m < 1001; ++m) {
          while (hash_map[m]-- > 0) {
              arr1[i++] = m;
          }
      }
      return arr1;
  }
};
```

**242. Valid-Anagram**

```c++
class Solution {
 public:
  bool isAnagram(string a, string b) {
      int m[128] = {0};
      for (const auto &s : a) {
          m[s]++;
      }
      for (const auto &s : b) {
          m[s]--;
      }
      for (const auto & i: m) {
          if (i) {
              return false;
          }
      }
      return true;
  }
};
```

**344. Reverse-String**

```c++
// 原地逆置, 采用双指针
class Solution {
 public:
  void reverseString(vector<char>& s) {
    int i = 0, j = s.size() - 1;
    while (i < j) {
        swap(s[i++], s[j--]);
    }
  }
};
```
