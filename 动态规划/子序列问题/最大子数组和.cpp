/*
leetcode 53 最大子数组和
https://leetcode-cn.com/problems/maximum-subarray/

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。

*/

#include<iostream>
#include<vector>

/*
动态规划思路 : 维持一个长度为nums.size()的 vector<int> dp

确定状态 : dp[i] 表示以nums[i]结尾的最大子数组的和

初始化 : 所有的dp[i] 都初始化为nums[i] 因为初始状态 以自己为结尾的最大子数组的和就为自己 

状态转移 :  dp[i] = max(nums[i],dp[i-1]+nums[i]); 


*/



/*
在做这一题的时候，定状态可能有两种情况
1. dp[i]表示以nums[i]结尾的最大子数组的和
2. dp[i]表示在nums[0:i]内的最大子数组的和

那么为什么选1 而不选2呢？

假设我们选2，那么状态转移该如何做？dp[i-1]和dp[i]之间的关系如何确定？
因为题目要求的是连续的子数组，而以2定状态，就无法判断nums[i] 和 dp[i-1]中的最大连续的子数组 是否连续

*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int>dp(nums.size(),0);
        dp[0]=nums[0];
        int res=dp[0];
        for(int i=1;i<nums.size();i++)
        {
            //如果以前一个数字结尾的最大子数组之和加上自己大于自己本身那么就记录
            //否则就是最大子数组之和就是自己
            dp[i] = max(nums[i],dp[i-1]+nums[i]);
            res=max(res,dp[i]);
        }
        return res;
    }
};

