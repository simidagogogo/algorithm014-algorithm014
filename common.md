# common



#### tree-node

```cpp
//
// Created by 张达 on 2020/10/16 20:03.
//

#ifndef PACED_REPEATITION_COMMON_TREE_NODE_H_
#define PACED_REPEATITION_COMMON_TREE_NODE_H_

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int val, TreeNode* left) : val(val), left(nullptr), right(nullptr) {}
};

#endif //PACED_REPEATITION_COMMON_TREE_NODE_H_
```



#### utils

```cpp
//
// Created by 张达 on 2020/10/16 19:58.
//

#ifndef PACED_REPEATITION_COMMON_UTILS_H_
#define PACED_REPEATITION_COMMON_UTILS_H_

#include <vector>
#include <iostream>
using namespace std;

void print(vector<int> arr, int n) {
    for (int i = 0; i < arr.size(); ++i) {
        printf("%d\t", arr[i]);
    }
}

void print_vector(vector<int> arr) {
    for_each(arr.begin(), arr.end(), [](int i){printf("%d ", i);});
}

void print_vector_delimiter(vector<int> arr, const char *delimiter) {
    ostream_iterator<int> it(cout, delimiter);
    copy(arr.begin(), arr.end(), it);
}

#endif //PACED_REPEATITION_COMMON_UTILS_H_
```
