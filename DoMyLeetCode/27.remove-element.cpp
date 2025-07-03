/*
 * @lc app=leetcode id=27 lang=cpp
 *
 * [27] Remove Element
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // 快慢指针
        int slow = 0; int fast = 0;
        for(int i=0; i<nums.size();i++)
        {
            if(nums[fast] == val)
            {
                fast = fast +1;
            }
            else
            {
                nums[slow] = nums[fast]; // 当slow和fast不同时，相当于在做删除操作
                fast +=1;
                slow +=1;
            }
        }
        return slow;
    }
};
// @lc code=end

