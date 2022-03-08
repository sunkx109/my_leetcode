/*
leetcode 712 两个字符串的最小ASCII删除和
https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/

给定两个字符串s1 和 s2，返回 使两个字符串相等所需删除字符的 ASCII 值的最小和.

和 583.两个字符串的删除操作 类似

定状态 : dp[i][j]表示 s1[0:i] 和 s2[0:j] 需要的最小删除ASCII数
状态转移 : if(word1[i]==word2[j])
             dp[i][j] = dp[i-1][j-1];
          else
             dp[i][j] = min(dp[i-1][j]+Ascll(s1[i]),dp[i][j-1]+Ascll(s2[j]))

*/



#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    //char to int function
    int ascll(char s)
    {
        return 97+(s-'a');
    }
    int minimumDeleteSum(string s1, string s2) {
        vector<vector<int>>dp(s1.size()+1,vector<int>(s2.size()+1,0));
        //边界条件
        for(int i=1;i<=s1.size();i++)
        {
            dp[i][0] = dp[i-1][0]+ascll(s1[i-1]);
        }
        for(int i=1;i<=s2.size();i++)
        {
            dp[0][i] = dp[0][i-1]+ascll(s2[i-1]);
        }



        for(int i=1;i<=s1.size();i++)
        {
            for(int j=1;j<=s2.size();j++)
            {
                //如果s1[i-1]==s2[j-1] 沿用dp[i-1][j-1]
                if(s1[i-1]==s2[j-1])
                  dp[i][j] = dp[i-1][j-1];
                else
                //否则就找一个Ascll操作数小的
                  dp[i][j] = min(dp[i-1][j]+ascll(s1[i-1]),  dp[i][j-1]+ascll(s2[j-1]));
            }
        }
        return dp[s1.size()][s2.size()];
    }
};