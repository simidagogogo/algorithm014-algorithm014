# paced-repeatition-week-3



#### Climbing-Stairs-70

```
//
// Created by 张达 on 2020/8/24. 3/5  23:02
//

#include <vector>
using namespace std;

// 递归法+记忆化存储
// 0 -> 0
// 1->1
// 2->2
// 3-> 3
class Solution {
 private:
  int helper(int n, vector<int> &memo) {
      if (n <= 3) return n;
      if (memo[n] > 0) {
          return memo[n];
      } else {
          memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
      }
      return memo[n];
  }
  
 public:
  int climbStairs(int n) {
      vector<int> memo(n + 1, 0);
      return helper(n, memo);
  }
};

```



#### Combinations-77

```
//
// Created by 张达 on 2020/8/29. 1/5 18:41
//

#include <vector>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

class Solution2 {
 public:
  vector<vector<int> > combine(int n, int k) {
      vector<vector<int> > result;
      vector<int> vec;
      combine(result, vec, 1, n, k);
      return result;
  }

  void combine(vector<vector<int> > &result, vector<int> &vec, int start, int& n, int& k) {
      if (vec.size() == k) {
          result.push_back(vec);
          return;
      }
      //
      for (int i = start; i <= n; i++) {
          vec.push_back(i);
          combine(result, vec, i + 1, n, k);
          vec.pop_back();
      }
  }
};

class Solution3 {
 public:
  vector<vector<int> > combine(int n, int k) {
      vector<vector<int> > result;
      vector<int> vec;
      recurion(result, vec, 1, n, k);
      return result;
  }

  void recurion(vector<vector<int> > &result, vector<int> &vec, int i, int& n, int& k) {
      if (vec.size() >= k) {
          result.push_back(vec);
          return;
      }
      if (i > n) return;
      vec.push_back(i);
      recurion(result, vec, i + 1, n, k); // 选
      vec.pop_back();
      recurion(result, vec, i + 1, n, k); // 不选
  }
};

```



#### Construct-Binary-Tree-from-Preorder-and-Inorder-Traversal-105

```
//
// Created by 张达 on 2020/8/27. 1/5 22:49
//

#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <sstream>
#include <map>
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
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
      // preorder和inorder在递归过程中，没有发生改变，直接传拷贝即可？(是的，但是传引用可以加快执行速度)
      return create(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
  }
  TreeNode *create(vector<int> &preorder,
                   vector<int> &inorder,
                   int p_start,
                   int p_end,
                   int i_start,
                   int i_end) {
      // recursion terminator
      if (p_start > p_end) {
          return nullptr;
      }
      auto node = new TreeNode(preorder[p_start]); // 这是头结点
      int root_pos; // 注意这里，不可以初始化，否则会报错，访问未定义内存空间(很奇怪，不理解)
      // 以下代码目的：为了找到中序的根节点位置pos
      // 同时pos代表着根节点的左子树存在pos个节点，因此preoder的右子树所以要从pos+1开始
      for (int i = i_start; i < i_end; ++i) {
          if (inorder[i] == node->val) { // 如果中序的元素等于前序的元素，此时的索引i即为pos即为在中序中头结点的位置
              root_pos = i;
              break;
          }
      }

      // 要理解代码，必须深刻的理解以下过程
      // similar idea, the first element in the preorder is the root node. then find the element in the inorder equal the the root node,
      // devide the inorder vector into two parts, the left part is the left child tree and the right part is the right child tree.
      // and the preorder has equal number nodes in correspondin part
      /*
       * Let me explain the coordinates in the recursion.
       * Very simply, we can see that the inorder traversal is divided into two parts,
       * [is, pos-1] and [pos+1, ie] according to the root node pointed by pos.
       * The first part contains pos - is elements, and the second part has ie- (pos+1)+1 = ie - pos elements.
       * Correspondingly, in preorder traversal, the elements in the [ps + 1, ps + pos - is] intervals belong to the left subtree,
       * and the elements in the [pe - (ie - pos)+1, pe] interval belong to the right subtree.
       * */
      node->left = create(preorder, inorder,
                          p_start + 1, // 根节点的左节点即为根节点的下一个位置
                          p_start + (root_pos - i_start), // 不好理解
          // (root_pos - i_start)表示inorder中左子树的节点个数
                          i_start + 0, //
                          root_pos - 1 //左子树的最大索引更新为根节点索引-1
      );
      node->right = create(preorder,
                           inorder,
                           p_end - (i_end - root_pos) + 1, // 根节点的下一个即为右节点 (不好理解)
          // i_end - root_pos 表示 inorder中根节点右子树的节点个数
          // 即从p_start到p_end的节点 (这就是p_start计算公式中各种+-操作的本质原因)
                           p_end + 0, // 一直顶到最右端
                           root_pos + 1, // pos的下一个位置
                           i_end + 0); // 一直顶到最右端
      return node;
  }
};

class Solution2 {
 public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
      return create(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
  }

  TreeNode *create(vector<int> &preorder, vector<int> &inorder, int p_start, int p_end, int i_start, int i_end) {
      if (p_start > p_end) return nullptr;

      TreeNode *node = new TreeNode(preorder[p_start]); // 这是头结点
      int root_pos;
      for (int i = i_start; i < i_end; ++i) {
          if (inorder[i] == node->val) { // 如果中序的元素等于前序的元素，此时的索引i即为pos即为在中序中头结点的位置
              root_pos = i;
              break;
          }
      }
      node->left = create(preorder, inorder, p_start + 1, p_start + (root_pos - i_start), i_start + 0, root_pos - 1);
      node->right = create(preorder, inorder, p_end - (i_end - root_pos) + 1, p_end + 0, root_pos + 1, i_end + 0);
      return node;
  }
};

// 代码很简洁，一定要学会
class Solution3 {
 public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
      // deal with edge case(s)
      if (preorder.empty()) return nullptr;

      // build a map of the indices of the values as they appear in the inorder array
      // 通过map将inorder中的元素和索引记录起来 （索引是从小到大顺序）
      map<int, int> map;
      for (int i = 0; i < inorder.size(); ++i) {
          map.emplace(inorder[i], i);
      }

      // initialize the stack of tree nodes
      stack<TreeNode *> stack;
      int value = preorder[0];
      auto root = new TreeNode(value); // root一定是根节点
      stack.push(root);

      // for all remaining values...
      for (int i = 1; i < preorder.size(); ++i) {
          // create a node
          value = preorder[i];
          TreeNode *node = new TreeNode(value); // 这个node是root左子树的根节点

          if (map[value] < map[stack.top()->val]) { //
              // the new node is on the left of the last node, so it must be its left child (that's the way preorder works)
              stack.top()->left = node;
          } else {
              // the new node is on the right of the last node, so it must be the right child of either the last node
              // or one of the last node's ancestors.
              // pop the stack until we either run out of ancestors
              // or the node at the top of the stack is to the right of the new node
              TreeNode *parent = nullptr; // 注意: 这里的parent定义不可以放到while里面，否则报错访问未定义标识符
              // 原因在于如果将定义放在while内部，则parent只在while的定义域仅在代码块中

              // 这里需要在纸上推演
              while (!stack.empty() && map[value] > map[stack.top()->val]) {
                  parent = stack.top();
                  stack.pop();
              }
              parent->right = node;
          }

          stack.push(node);
      }
      return root;
  }
};
```



#### divide-and-conquer-template

```
//
// Created by 张达 on 2020/8/30. 14:42
//

int divide_conquer(Problem *problem, int params) {
    // recursion terminator
    if (problem == nullptr) {
         process_result;
         return return_result;
    }

    // process current problem
    subproblems = split_problem(problem, data);
    subresult1 = divide_conquer(subproblem[0], p1);
    subresult2 = divide_conquer(subproblem[1], p1);
    subresult3 = divide_conquer(subproblem[2], p1);
    ...

    // merge
    result = process_result(subresultt1, subresultt2, subresultt3);

    // reverse current level status
    return 0;
}
```



#### Generate-Parentheses-22

```
//
// Created by 张达 on 2020/8/24.
//

#include <vector>
#include <string>
using namespace std;

// 递归法：不断放置括号和取回括号，2^n
// 因为参数团队对于函数所包含参数，因此需要helper
// 自顶向下编程
class Solution {
 private:
  void helper(int left, int right, int n, vector<string> &result, string temp) {
      // recursion ternimator
      if (left == n and right == n) {
          printf("%s\n", temp.c_str());
          result.push_back(temp);
          return;
      }

      // process current logic

      // drill down

      // reverse states

      helper(left + 1, right, n, result, temp + "(");
      helper(left, right + 1, n, result, temp + ")");

  }

 public:
  vector<string> generateParenthesis(int n) {
      vector<string> result;
      helper(0, 0, n, result, "");
      return result;
  }
};

int main() {
    Solution solve;
    solve.generateParenthesis(3);
}
```



#### Invert-Binary-Tree-226

```
//
// Created by 张达 on 2020/8/25. 2/5 23:47
//

// 这道题还是不熟练，需要反复过遍数

#include <vector>
#include <string>
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

// right
class Solution {
 public:
  TreeNode *invertTree(TreeNode *root) {
      // 1 recusion ternimator
      if (!root) return root;
      if (!root->left && !root->right) // 判断根节点
          return root;

      // 2 process current level
      // 3 drill down
      auto l = invertTree(root->left); // 处理左子树
      auto r = invertTree(root->right); // 处理柚子树

      root->right = l; // 当前根节点右儿子接左子树
      root->left = r; // 当前根节点左儿子接右子树

      // 4 reverse states
      return root;
  }
};

// 更好理解一些
class Solution2 {
 public:
  TreeNode *invertTree(TreeNode *root) {
      if (!root) return root;
      if (!root->left && !root->right) // 判断根节点
          return root;
      swap(root->left, root->right);
      invertTree(root->left);
      invertTree(root->right);
      return root;
  }
};

class Solution3 {
 public:
  TreeNode *invertTree(TreeNode *root) {
      if (!root) return root;
      invertTree(root->left); // 返回值没人接
      invertTree(root->right); //
      std::swap(root->left, root->right);
      return root;
  }
};

class Solution4 {
 public:
  TreeNode *invertTree(TreeNode *root) {
      if (!root)
          return root;
      if (!root->left && !root->right) // 判断根节点
          return root;
      if (root != nullptr) {
          TreeNode *l = invertTree(root->left);
          TreeNode *r = invertTree(root->right);
          root->right = l;
          root->left = r;
      }
      return root;
  }
};

// BFS 这种方法也非常不错
TreeNode *invertTree(TreeNode *root) {
    if (!root) return root;

    queue<TreeNode *> myQueue;   // our queue to do BFS
    myQueue.push(root);         // push very first item - root

    while (!myQueue.empty()) {    // run until there are nodes in the queue

        TreeNode *node = myQueue.front();  // get element from queue
        myQueue.pop();                     // remove element from queue

        if (node->left) {         // add left kid to the queue if it exists
            myQueue.push(node->left);
        }

        if (node->right) {        // add right kid
            myQueue.push(node->right);
        }

        // invert left and right pointers
        swap(node->left, node->right);
    }
    return root;
}
```



#### Letter-Combinations-of-a-Phone-Number-17

```
//
// Created by 张达 on 2020/8/30. 1/5 17:50
//


#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  void recurion(const string& str,
                string &digits,
                int i,
                vector<string> &result,
                unordered_map<char, string> &map) {
      // recursion terminator
      if (i == digits.size()) {
          result.push_back(str);
          return;
      }
      // process
      string letters = map[digits[i]];
      for (int j = 0; j < letters.size(); ++j) {
          // drill down
          recurion(str + letters[j], digits, i + 1, result, map);
      }
  }
  vector<string> letterCombinations(string digits) {

      vector<string> result;
      if (digits.empty()) return result;

      unordered_map<char, string> map;
      map.emplace('2', "abc");
      map.insert(make_pair('3', "def"));
      map.emplace('4', "ghi");
      map.emplace('5', "jkl");
      map.emplace('6', "mno");
      map.emplace('7', "pqrs");
      map.emplace('8', "tuv");
      map.emplace('9', "wxyz");
      recurion("", digits, 0, result, map);
      return result;
  }
};
```



#### Lowest-Common-Ancestor-of-a-Binary-Tree-236

```
//
// Created by 张达 on 2020/8/27. 2/5 09:43
//

// 非常经典的题目，需要做的滚瓜烂熟

#include <vector>
#include <string>
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

// 数学归纳法思考：(本题不适合人肉递归，会绕晕)
// 1 root为空格， return null
// 2. 仅有一个根节点，则一定满足root == p and root == q, return root
// 3. 两个节点的棍树，一定满足root == p 或者 root == q

// 个人认为第一种解法不具有通用性，虽然很精妙，但是无法解决一类问题
class Solution1 {
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
      // recurison terminator
      if (!root) return nullptr;
      if (root == p or root == q) return root;

      auto l = lowestCommonAncestor(root->left, p, q); // 如果不满足上述条件，继续遍历左子树
      auto r = lowestCommonAncestor(root->right, p, q);// 如果不满足上述条件，继续遍历右子树
      // 递归的返回值，是从最下层传上来的

      if (!l and !r) return nullptr;
      else if (l and !r) return l;
      else if (r and !l) return r;
      else return root;
  }
};

class Solution {
 private:
  int flag = 0;
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
      if (!root) return nullptr;
      if (root == p or root == q) {
          flag++;
          return root;
      }

      auto left = lowestCommonAncestor(root->left, p, q);
      if (flag == 2) return left;
      auto right = lowestCommonAncestor(root->right, p, q);
      if (!left) return left;
      if (!right) return right;
      return root;
  }
};

// 还有一种解法代码比较长，但是容易理解，同时具有通用性
// 算法思路：(通用解法)
// 1. 两个节点的公共祖先，一定在从根节点到各个节点的路径上。
// 2. 最近公共祖先，即同时出现在两条路径上，并且距离根节点最远的那个节点。
// 3. 简化为：求两条路径上最后一个相同的节点即可。
// space O(n)
// 注意： 这是典型的preorder遍历的问题

// 为啥可以AC？
class Solution2 {
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
      vector<TreeNode *> path;
      vector<TreeNode *> result_p;
      vector<TreeNode *> result_q;
      preorder(root, p, path, result_p);
      path.clear();
      preorder(root, q, path, result_q);

      TreeNode *res = NULL;
      int len = result_p.size() > result_q.size() ? result_q.size() : result_p.size();
      for (int i = 0; i < len; i++) {
          if (result_p[i] == result_q[i]) {
              res = result_q[i]; // 相等就更新，不相等就退出循环
          }
      }
      return res;
  }

  void preorder(TreeNode *node, TreeNode *search, vector<TreeNode *> &path, vector<TreeNode *> &result) {
      if (!node) return;

      path.push_back(node);
      if (node->val == search->val) {
          result = path;
          return; // 不建议这么写，特别的不规范，因为破坏了回溯的完整过程，变得混乱
      }
      preorder(node->left, search, path, result);
      preorder(node->right, search, path, result); // 对path修改了一大圈，最终还是回到原点。并且path中总是带着一个左节点的值，并且永远也找不到target，因此不会修改result
      path.pop_back();
  }
};
```



#### Majority-Element-169

```
//
// Created by 张达 on 2020/8/30. 1/5 18:11
//


class Solution {
 public:
  int majorityElement(vector<int>& nums) {

  }
};

```





#### Maximum-Depth-of-Binary-Tree-104

```
///
// Created by 张达 on 2020/8/25. 2/5 08:46
//

#include <vector>
#include <string>
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

// 这是最初始的代码
class Solution {
 public:
  int maxDepth(TreeNode *root) {
      if (!root) {
          return 0;
      }
      if (!root->left and !root->right) {
          return 1;
      }

      int l = maxDepth(root->left) + 1;
      int r = maxDepth(root->right) + 1;
      return max(l, r);
  }
};

// 这是优化之后的代码
class SolutionSimplify {
 public:
  int maxDepth(TreeNode *root) {
      if (!root) return 0;
      return max(maxDepth(root->left), maxDepth(root->right)) + 1;
  }
};
```



#### Minimum-Depth-of-Binary-Tree-111

```
//
// Created by 张达 on 2020/8/26. 1/5 09:10
//

#include <vector>
#include <string>
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

// 同最大深度类似，数学归纳法
// 是否存在右子树：
// 如果存在右子树，也存在左子树，则Min
// 如果存在右子树，但不存在左子树，return r
// 如果不存在右子树，return l
class Solution {
 public:
  int minDepth(TreeNode *root) {
      if (!root) {
          return 0;
      }
      if (!root->left and !root->right) {
          return 1;
      }
      int l = minDepth(root->left) + 1;
      int r = minDepth(root->right) + 1;
      if (!root->right) {
          return l;
      } else if (!root->left) {
          return r;
      } else {
          return min(l, r);
      }
  }
};

```





#### Path-Sum-112

```
//
// Created by 张达 on 2020/8/28. 23:56 2/5
//

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <vector>
#include <string>
#include <queue>
using namespace std;

class Solution {

 private:
  int flag = false;
  void preorder(TreeNode *node, int sum, int &val) {
      // recursion ternimator
      if (!node) return;

      // process current level logic
      val += node->val;
      if (!node->left and !node->right and sum == val) {
          flag = true; // 注意这里可以return，但是最好不要这么做，否则后面的reverse将无法执行
          // 虽然这里直接return，截断后面的reverse操作也可以ac（因为已经找到了，相当于剪枝），但是该做法不通用，会造成记忆错乱。
      }

      // drill down
      // 当上述if满足时，以下两句无效，效果相当于直接跳过，直接执行val -= node->val;
      preorder(node->left, sum, val);
      preorder(node->right, sum, val);

      // reverse states
      val -= node->val;
  }
 public:
  bool hasPathSum(TreeNode *root, int sum) {
      int val = 0;
      preorder(root, sum, val);
      return flag;
  }
};

class Solution2 {
 private:
  bool preorder(TreeNode *node, int sum, int &val) {
      if (!node) return false;

      val += node->val;
      if (!node->left and !node->right and sum == val) {
          return true;
      }
      bool l = preorder(node->left, sum, val);
      bool r = preorder(node->right, sum, val);
      val -= node->val;
      return l or r; // 虽然node本身不是，但只要起左右子树中有一个满足，即为true
  }
 public:
  bool hasPathSum(TreeNode *root, int sum) {
      int val = 0;
      return preorder(root, sum, val);
  }
};
```



#### Path-Sum-II-113

```
//
// Created by 张达 on 2020/8/28. 2/5 21:13
//

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <vector>
#include <string>
#include <queue>
using namespace std;

class Solution {
 private:
  // 既然是树的递归，就一定会用到preorder/inorder/postorder.递归函数名直接体现递归顺序即可
  void preorder(TreeNode *node, int sum, int &val, vector<vector<int>> &result, vector<int> &path) {
      // recursion terminator
      if (!node) return; // 如果为null，即不进入这层梦境，不对参数进行任何的改变

      // process current level logic
      val += node->val;
      path.push_back(node->val);
      if (!node->left && !node->right && val == sum) {
          result.push_back(path);
      }
      // drill down
      preorder(node->left, sum, val, result, path);
      preorder(node->right, sum, val, result, path);

      // reverse states
      val -= node->val;
      path.pop_back();
  }

 public:
  vector<vector<int>> pathSum(TreeNode *root, int sum) {
      vector<vector<int>> result;
      vector<int> path;
      int val = 0;
      // 注意：val即可以传引用，也可以传拷贝。
      // 因为无论是引用还是拷贝，回溯的过程中，都会不断的还原状态，即同一层梦境中的同一个变量值最终是不变的
      preorder(root, sum, val, result, path);
      return result;
  }
};

class Solution4 {
 public:
  vector<vector<int>> pathSum(TreeNode *root, int sum) {
      vector<vector<int>> result;
      vector<int> solution;
      preorder(root, sum, result, solution);
      return result;
  }

  void preorder(TreeNode *root, int sum, vector<vector<int>> &result, vector<int> &solution) {
      if (!root) return;

      solution.push_back(root->val);
      if (!root->left && !root->right && root->val == sum) {
          result.push_back(solution);
      }
      preorder(root->left, sum - root->val, result, solution);
      preorder(root->right, sum - root->val, result, solution);
      solution.pop_back();
  }
};
```





#### Path-Sum-III-437

```
//
// Created by 张达 on 2020/8/29. 08:03 1/5
//

// 这道题非常经典，需要做的滚瓜烂熟

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// 不从头结点开始，可以从任意节点开始
// 就是选和不选根节点的问题(不可以这么思考，会很难搞，需要转换问题)

class Solution {
 public:
  int pathSum(TreeNode *root, int sum) {
      unordered_map<int, int> map; // record <sum[0, j], frequency>
      map[0]++;

      int result = 0;
      preorder(root, 0, sum, result, map);
      return result;
  }

  // hashmap + preSum
  // sum[0, i-1] + sum[i, j] = sum[0, j]
  // total表示什么？
  void preorder(TreeNode *node, int sum, int target_sum, int &result, unordered_map<int, int> &map) {
      if (!node) return;

      sum += node->val; // 从根节点开始，一直不停的累加，下面没有回退(还原)的过程，表示sum[0, j]
      int preSum = sum - target_sum; // target_sum[0, i-1]
      if (map.find(preSum) != map.end()) { //说明从根节点到该节点的路径中，包含了一个可以
          result += map[preSum];
      }
      map[sum]++; //

      preorder(node->left, sum, target_sum, result, map);
      preorder(node->right, sum, target_sum, result, map);

      map[sum]--; // 抹去该层梦境的所有操作，挥一挥手，不带走一片云彩
      // val本身不需要回溯，一直往下走即可
  }
};

class Solution2 {
 public:
  int pathSum(TreeNode *root, int sum) {
      unordered_map<int, int> map; // record <sum[0, j], frequency>
      int result = 0;
      preorder(root, 0, sum, result, map);
      return result;
  }

  void preorder(TreeNode *node, int sum, int target_sum, int &result, unordered_map<int, int> &map) {
      // recursion terminator
      if (!node) return;

      // process current level logic
      sum += node->val;
      int preSum = sum - target_sum;
      if (sum == target_sum) result++; // 特殊情况吗，一定要注意
      if (map.find(preSum) != map.end()) {
          result += map[preSum];
      }
      map[sum]++;

      // drill down
      preorder(node->left, sum, target_sum, result, map);
      preorder(node->right, sum, target_sum, result, map);

      // reverse states
      map[sum]--;
  }
};
```



#### Permutations-46

```
//
// Created by 张达 on 2020/8/29. 22:21 2/5
//

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  void help(vector<int> &nums, int begin, vector<vector<int>> &result) {
      if (begin >= nums.size()) {
          result.push_back(nums);
          return;
      }

      for (int i = begin; i < nums.size(); i++) {
          swap(nums[i], nums[begin]); // 前序
          help(nums, begin + 1, result);
          swap(nums[i], nums[begin]); // 后续-体现回溯的还原过程
      }
  }

  vector<vector<int>> permute(vector<int> &nums) {
      vector<vector<int>> result;
      help(nums, 0, result);
      return result;
  }
};

 // 未AC
class Solution2 {
 public:
  void help(vector<int> &nums, int i, vector<vector<int>> &result) {
      if ( i >= nums.size()) {
          result.push_back(nums);
          return;
      }
//      if (i > nums.size()) return;

      swap(nums[i], nums[i+1]); //
      help(nums, i + 1, result);

      swap(nums[i], nums[i+1]); // 后续-体现回溯的还原过程
      help(nums, i + 1, result);

  }

  vector<vector<int>> permute(vector<int> &nums) {
      vector<vector<int>> result;
      help(nums, 0, result);
      return result;
  }
};
```





#### Permutations-II-47

```
//
// Created by 张达 on 2020/8/29. 1/5 22:22
//


#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
 public:
  void help(vector<int> &nums, int begin, vector<vector<int>> &result, set<vector<int>>& set) {
      if (begin >= nums.size()) {
          if (set.find())
          result.push_back(nums);
          return;
      }

      for (int i = begin; i < nums.size(); i++) {
          swap(nums[i], nums[begin]); // 前序
          help(nums, begin + 1, result);
          swap(nums[i], nums[begin]); // 后续
      }
  }

  vector<vector<int>> permuteUnique(vector<int> &nums) {
      vector<vector<int>> result;
      set<vector<int>> set;
      sort(nums.begin(), nums.end());
      help(nums, 0, result,set);
      return result;
  }
};


//This is like the Permutation I solution, but we use an unordered_set to avoid swapping elements that are the same (which would generate identical permutations).

class Solution2 {
 public:

  void permuteUniqueHelper(int i, vector<int>& nums, vector<vector<int> >& result) {
      if (i == nums.size()) { result.emplace_back(nums); return; }
      unordered_set<int> st;
      for (int j = i; j < nums.size(); ++j) {
          if (st.count(nums[j]) == 1) { continue; }
          st.insert(nums[j]);
          std::swap(nums[i], nums[j]);
          permuteUniqueHelper(i + 1, nums, result);
          std::swap(nums[i], nums[j]);
      }
  }

  vector<vector<int>> permuteUnique(vector<int>& nums) {
      vector<vector<int> > result;
      permuteUniqueHelper(0, nums, result);
      return result;
  }
};
```



#### Pow-50

```
//
// Created by 张达 on 2020/8/30. 2/5 15:03
//

#include <iostream>
using namespace std;

// time complexity O(logn)
// space complexity O(1)

// 分治法
class Solution {
 public:
  double fastPow() {
      return 0;
  }
  double myPow(double x, int n) {
    // recursion ternimator

    //process (split your big probledms)

    // dirll down (subproblems)
    // process 和 drill down 往往合在一起

    // merge (subresult)

    // reverse status

    return fastPow()
  }
};

```



#### recursion-template

```
//
// Created by 张达 on 2020/8/30. 14:15
//
// 递归模板，需要默写的滚瓜烂熟

#include <iostream>
using namespace std;
void recursion(int level, int param) {
    // recursion terminator
    if (level > MAX_LEVEL) {
        //process result;
        return;
    }

    // process current logic
    process(level, param);

    // drill down
    recursion(level + 1, param);

    // reverse the current level status if needed
}

```



#### remove-spaces-form-a-given-string

```
//
// Created by 张达 on 2020/8/26. 21:37
//

//https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/

#include <iostream>
#include <cstring>
using namespace std;

// time O(n)
void removeSpace(string& str) {
    int j = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            swap(str[i], str[j++]);
        }
    }
    str[j] = '\0';
}

int main() {
    string str = "geeks  for geeks";
    removeSpace(str);
    printf("%s\n", str.c_str());
    return 0;
}

```





#### Serialize-and-Deserialize-Binary-Tree-297

```
//
// Created by 张达 on 2020/8/25. 2/5 19:48
//

// 经典题目，需要反复练习，写的滚瓜烂熟
// n叉树的序列化与反序列化，与二叉树异曲同工

#include <vector>
#include <string>
#include <queue>
#include <sstream>
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

// 尝试不适用getline，而是手动解析string
// 递归形式简洁明了
class Codec2 {
 public:

  // Encodes a tree to a single string.
  string serialize(TreeNode *root) {
      if (!root) return "#";

      // 相当于前序遍历
      string str = to_string(root->val) + ","
          + serialize(root->left) + ","
          + serialize(root->right);
      printf("%s\n", str.c_str());
      return str;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data) {
      if (data == "#") return nullptr;
      stringstream s(data);
      return makeDeserialize(s);
  }

  TreeNode *makeDeserialize(stringstream &s) {
      string str;
      getline(s, str, ','); // read a string splited by ,
      if (str == "#") return nullptr;

      // 前序遍历，解码要和编码对应上
      TreeNode *root = new TreeNode(stoi(str));
      auto l = makeDeserialize(s);
      auto r = makeDeserialize(s);
      root->left = l;
      root->right = r;
      // 由于局部变量l和r不会被任何东西改变，可以直接4句合并为2句。
      return root;
  }
};


// 层序遍历太复杂了，代码又臭又长，还容易出错，不采纳
class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root) {
      string res;
      queue<TreeNode *> que;
      que.push(root);
      while (!que.empty()) {
          int siz = que.size();
          while (siz--) {
              TreeNode *cur = que.front();
              que.pop();
              if (!cur) {
                  res += "#,"; // 技术处理
              } else {
                  string str_val = to_string(cur->val) + ",";
                  res += str_val;
                  que.push(cur->left);
                  que.push(cur->right);
              }
          }
      }
      printf("%s\n", res.c_str());
      return res;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data) {
      stringstream s(data);
      string str_node;
      queue<TreeNode *> que;
      getline(s, str_node, ',');

      TreeNode *root;
      if (str_node == "#") {
          return nullptr;
      } else {
          root = new TreeNode(stoi(str_node)); // 先把头结点构造出来
          que.push(root);
      }

      while (!que.empty()) {
          TreeNode *cur = que.front();
          que.pop();
          if (cur) {  // 技术处理
              string str_left, str_right;
              getline(s, str_left, ',');
              getline(s, str_right, ',');

              if (str_left != "#") {
                  auto l = new TreeNode(stoi(str_left));
                  cur->left = l;
                  que.push(l);
              }
              if (str_right != "#") {
                  auto r = new TreeNode(stoi(str_right));
                  cur->right = r;
                  que.push(r);
              }
          }
      }
      return root;
  }
};

vector<string> splitString(string s, char delim) {
    vector<string> result;
    string str;
    s.push_back(delim);

    if (s.empty()) return result;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == delim) {
            result.push_back(str);
            printf("%s\n", str.c_str());
            str.clear();
        } else {
            str += s[i];
        }
    }
    return result;
}

int main() {
    splitString("1,2,3,4,5", ',');
}
```



#### Subsets-78

```
//
// Created by 张达 on 2020/8/30. 2/5 15:33
//

#include <vector>
using namespace std;

// 利用递归去模拟每次放入和取出的操作
class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
      vector<vector<int>> result; // 存放最终结果
      vector<int> item; // 存在中间的过程
      help(nums, 0, result, item);
      return result;

  }

  void help(vector<int>& nums, int i, vector<vector<int>>& res, vector<int>& item) {
      // recursion terminator
      if (i >= nums.size()) {
          res.push_back(item);
          return;
      }

      // drill down
      item.push_back(nums[i]);
      help(nums, i + 1, res, item); // 放入

      item.pop_back();
      help(nums, i + 1, res, item); // 不放入
  }
};


class Solution2 {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
      vector<vector<int>> result; // 存放最终结果
      vector<int> item; // 存在中间的过程
      help(nums, 0, result, item);
      return result;

  }

  void help(vector<int>& nums, int i, vector<vector<int>>& res, vector<int>& item) {
      // recursion terminator
      if (i >= nums.size()) {
          res.push_back(item);
          return;
      }

      // drill down
      help(nums, i + 1, res, item); // 不放入

      item.push_back(nums[i]);
      help(nums, i + 1, res, item); // 放入

      item.pop_back();
  }
};

```



#### Top-K-Frequent-Elements-347

```
//
// Created by 张达 on 2020/8/30. 1/5 18:11
//

#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
 private:
  static bool compare(int a, int b) {
      return a > b;
  }

 public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
      vector<int> result;
      map<int, int> map;

      for (int i = 0; i < nums.size(); ++i) {
              map[nums[i]]++;
      }

      sort(map.begin()->second, map.end()->second, compare);

      auto map_iterator = map.begin();
      int cnt = 0;
      while (map_iterator != map.end() and cnt < k) {
          result.push_back(map_iterator->second);
          ++map_iterator;
          --k;
      }
      return result;
  }
};

// 非常好的方法
// 优先队列
class Solution1 {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
      map<int,int> map;
      for(int num : nums){
          map[num]++;
      }

      vector<int> res;
      // pair<first, second>: first is frequency,  second is number
      priority_queue<pair<int,int>> pq;
      for(auto it = map.begin(); it != map.end(); it++){
          pq.push(make_pair(it->second, it->first));
          // 如果优先队列中的元素个数大于size - k，则说明
          if(pq.size() > (int)map.size() - k){
              res.push_back(pq.top().second);
              pq.pop();
          }
      }
      return res;
  }
};


// heap

class Solution2 {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
      unordered_map<int, int> cnt;
      for (auto num : nums) cnt[num]++;
      for (auto kv : cnt) {
          pq.push({kv.second, kv.first});
          while (pq.size() > k) pq.pop();
      }
      vector<int> res;
      while (!pq.empty()) {
          res.push_back(pq.top().second);
          pq.pop();
      }
      return res;
  }
};


// selection algorithm
class Solution3 {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
      vector<int> res;
      if (!nums.size()) return res;
      unordered_map<int, int> cnt;
      for (auto num : nums) cnt[num]++;
      vector<pair<int, int>> num_with_cnt;
      for (auto kv : cnt) {
          num_with_cnt.push_back({kv.first, kv.second});
      }
      kselection(num_with_cnt, 0, num_with_cnt.size()-1, k);
      for (int i = 0; i < k && i < num_with_cnt.size(); ++i) {
          res.push_back(num_with_cnt[i].first);
      }
      return res;
  }

  void kselection(vector<pair<int, int>>& data, int start, int end, int k) {

      if (start >= end) return;
      auto pv = data[end];
      int i = start;
      int j = start;
      while (i < end) {
          if (data[i].second > pv.second) {
              swap(data[i++], data[j++]);
          } else {
              ++i;
          }
      }
      swap(data[j], data[end]);
      int num = j - start + 1;
      if (num == k) return;
      else if (num < k) {
          kselection(data, j + 1, end, k - num);
      } else {
          kselection(data, start, j - 1, k);
      }
  }
};

//using bucket sort
class Solution4 {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
      vector<int> res;
      if (!nums.size()) return res;
      unordered_map<int, int> cnt;
      for (auto num : nums) cnt[num]++;
      vector<vector<int>> bucket(nums.size() + 1);
      for (auto kv : cnt) {
          bucket[kv.second].push_back(kv.first);
      }

      for (int i = bucket.size() - 1; i >= 0; --i) {
          for (int j = 0; j < bucket[i].size(); ++j){
              res.push_back(bucket[i][j]);
              if (res.size() == k) return res;
          }
      }
      return res;
  }
};

```



#### Validate-Binary-Search-Tree-98

```
//
// Created by 张达 on 2020/8/27. 2/5 19:48
//

#include <vector>
#include <string>
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

// 相对较易理解
class Solution2 {
 public:
  bool isValidBST(TreeNode *root) {
      return recurse(root, LONG_MIN, LONG_MAX);
  }

  bool recurse(TreeNode *root, long lower, long upper) {
      // recursion terminator
      if (!root) return true;

      // process logic in current level
      long val = root->val;

      if ((val <= lower) || (val >= upper)) {
          return false;
      }

      // drill down
      return recurse(root->left, lower, val) and recurse(root->right, val, upper);
  }
};
```


