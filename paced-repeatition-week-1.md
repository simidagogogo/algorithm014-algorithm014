# paced-repeatition-week-1



#### 3Sum-15

```
//
// Created by 张达 on 2020/8/11. 10:00 3/5
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

// force brute
class Solution1 {
 public:
  vector<vector<int>> threeSum(vector<int> &nums) {
      vector<vector<int>> result;
      if (nums.size() < 3) {
          return result;
      }
      set<vector<int>> set;
      sort(nums.begin(), nums.end());
      vector<int> temp;
      for (int i = 0; i < nums.size() - 2; ++i) {
          for (int j = i + 1; j < nums.size() - 1; ++j) {
              for (int k = j + 1; k < nums.size(); ++k) {
                  if (nums[i] + nums[j] + nums[k] == 0) {
                      temp = {nums[i], nums[j], nums[k]};
                      if (set.find(temp) == set.end()) {
                          result.push_back(temp);
                          set.insert(temp);
                      }
                  }
              }
          }
      }
      return result;
  }
};

// double pointer: from end to center by double pointer
class Solution2 {
 public:
  vector<vector<int>> threeSum(vector<int> &nums) {
      vector<vector<int>> res;
      if (nums.size() < 3) {
          return res;
      }
      sort(nums.begin(), nums.end());
      for (int k = 0; k < nums.size() - 2; ++k) {
          // case1
          if (nums[k] > 0) break;

          // case2
          if (k >= 1 && nums[k] == nums[k - 1]) continue;

          // case3: excluding above two cases
          int i = k + 1;
          int j = nums.size() - 1;
          while (i < j) {
              int s = nums[k] + nums[i] + nums[j];
              if (s < 0) {
                  ++i;
              } else if (s > 0) {
                  --j;
              } else {
                  res.push_back({nums[k], nums[i], nums[j]});
                  ++i;
                  --j;
                  while (i < j && nums[i] == nums[i - 1]) ++i;
                  while (i < j && nums[j] == nums[j + 1]) --j;
              }
          }
      }
      return res;
  }
};
```



#### Add-Two-Numbers-2

```
//
// Created by simida on 2020/06/09.
//

#include <stack>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// time complexity O(n)
// space complexity
class Solution {
 public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
      ListNode preHead(0); // 头插节点
      ListNode *p = &preHead;

      int advance_flag = 0; // 进位标记
      while (l1 || l2 || advance_flag) {
          int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + advance_flag;
          advance_flag = sum / 10;
          p->next = new ListNode(sum % 10);
          p = p->next;
          if (l1) l1 = l1->next;
          if (l2) l2 = l2->next;
      }
      return preHead.next;
  }
};


int main() {
    Solution solve;

    ListNode a(0);
//  ListNode b(4);
//  ListNode c(3);

    ListNode d(0);
//  ListNode e(6);
//  ListNode f(4);

//  a.next = &b;
//  b.next = &c;

//  d.next = &e;
//  e.next = &f;

    ListNode* head = solve.addTwoNumbers(&a, &d);
    while (head) {
        printf("the value is %d\n", head->val);
        head = head->next;
    }

    return 0;
}
```



#### Climbing-Stairs-70

```
//
// Created by 张达 on 2020/8/11. 2/5
//

#include <iostream>
#include <vector>

using namespace std;

// 暴力递归
class Solution1 {
 public:
  int climbStairs(int n) {
      if (n < 3) {
          return n;
      }
      return climbStairs(n - 1) + climbStairs(n - 2);
  }
};

// 递推
class Solution2 {
 public:
  int climbStairs(int n) {
      if (n < 3) {
          return n;
      }
      int f1 = 1, f2 = 2, f3 = 3;
      for (int i = 2; i < n; ++i) {
          f3 = f2 + f1;
          f1 = f2;
          f2 = f3;
      }
      return f3;
  }
};

// 利用向量保存中间结果的递推
class Solution3 {
 public:
  int climbStairs(int n) {
      vector<int> vec(n + 3, 0);
      vec[0] = 0;
      vec[1] = 1;
      vec[2] = 2;
      for (int i = 3; i <= n; ++i) { // 注意这里是<=，否则取不到
          vec[i] = vec[i - 2] + vec[i - 1];
      }
      return vec[n];
  }
};

// 记忆化存储 + 递归
class Solution4 {
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

  int climbStairs(int n) {
      vector<int> dp(n + 1, 0); // 防止dp[n]操作数组越界
      return help(n, dp);
  }
};
```





#### Container-With-Most-Water-11

```
//
// Created by 张达 on 2020/8/11. 2/5
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
 public:
  int maxArea(vector<int> &height) {
      assert(height.size() >= 2);
      if (height.size() < 2) return 0;

      int maxArea = 0;
      for (int i = 0; i < height.size() - 1; ++i) {
          for (int j = i + 1; j < height.size(); ++j) {
              maxArea = max(maxArea, (j - i + 1) * min(height[i], height[j]));
          }
      }
      return maxArea;
  }
};


// 两边向中间左右夹逼
// 两边的柱子，哪个矮就移动哪个
class Solution2 {
 public:
  int maxArea(vector<int>& height) {
      if (height.size() < 2) return 0;

      int maxArea = 0;
      int i = 0, j = height.size() -1 ;
      while (i < j) {
          maxArea = max(maxArea, (j - i) * min(height[i], height[j]));
          height[i] < height[j] ? ++i:--j;
      }
      return maxArea;
  }
};


// 最简洁版本
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



#### Design-Circular-Queue-622

```
//
// Created by 张达 on 2020/8/18. 09:30 2/5
//
#include <iostream>
#include <vector>
using namespace std;

class MyCircularQueue {
 private:;
  vector<int> arr;
  int capacity;
  int front;
  int rear;

 public:
  /** Initialize your data structure here. Set the size of the queue to be k. */
  MyCircularQueue(int k) {
      capacity = k + 1;
      arr.assign(capacity, 0);
      front = 0;
      rear = 0;
  }

  /** Insert an element into the circular queue. Return true if the operation is successful. */
  bool enQueue(int value) {
      if (isFull()) {
          return false;
      }
      arr[rear] = value;
      rear = (rear + 1) % capacity;
      return true;
  }

  /** Delete an element from the circular queue. Return true if the operation is successful. */
  bool deQueue() {
      if (isEmpty()) {
          return false;
      }
      front = (front + 1) % capacity;
      return true;
  }

  /** Get the front item from the queue. */
  int Front() {
      if (isEmpty()) {
          return -1;
      }
      return arr[front];
  }

  /** Get the last item from the queue. */
  int Rear() {
      if (isEmpty()) {
          return -1;
      }
      return arr[(rear - 1 + capacity) % capacity];
  }

  /** Checks whether the circular queue is empty or not. */
  bool isEmpty() {
      return rear == front;
  }

  /** Checks whether the circular queue is full or not. */
  bool isFull() {
    return (rear + 1 + capacity) % capacity == front;
  }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
```



#### Linked-List-Cycle-141

```
//
// Created by 张达 on 2020/8/12. 3/5 09:00-09:30
//
#include <iostream>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// method1: set
class Solution {
 public:
  bool hasCycle(ListNode *head) {
      set<ListNode *> set;
      while (head) {
          if (set.find(head) == set.end()) {
              set.insert(head);
              head = head->next;
          } else {
              return true;
          }
      }
      return false;
  }
};

// method2: fast and slow pointer
class Solution2 {
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



#### Linked-List-Cycle-II-142

```
//
// Created by 张达 on 2020/8/12. 20:20
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 空间复杂度O(n)：利用map存储<ListNode*, index>
class Solution1 {
 public:
  ListNode *detectCycle(ListNode *head) {
    vector<ListNode*> vec;
    while (head) {
        if (find(vec.begin(), vec.end(), head) != vec.end()) {
            return head;
        } else {
            vec.push_back(head);
            head = head->next;
        }
    }
  return nullptr;
  }
};

class Solution3 {
 public:
  ListNode *detectCycle(ListNode *head) {
      set<ListNode*> vec;
      while (head) {
          if (find(vec.begin(), vec.end(), head) != vec.end()) {
              return head;
          } else {
              vec.insert(head);
              head = head->next;
          }
      }
      return nullptr;
  }
};

// 快慢指针，利用数学公式
// 从相遇节点和起始节点一起走，直到相遇即为交叉点
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





#### LRU-Cache-146

```
//
// Created by simida on 2020/08/11. 2/5
//

// 报错，待排查

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;


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



#### Merge-k-Sorted-Lists-23

```
//
// Created by 张达 on 2020/8/14. 09:20
//

#include <vector>
#include <iostream>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int val) : val(val), next(nullptr) {}
};

class Solution {
 public:
  ListNode *mergeTwoList(ListNode *l1, ListNode *l2) {
      ListNode *head_temp = new ListNode(0);
      ListNode *head = head_temp;
      while (l1 && l2) {
          if (l1->val < l2->val) {
              head->next = l1;
              l1 = l1->next;
          } else {
              head->next = l2;
              l2 = l2->next;
          }
          head = head->next;
      }
      head->next = l1 ? l1 : l2;
      return head_temp->next;
  }
  ListNode *mergeKLists(vector<ListNode *> &lists) {
      unsigned long len = lists.size();
      if (len == 0) return nullptr;
      if (len == 1) return lists[0];
      if (len == 2) return mergeTwoList(lists[0], lists[1]);

      std::vector<ListNode *> small_list;
      std::vector<ListNode *> large_list;
      int mid = len / 2;
      for (int i = 0; i < mid; i++) {
          small_list.push_back(lists[i]);
          large_list.push_back(lists[i + mid]);
      }
      if (len % 2) large_list.push_back(lists[len - 1]);
      return mergeTwoList(mergeKLists(small_list), mergeKLists(large_list));
  }
};

class Solution2 {
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


int main() {
    ListNode a(1);
    ListNode b(3);
    ListNode c(2);
    ListNode d(4);
    ListNode e(-9);
    ListNode f(5);
    a.next = &b;
    c.next = &d;
    e.next = &f;
    Solution solve;

    vector<ListNode *> lists;
    lists.push_back(&a);
    lists.push_back(&c);
    lists.push_back(&e);
    ListNode *head = solve.mergeKLists(lists);

    while (head) {
        printf("%d\n", head->val);
        head = head->next;
    }
    return 0;
}
```



#### Merge-Two-Sorted-Lists-21

```
//
// Created by 张达 on 2020/8/14.
//


// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
      if (!l1 || !l2) return (l1) ? l1 : l2;
      ListNode tmp(0);
      ListNode *head = &tmp;
      while (l1 && l2) {
          if (l1->val < l2->val) {
              head->next = l1;
              l1 = l1->next;
          } else {
              head->next = l2;
              l2 = l2->next;
          }
          head = head->next;
      }
      head->next = l1 ? l1 : l2;
      return tmp.next;
  }
};

class Solution2 {
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



#### Min-Stack-155

```
//
// Created by 张达 on 2020/8/16. 3/5 17:35
//

#include <iostream>
#include <stack>
using namespace std;


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

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```



#### Swap-Nodes-in-Pairs-24

```
//
// Created by 张达 on 2020/8/12. 2/5 19:00
//

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {
  }
};

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





#### Reverse Linked List-206

```
//
// Created by 张达 on 2020/8/12. 08:48 3/5
//


// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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





#### Valid-Parentheses-20

```
//
// Created by 张达 on 2020/8/16. 3/5 17:46 - 17:58
//

#include <string>
#include <iostream>
#include <stack>

using namespace std;

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

class Solution2 {
 public:
  bool isValid(string s) {
      stack<char> stack;

      for (int i = 0; i < s.length(); ++i) {
          if (stack.empty() and (s[i] == ')' or s[i] == '}' or s[i] == ']')) {
              return false;
          } else if ((s[i] == ')' and stack.top() == '(')
              or (s[i] == '}' and stack.top() == '{')
              or (s[i] == ']' and stack.top() == '[')) {
              stack.pop();
          } else {
              stack.push(s[i]);
          }
      }
      return stack.empty();
  }
};
```





#### Search-in-Rotated-Sorted-Array-33

```
//
// Created by 张达 on 2020/8/16. 3/5 18:06
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:

  int binartSearch(vector<int> nums, int target) {
      int start = 0;
      int end = nums.size() - 1;
      while (start <= end) {
          int mid = (start + end) / 2;
          if (nums[mid] < target) {
              start = mid + 1;
          } else if (nums[mid] > target) {
              end = mid - 1;
          } else {
              return mid;
          }
      }
      return 0;
  }

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



int search(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (nums[middle] < target) {
            if (nums[left] > nums[middle] && target > nums[right]) { // 左旋转，右升序。target>nums[right]，说明在左边
                right = middle - 1;
            } else {    // 升序数组，或者左旋转，右升序，但是target在升序数组
                left = middle + 1;
            }
        } else if (nums[middle] > target) {
            if (nums[middle] > nums[right] && target < nums[left]) { // 左升序，右旋转。target < nums[left，说明在右边
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        } else {
            return middle;
        }
    }
    return -1;
}
```



#### Plus-One-66

```
//
// Created by 张达 on 2020/8/18. 08:50 2/5
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> plusOne(vector<int> &digits) {
      for (int i = digits.size() - 1; i >= 0; --i) { // from right to left
          if (digits[i] == 9) {
              digits[i] = 0;
          } else {
              ++digits[i];
              return digits;
          }
      }
      digits[0] = 1;
      digits.push_back(0);
      return digits;
  }
};
```



#### Sliding-Window-Maximum-239

```
//
// Created by 张达 on 2020/8/18. 2/5  08:50-09:10
//
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

struct Monoqueue {
  deque<pair<int, int>> mydeque;
  // first: the auctual value
  // second: the deleted element before it

  void push(int val) {
      int count = 0;
      while (!mydeque.empty() && mydeque.back().first < val) {
          count += mydeque.back().second + 1;
          mydeque.pop_back();
      }
      mydeque.emplace_back(val, count);
  }

  int max() {
      return mydeque.front().first;
  }

  void pop() {
      if (mydeque.front().second > 0) {
          --mydeque.front().second;
          return ;
      }
      mydeque.pop_front();
  }
};

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
      vector<int> result;
      Monoqueue monoqueue;
      for (int i = 0; i < nums.size(); ++i) {
          if (i < k - 1) {
              monoqueue.push(nums[i]);
          } else {
              monoqueue.push(nums[i]);
              result.push_back(monoqueue.max());
              monoqueue.pop();
          }
      }
      return result;
  }
};
```



#### Two-Sum-1

```
//
// Created by 张达 on 2020/8/12. 08:30 2/5
//

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// exhaustive enumeration
class Solution1 {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
      vector<int> result;
      for (int i = 0; i < nums.size() - 1; ++i) {
          for (int j = i + 1; j < nums.size(); ++j) {
              if (nums[i] + nums[j] == target) {
                  return {i, j};
              }
          }
      }
      return result;
  }
};


// two pointer: from edge to center
class Solution2 {
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
              return {i, map[number]};
          }
      }
      return result;
  }
};

// 一边查找一边插入
class Solution3 {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
      vector<int> result;
      unordered_map<int, int> map;
      for (int i = 0; i < nums.size(); ++i) {
          int number = target - nums[i];
          if (map.count(number) && map[number] != i) {
              return {i, map[number]};
          } else {
              map.emplace(nums[i], i);
          }
      }
      return result;
  }
};


```





#### Remove-Duplicates-from-Sorted-Array-26

```
//
// Created by 张达 on 2020/8/12. 21:00 2/5
//

#include <iostream>
#include <vector>
using namespace std;

// 空间复杂度为O(1), 类似移动zero
// 排序数组，如果前后相邻元素相等，则指针不移动。否则，如果不等，则移动指针。
class Solution {
 public:
  int removeDuplicates(vector<int> &nums) {
      if (nums.empty()) return 0;

      int j = 0;
      for (int i = j + 1; i < nums.size(); ++i) {
          if (nums[j] != nums[i]) {
              swap(nums[i], nums[++j]);
          }
      }
      return j + 1;
  }
};


class Solution1 {
 public:
  int removeDuplicates(vector<int> &nums) {
      if (nums.empty()) return 0;

      int j = 0;
      for (int i = 0; i < nums.size(); ++i) {
          if (nums[i] > nums[j]) {
              swap(nums[i], nums[++j]);
          }
      }
      return j + 1;
  }
};
```



#### Move-Zeroes-283

```
//
// Created by 张达 on 2020/8/11. 2/5
//

// 非常经典的题，套路模板需要熟练掌握，写的滚瓜烂熟

#include <iostream>
#include <vector>
using namespace std;

// 思路：遇到零，就往后面第一个非零元素交换


class Solution1 {
 public:
  void moveZeroes(vector<int> &nums) {
      int zeroPointer = 0;
      for (int i = 0; i < nums.size(); ++i) {
          if (nums[i] != 0) { // 不等于零，则zeroPinter跟随一起移动，如果等于零，则停下等待
              if (i != zeroPointer) { // 这个判断其实没必要，最多自己和自己交换，不影响最终结果
                  swap(nums[i], nums[zeroPointer]);
              }
              zeroPointer++;
          }
      }
  }
};

// 化简版本
class Solution {
 public:
  void moveZeroes(vector<int> &nums) {
      int j = 0;
      for (int i = 0; i < nums.size(); ++i) {
          if (nums[i]) swap(nums[i], nums[j++]);
      }
  }
};



class Solution2 {
 public:
  void moveZeroes(vector<int> &nums) {
      int zeroPoint = 0;
      for (int i = 0; i < nums.size(); ++i) {
          if (nums[i] == 0) {
              continue;
          } else {
              swap(nums[i], nums[zeroPoint++]);
          }
      }
  }
};
```
