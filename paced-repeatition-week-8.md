# paced-repeatition-week-8



### bubbleSort-912

```cpp
//
// Created by 张达 on 2020/10/12 19:04.
//
#include <vector>
using namespace std;


// bubble sort
// 每次遍历，都把最大的元素往尾巴甩
class Solution {
 public:
  vector<int> sortArray(vector<int>& arr) {
      return bubbleSort(arr);
  }

  vector<int> bubbleSort(vector<int>& arr) {
      for (int i = 0; i < arr.size() - 1; ++i) {
          for (int j = 0; j < arr.size() - 1 - i; ++j) {
              if (arr[j] > arr[j + 1]) {
                  swap(arr[j], arr[j + 1]);
              }
          }
      }
      return arr;
  }
};
```



#### bucketSort-912

```cpp
//
// Created by 张达 on 2020/10/12 20:38.
//

// C++ program to sort an array using bucket sort

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 划分多个范围相同的区间，每个子区间自排序，最后合并
class Solution {
 public:
  // 0到1之间的double排序
  vector<int> sortArray(vector<int>& arr) {
      bucketSortInterger(arr);
      return arr;
  }

  void bucketSort(vector<float> &arr) {
      int bucket_num = arr.size();
      // 1) Create bucket_num empty buckets
      vector<float> bucket[bucket_num];

      // 2) Put array elements in different buckets
      for (int i = 0; i < bucket_num; i++) {
          int num = (int) (bucket_num * arr[i]); // Index in bucket 关键在于映射函数的选取
          bucket[num].push_back(arr[i]);
      }

      // 3) Sort individual buckets
      for (int i = 0; i < bucket_num; i++)
          sort(bucket[i].begin(), bucket[i].end());

      // 4) Concatenate all buckets into arr[]
      int index = 0;
      for (int i = 0; i < bucket_num; i++)
          for (int j = 0; j < bucket[i].size(); j++)
              arr[index++] = bucket[i][j];
  }

// 整数排序
  void bucketSortInterger(vector<int> &arr) {
      int max_value = *max_element(arr.begin(), arr.end());
      int min_value = *min_element(arr.begin(), arr.end());
      int bucket_num = (max_value - min_value) / arr.size() + 1;

      // 1) Create n empty buckets
      vector<vector<int>> bucket_arr(bucket_num);

      for (int i = 0; i < bucket_num; ++i) {
          bucket_arr.emplace_back();
      }

      // 2) Put array elements in different buckets
      for (int i = 0; i < arr.size(); ++i) {
          int num = (arr[i] - min_value) / arr.size(); // 关键在于映射函数的选取
          bucket_arr[num].emplace_back(arr[i]);
      }

      // 3) Sort individual buckets
      for (auto &i : bucket_arr) {
          sort(i.begin(), i.end()); // 这里可换为插入排序
      }

      // 4) Concatenate all buckets into arr[]
      int index = 0;
      for (int i = 0; i < bucket_arr.size(); ++i) {
          for (int j = 0; j < bucket_arr[i].size(); ++j) {
              arr[index++] = bucket_arr[i][j];
          }
      }
  }
};

/* Driver program to test above function */
int main() {
    Solution solve;
    vector<float> arr = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
//    vector<int> arr = {54,2,5,43,22,1,788,5};
    int n = arr.size();

//    solve.bucketSortInterger(arr);
    solve.bucketSort(arr);

    cout << "Sorted array is \n";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    return 0;
}

```



#### char-count-by-hash

```cpp
//
// Created by 张达 on 2020/10/11.
//

#include <vector>
#include <string>
using namespace std;

class Solution {
 public:
  void charCount(string str) {
      int char_map[128] = {0};
      for (int i = 0; i < str.size(); ++i) {
          char_map[str[i]]++;
      }

      for (int i = 0; i < 128; ++i) {
          while (char_map[i]-- > 0) {
              printf("%c:%d \n", i, i);
          }
      }
  }
};

int main() {
    Solution solve;
    solve.charCount("adfafdsaf");
}
```



#### Counting-Bits-338

```cpp
//
// Created by 张达 on 2020/10/8. 15:05
//

#include <vector>
using namespace std;

// time complexity: O(nk), k为int的比特数32
class Solution {
 public:
  vector<int> countBits(int num) {
      vector<int> result(num + 1, 0);
      for (int i = 0; i <= num; ++i) {
          int sum = 0;
          int index = i;
          while (index) {
              sum++;
              index = index & (index - 1);
          }
          result[i] = sum;
      }
      return result;
  }
};

// 次最优解（动态规划 + 按照比特位逐个打掉）
// f(x) = f(x/2) + x%2
// time complexity: O(n)
class Solution2 {
 public:
  vector<int> countBits(int num) {
      vector<int> res(num + 1, 0);
      for (int i = 1; i <= num; ++i) {
          res[i] = res[(i >> 1)] + (i & 1);
      }
      return res;
  }
};

// 最优解（动态规划 + 打掉最后比特1位）
// 打掉最后一个1, 然后计数加1。使用 x &= x - 1 将该位设置为0，就可以得到以下状态转移函数：
// f(x)=f(x & (x−1)) + 1;
// time complexity: O(n)
class Solution3 {
 public:
  vector<int> countBits(int num) {
      vector<int> res(num + 1, 0);
      for (int i = 1; i <= num; ++i) {
          res[i] = res[i & (i - 1)] + 1;
      }
      return res;
  }
};

class Solution3_recursion_with_memorization {
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

int main() {
    Solution solve;
    int num = 5;
    vector<int> res = solve.countBits(num);
    for (const auto &item : res) {
        printf("%d\n", item);
    }
}
```



#### countingSort-912

```cpp
//
// Created by 张达 on 2020/10/12 19:12.
//

// 计数排序就是利用字符哈进行排序

#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> sortArray(vector<int>& arr) {
      int max_value = *max_element(arr.begin(), arr.end()); // 最大元素值， 通常由题目中给出
      countingSort(arr, max_value);
      return arr;
  }

  void countingSort(vector<int>& arr, int max_value) {
      vector<int> bucket(max_value + 1, 0);
      int sorted_index = 0;
      for (const auto & i : arr) {
          bucket[i]++;
      }

      for (int i = 0; i < max_value + 1; ++i) {
          while (bucket[i]-- > 0) {
              arr[sorted_index++] = i;
          }
      }
  }
};

struct Test {
 public:
  int test_sort(Solution solve) {
      vector<int> arr;
      srand(time(NULL));
      for (int i = 0; i < 100; ++i) {
          int num = rand() % 103;
          arr.emplace_back(num);
      }

      auto arr1 = arr;
      auto arr2 = arr;

      // 对arr1调用系统函数
      sort(arr1.begin(), arr1.end());

      // 对arr2调用自己的函数
      auto arr3 = solve.sortArray(arr2);

      assert(arr1.size() == arr3.size());
      for (int i = 0; i < arr1.size(); ++i) {
          assert(arr1[i] == arr3[i]);
      }
      for (const auto &item : arr3) {
          printf("%d\n", item);
      }
      return 0;
  }
};


int main() {
    Test test;
    Solution solve;
    int res = test.test_sort(solve);
    printf("%d\n", res);
}
```



#### Hanota

```cpp
//
// Created by 张达 on 2020/10/9. 20:00
//

#include <cstdio>
#include <vector>
using namespace std;

/*
 * a -> b  f(n-1)
 * a -> c
 * b -> c f(n-1)
 * f(n) = 2f(n - 1) + 1
 * */
class Solution {
 public:
  void hanota(int n, char a, char b, char c) {
      // recursion ternimator
      if (n == 0) return;

      //drill down
      hanota(n - 1, a, c, b);
      printf("%d: %c -> %c\n", n, a, c);
      hanota(n - 1, b, a, c);
  }
};


class Solution2 {
 public:
  void hanota(vector<int> &A, vector<int> &B, vector<int> &C) {
      inorder(A.size(), A, B, C);
  }

  void inorder(int n, vector<int> &A, vector<int> &B, vector<int> &C) {
      // recursion ternimator
      if (n == 0) return;

      // drill down
      inorder(n - 1,A, C, B);
      C.emplace_back(A.back());
      A.pop_back();
      inorder(n - 1,B ,A, C);
  }
};
```



### heapSort-912

```cpp
//
// Created by 张达 on 2020/10/10.
//

#include <vector>
#include <queue>
using namespace std;

class Solution {
 public:
  vector<int> heapSort(vector<int> &arr) {
    priority_queue<int, vector<int>, greater<>> q;
      for (int i = 0; i < arr.size(); ++i) {
          q.push(arr[i]);
      }
      for (int i = 0; i < arr.size(); ++i) {
          arr[i] = q.top();
          q.pop();
      }
      return arr;
  }

  vector<int> sortArray(vector<int> arr) {
        return heapSort(arr);
    }
};
```



#### Insertion-Sort

```cpp
//
// Created by 张达 on 2020/10/9. 11:01
//

// 插入排序：代码具有一定技巧，需要当做代码模板记下来

#include <vector>
using namespace std;

class Solution {
  vector<int> insertionSort(vector<int> arr) {
      int preIndex, current;
      for (int i = 1; i < arr.size(); ++i) {
          preIndex = i - 1;
          current = arr[i];
          // 如果当前元素小于之前元素，则把之前元素向后群移
          while (preIndex >= 0 && arr[preIndex] > current) {
              arr[preIndex + 1] = arr[preIndex];
              preIndex--; // 从后往前扫
          }
          arr[preIndex + 1] = current; // 当前元素的插入位置，+1是由于while中进行了preIndex--操作
      }
      return arr;
  }
};
```



#### insertionSort-912

```cpp
//
// Created by 张达 on 2020/10/12 19:04.
//
#include <vector>
using namespace std;

// 插入排序代码
class Solution {
 public:
  vector<int> sortArray(vector<int>& arr) {
      return insertionSort(arr);
  }

  vector<int> insertionSort(vector<int>& arr) {
      int preIndex, current;
      for (int i = 1; i < arr.size(); ++i) {
          preIndex = i - 1;
          current = arr[i]; // 把当前元素扣出来了
          // 如果当前元素小于之前元素，则把之前元素向后群移
          while (preIndex >= 0 && arr[preIndex] > current) {
              arr[preIndex + 1] = arr[preIndex];
              preIndex--; // 从后往前扫
          }
          arr[preIndex + 1] = current; // 当前元素的插入位置，+1是由于while中进行了preIndex--操作
      }
      return arr;
  }
};
```



#### integer-sort-by-hash

```cpp
//
// Created by 张达 on 2020/10/11 18:45.
//
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> integerSort(vector<int>& arr) {
      vector<int> res;
      int hash_map[10000] = {0};
      for (int i = 0; i < arr.size(); ++i) {
          hash_map[arr[i]]++;
      }

      for (int i = 0; i < 10000; ++i) {
          while (hash_map[i]-- > 0) {
              res.emplace_back(i);
          }
      }
      return res;
  }
};

struct Test {
 public:
  int test_sort(Solution solve) {
      vector<int> vec;
      srand(time(NULL));
      for (int i = 0; i < 100; ++i) {
          vec.push_back((rand()) % 1003);
      }

      vector<int> vec1 = solve.integerSort(vec);
      vector<int> vec2 = vec;

      sort(vec2.begin(), vec2.end());
      assert(vec1.size() == vec2.size());
      for (int i = 0; i < vec2.size(); ++i) {
          assert(vec1[i] == vec2[i]);
      }
      return 0;
  }
};

int main() {
    Solution solve;
    Test test;
    printf("%d\n", test.test_sort(solve));
}
```



#### Merge-Intervals-56

```cpp
//
// Created by 张达 on 2020/10/11. 10:05 1/5
//
#include <vector>
using namespace std;

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
          while (j < intervals.size() and intervals[j][0] < last_second) { // 如果上右 > 下左，就更新
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



#### mergeSort-912

```cpp
//
// Created by 张达 on 2020/10/10. 17:00
//

// 归并排序算法

#include <vector>
using namespace std;

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

      // 最后要把新开辟数组的内容移动回 arr
      for (int i = 0; i < temp.size(); ++i) {
          arr[left + i] = temp[i];
      }
  }
};
```



#### Number-of-1-Bits-191

```cpp
//
// Created by 张达 on 2020/10/8. 11:11
//

#include <cstdint>
using namespace std;

// 最优解
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

// 不断移位，看最后一位是否为1
class Solution2 {
 public:
  int hammingWeight(uint32_t n) {
      int sum = 0;
      while (n) {
          if (n & 1) {
              sum++;
          }
          n = n >> 1;
      }
      return sum;
  }
};
```



#### Pow(x, n)-50

```cpp
//
// Created by 张达 on 2020/10/8.
//
#include <algorithm>
using namespace std;

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



#### Power-of-Two-231

```cpp
//
// Created by 张达 on 2020/10/8. 14:55
//

// 注意：2的幂次都是大于0的数
class Solution {
 public:
  bool isPowerOfTwo(int n) {
    return (n > 0) and (n & (n-1)) == 0;
  }
};
```



#### QuickSort-912

```cpp
//
// Created by 张达 on 2020/10/9. 20:32
//

#include <vector>
#include <stdio.h>
using namespace std;

class Solution {
 public:
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

  vector<int> sortArray(vector<int> &arr) {
      quickSort(arr, 0, arr.size() - 1);
      return arr;
  }
};
```



### radixSort-912

```cpp
//
// Created by 张达 on 2020/10/16 18:23.
//

// C++ implementation of Radix Sort
// https://www.geeksforgeeks.org/radix-sort/
#include <vector>
#include <iostream>
using namespace std;

class Solution {
 public:
  vector<int> sortArray(vector<int>& arr) {
      radixSort(arr);
      return arr;
  }
  void radixSort(vector<int>& arr) {

  }

  void countSort(vector<int>& arr, int n, int exp) {
      vector<int> output(n);
      int i;
      vector<int> count(10, 0);

      for (int i = 0; i < n; ++i) {
          count[(arr[i] / exp) %10]++;
      }

      for (int i = 0; i < 10; ++i) {
          count[i] += count[i - 1];
      }

      for (int i = n - 1; i >= 0; --i) {
          output[count]()
      }

  }
};
```



### Relative-Sort-Array-1122

```cpp
//
// Created by 张达 on 2020/10/11. 15:30
//

#include <vector>
#include <map>
using namespace std;

// 哈希排序

/*
 * Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
 * Output: [2,2,2,1,4,3,3,9,6,7,19]
 * */

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

int main() {
    vector<int> a = {2,3,1,3,2,4,6,7,9,2,19};
    vector<int>  b = {2,1,4,3,9,6};
    Solution solve;

    auto r = solve.relativeSortArray(a, b);
    for (const auto &i : r) {
        printf("%d \n", i);
    }
}
```



#### Reverse-Bits-190

```cpp
//
// Created by 张达 on 2020/10/8. 11:27
//

#include <cstdint>
using namespace std;

// 非常经典
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


class Solution2 {
 public:
  uint32_t recur(uint32_t n, int count){
      if(!n) return 0;
      return ((n & 1) << count) + recur(n >> 1, count - 1);
  }

  uint32_t reverseBits(uint32_t n) {
      return recur(n, 31);    //recursive
  }
};
```



#### Reverse-String-344

```cpp
//
// Created by 张达 on 2020/10/8. 16:01
//
#include <vector>
using namespace std;

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



### selectSort-912

```cpp
//
// Created by 张达 on 2020/10/12 19:03.
//
#include <vector>
using namespace std;

// selection sort
// 每次排序，都把最小的元素往头部堆
class Solution {
 public:
  vector<int> sortArray(vector<int>& arr) {
      selectSort(arr);
      return arr;
  }

  void selectSort(vector<int>& arr) {
      int minIndex, temp;
      for (int i = 0; i < arr.size() - 1; ++i) {
          minIndex = i;
          for (int j = i + 1; j < arr.size(); ++j) {
              if (arr[j] < arr[minIndex]) { // 找到元素值最小的下标
                  minIndex = j;
              }
          }
          swap(arr[i], arr[minIndex]); // 和头部元素调换
      }
  }
};
```



#### Valid-Anagram-242

```cpp
//
// Created by 张达 on 2020/10/11 23:35.
//

#include <string>
using namespace std;

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

int main() {
    string s1 = "anagram";
    string s2 = "nagaram";
    Solution solve;

    bool r = solve.isAnagram(s1, s2);
    printf("%d\n", r);
}
```
