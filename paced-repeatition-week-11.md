# paced-repeatition-week-11



#### Reformat-Date-1507

```cpp
//
// Created by 张达 on 2020/10/30 20:35.
//
#include <string>
#include <vector>
#include <map>
using namespace std;

class Solution {
 private:
  map<string, string> month_map{
      {"Jan", "01"},
      {"Feb", "02"},
      {"Mar", "03"},
      {"Apr", "04"},
      {"May", "05"},
      {"Jun", "06"},
      {"Jul", "07"},
      {"Aug", "08"},
      {"Sep", "09"},
      {"Oct", "10"},
      {"Nov", "11"},
      {"Dec", "12"}
  };

  map<string, string> day_map {
      {"1st", "01"},
      {"21st", "21"},
      {"31st", "31"},
      {"2nd", "02"},
      {"22nd", "22"},
      {"3rd", "03"},
      {"23rd", "23"}
  };

 public:
  Solution() {
      for (int i = 4; i <= 31; ++i) {
          if (i == 2 or i == 22 or i == 23 or i == 31) continue;
          if (i < 10) {
              day_map.insert(make_pair(to_string(i) + "th", "0" + to_string(i)));
          } else {
              day_map.insert(make_pair(to_string(i) + "th", to_string(i)));
          }
      }
  }

  string reformatDate(string s) {
      vector<string> v;
      string str;
      s.push_back(' ');
      for (int i = 0; i <= s.size() - 1; ++i) {
          if (s[i] != ' ') {
              str += s[i];
          } else {
              v.push_back(str);
              str = "";
          }
      }
      return v[2] + "-" + month_map[v[1]] + "-" + day_map[v[0]].substr(0, 2);
  }
};
```
