# [DSA] training camp week-1

> 2020/08/10-2020/08/16



## 完成情况

| Number                                  | Rounds |
| --------------------------------------- | ------ |
| 146. LRUCache                           | 2/5    |
| 1. Two Sum                              | 3/5    |
| 11. Container With Most Water           | 3/5    |
| 83. Move Zeroes                         | 3/5    |
| 70. Climbing Stairs                     | 4/5    |
| 15. 3Sum                                | 3/5    |
| 206. Reverse Linked List                | 4/5    |
| 24. Swap Nodes in Pairs                 | 2/5    |
| 141. Linked List Cycle                  | 4/5    |
| 142. Linked List Cycle II               | 4/5    |
| 25. Reverse Nodes in k-Group            | 1/5    |
| 155. Min Stack                          | 4/5    |
| 20. Valid Parentheses                   | 4/5    |
| 84. Largest Rectangle in Histogram      | 1/5    |
| 33. Search in Rotated Sorted Array      | 4/5    |
| 239. Sliding Window Maximum             | 1/5    |
| 26. Remove Duplicates from Sorted Array | 2/5    |
| 21. Merge Two Sorted Lists              | 2/5    |
| 23. Merge k Sorted Lists                | 2/5    |



## Codes

**146. LRUCache**

```cpp
class LRUCache{
 private:
  int capacity;
  list<int> lru;
  unordered_map<int, list<int>::iterator> map;
  unordered_map<int, int> kv;

 public:
  LRUCache(int capacity):capacity(capacity) {}

  void updateLru(int key) {
      if (kv.find(key) != kv.end()) {
          lru.erase(map[key]); // 删除旧的链接
      }
      lru.push_front(key);
      map[key] = lru.begin(); // 建立新的链接
  }

  void eliminate(int key) {
      lru.pop_back(); // 淘汰最老的末尾元素
      map.erase(lru.back()); // 淘汰最老的末尾元素
      kv.erase(lru.back()); // 淘汰最老的末尾元素
  }

  int get(int key) {
      if (kv.find(key) == kv.end()) {
          return -1;
      }
      updateLru(key);
      return kv[key];
  }

  void put(int key, int value) {
      if (capacity == lru.size() && kv.find(key) == kv.end()) {
          eliminate(key);
      }
      updateLru(key);
      kv[key] = value;
  }
};
```



**1. Two Sum**

```cpp
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
      vector<int> result;
      unordered_map<int, int> map;
      for (int i = 0; i < nums.size(); ++i) {
          map.insert(make_pair(nums[i], i));
      }
      for (int i = 0; i < nums.size(); ++i) {
          int number = target - nums[i];
          if (map.count(number) && map[number] != i) {
              result = {i, map[number]};
              break;
          }
      }
      return result;
  }
};
```



**11. Container With Most Water**

```cpp
class Solution {
 public:
  int maxArea(vector<int>& height) {
      int maxArea = 0, i = 0, j = height.size() -1 ;
      while (i < j) {
          maxArea = max(maxArea, (j - i) * (height[i] < height[j] ? height[i++] : height[j--]));
      }
      return maxArea;
  }
};
```



**83. Move Zeroes**

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zeroPoint = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i]) {
                swap(nums[i], nums[zeroPoint++]);
            }
        }
    }
};
```



**70. Climbing Stairs**

```cpp
class Solution {
 public:

  int help(int n, vector<int> &dp) {
      if (n <= 3) {
          return n;
      }
      if (dp[n]) {
          return dp[n];
      }
      dp[n] = help(n - 1, dp) + help(n - 2, dp);
      return dp[n];
  }
```



**15. 3Sum**

```cpp
class Solution {
 public:
  vector<vector<int>> threeSum(vector<int> &nums) {
      vector<vector<int>> result;
      if (nums.size() < 3) {
          return result;
      }
      sort(nums.begin(), nums.end());

      for (int k = 0; k < nums.size() - 2; ++k) {
          // case 1
          if (nums[k] > 0) break;

          // case 2
          if (k > 0 && nums[k] == nums[k - 1]) continue;


          // case 3
          int i = k + 1;
          int j = nums.size() - 1;
          while (i < j) {
              int sum = nums[k] + nums[i] + nums[j];

              if (sum < 0) {
                  ++i;
              } else if (sum > 0) {
                  --j;
              } else {
                  result.push_back({nums[k], nums[i], nums[j]});
                  ++i;
                  --j;
                  while (i < j && nums[i] == nums[i - 1]) ++i;
                  while (i < j && nums[j] == nums[j + 1]) --j;
              }
          }
      }
      return result;
  }
};
```



**206. Reverse Linked List**

```cpp
class Solution {
 public:
  ListNode *reverseList(ListNode *head) {
      ListNode *new_head = nullptr;
      ListNode *next = nullptr;
      while (head) {
          next = head->next;
          head->next = new_head;
          new_head = head;
          head = next;
      }
      return new_head;
  }
};
```



**24. Swap Nodes in Pairs**

```cpp
class Solution {
 public:
  ListNode* swapPairs(ListNode* head) {
      if (!head || !head->next) {
          return head;
      }

      ListNode* new_head = head->next;
      ListNode* third = head->next->next;
      new_head->next = head;
      head->next = swapPairs(third);
      return new_head;
  }
};
```



**141. Linked List Cycle**

```cpp
class Solution {
 public:
  bool hasCycle(ListNode *head) {
      if (!head || !head->next) return false;
      ListNode *fast = head;
      ListNode *slow = head;
      while (slow && fast) {
          slow = slow->next;
          fast = fast->next;
          if (fast) {
              fast = fast->next;
          }
          if (slow == fast) {
              return true;
          }
      }
      return false;
  }
};
```



**142. Linked List Cycle II**

```cpp
class Solution2 {
 public:
  ListNode* detectCycle(ListNode* head) {
      if (!head || !head->next) {
          return nullptr;
      }
      ListNode* slow = head;
      ListNode* fast = head;
      ListNode* meet = nullptr;
      while (slow && fast) {
          slow = slow->next;
          fast = fast->next;
          if (fast) {
              fast = fast->next;
          }
          if (fast == slow) {
              meet = fast;
              break;
          }
      }
      while (meet && head) {
          if (meet == head) {
              return meet;
          }
          meet = meet->next;
          head = head->next;
      }
      return nullptr;
  }
};
```



**25. Reverse Nodes in k-Group**

```cpp
class Solution {
 public:
  ListNode *getKNode(ListNode *head, int k) {
      while (head && k--) {
          head = head->next;
      }
      return head;
  }

  void reverseList(ListNode *head, int k) {
      ListNode *new_head = nullptr;
      while (head && k--) {
          auto next = head->next;
          head->next = new_head;
          new_head = head;
          head = next;
      }
  }

  ListNode *reverseKGroup(ListNode *head, int k) {
      if (!getKNode(head, k-1)) {
          return head; // list size less than k, return head directly! （想想k为3，链表长度为2的情况）
      }

      ListNode *new_head = getKNode(head, k-1);
      ListNode *neightNode = new_head->next;
      reverseList(head, k);
      head->next = reverseKGroup(neightNode, k);
      return new_head;
  }
};
```



**155. Min Stack**

```cpp
class MinStack {
 private:
  stack<int> stack, min_stack;

 public:
  /** initialize your data structure here. */
  MinStack() {

  }

  void push(int x) {
      stack.push(x);
      if (min_stack.empty()) {
        min_stack.push(x);
      } else {
          if (x < min_stack.top()) {
              min_stack.push(x);
          } else {
              min_stack.push(min_stack.top());
          }
      }
  }

  void pop() {
    stack.pop();
    min_stack.pop();
  }

  int top() {
    return stack.top();
  }

  int getMin() {
    return min_stack.top();
  }
};
```



**20. Valid Parentheses**

```cpp
class Solution {
 public:
  bool isValid(string s) {
      stack<char> stack;

      for (int i = 0; i < s.length(); ++i) {
          if (stack.empty()) {
              if (s[i] == ')' or s[i] == '}' or s[i] == ']') {
                  return false;
              } else {
                  stack.push(s[i]);
              }
          } else {
              if ((s[i] == ')' and stack.top() == '(')
                  or (s[i] == '}' and stack.top() == '{')
                  or (s[i] == ']' and stack.top() == '[')) {
                  stack.pop();
              } else {
                  stack.push(s[i]);
              }
          }
      }
      return stack.empty();
  }
};
```



**84. Largest Rectangle in Histogram**

```cpp
class Solution {
 public:
  int largestRectangleArea(vector<int> &heights) {
      stack<int> index;
      int maxArea = 0;
      heights.push_back(0); //在vector最后面加一个0,这步很关键，能够保证所有的元素都小于等于0
      for (int i = 0; i < heights.size(); ++i) {
          while (!index.empty() && heights[index.top()] > heights[i]) {
              int height = heights[index.top()];
              index.pop();
              int prev = index.empty() ? -1 : index.top();
              maxArea = max(maxArea, (i - prev - 1) * height);
              printf("i = %d, prev = %d, maxArea = %d\n", i, prev, maxArea);
          }
          index.push(i);
      }
      return maxArea;
  }
};
```



**33. Search in Rotated Sorted Array**

```cpp
class Solution {
 public:
  int search(vector<int> &nums, int target) {
      int start = 0;
      int end = nums.size() - 1;
      while (start <= end) {
          int mid = (start + end) / 2;
          if (nums[mid] < target) {
              // 判断是否旋转数组，并确定旋转点所在分段
              if (nums[start] > nums[mid] && nums[end] < target) { // 左旋转，右升序
                  end = mid - 1;
              } else {
                  start = mid + 1;
              }
          } else if (nums[mid] > target) {
              if (nums[end] < nums[mid] and nums[start] > target) { // 左升序，右旋转
                  start = mid + 1;
              } else {
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



**239. Sliding Window Maximum**

```cpp
// method 1 : exhaustive enumeration
// Time Limit Exceeded: 17/18
class Solution1 {
 public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
      vector<int> res;
      for (int i = 0; i < nums.size() - (k - 1); ++i) {
          int maxvalue = INT_MIN;
          for (int j = i; j < i + k; ++j) {
              maxvalue = max(maxvalue, nums[j]);
          }
          res.push_back(maxvalue);
      }
      return res;
  }
};
```



**26. Remove Duplicates from Sorted Array**

```cpp
class Solution {
 public:
  int removeDuplicates(vector<int> &nums) {
      if (nums.empty()) return 0;

      int j = 0;
      for (int & num : nums) {
          if (num > nums[j]) {
              swap(num, nums[++j]);
          }
      }
      return j + 1;
  }
};
```



**21. Merge Two Sorted Lists**

```cpp
class Solution {
 public:
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
      if (!l1 || !l2) return (l1) ? l1 : l2;
      if (l1->val <= l2->val) {
          l1->next = mergeTwoLists(l1->next, l2);
          return l1;
      } else {
          l2->next = mergeTwoLists(l2->next, l1);
          return l2;
      }
  }
};
```



**23. Merge k Sorted Lists**

```cpp
class Solution {
 public:
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
      if (!l1 || !l2) return (l1) ? l1 : l2;
      if (l1->val <= l2->val) {
          l1->next = mergeTwoLists(l1->next, l2);
          return l1;
      } else {
          l2->next = mergeTwoLists(l2->next, l1);
          return l2;
      }
  }

  ListNode *help(vector<ListNode *> &lists, int low, int hight) {
      if (low >= hight) {
          return lists[low];
      }
      int mid = (low + hight) / 2;
      ListNode *left = help(lists, low, mid); // complement merge left side
      ListNode *right = help(lists, mid + 1, hight);// complement merge right side
      ListNode *res = mergeTwoLists(left, right);
      return res;
  }
  
  ListNode *mergeKLists(vector<ListNode *> &lists) {
      if (lists.empty()) {
          return nullptr;
      }
      return help(lists, 0, lists.size() - 1);
  }
};
```
