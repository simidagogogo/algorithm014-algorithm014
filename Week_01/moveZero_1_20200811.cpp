//思想：
/// 借用额外一个数组（虽说不符合要求）；
/// 遍历原有数组并将非零值按顺序放到额外数组，并计算出零值个数；
/// 根据零值个数将额外数组末尾值添加0，并将额外数组拷贝回当前数组
//时间复杂度：
//空间复杂度:
// can i modify this source code???
class Solution {
public:
    void moveZeroes(vector<int>& nums) {		
		vector<int> tmpNums;
		int zeroNumsize = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != 0) {
				tmpNums.push_back(nums[i]);
			} 
			else {
				zeroNumsize++;
			}
		}
		while(0 != zeroNumsize--) {
			tmpNums.push_back(0);
		}

		for (int i = 0; i < nums.size(); i++) {
			nums[i] = tmpNums[i];
			//cout << nums[i] << " ";
		}
		//cout << endl;
    }
};  
