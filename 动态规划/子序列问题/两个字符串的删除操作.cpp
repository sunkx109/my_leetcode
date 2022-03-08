/*
leetcode 583 两个字符串的删除操作
https://leetcode-cn.com/problems/delete-operation-for-two-strings/


给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。

每步 可以删除任意一个字符串中的一个字符。

*/




/*
动态规划思路 : 维护一个长度为[word1.size(),word2.size()]的二维数组
定状态 : dp[i][j]表示 word1[0:i] 和 word2[0:j] 需要的最小删除操作数
状态转移 : if(word1[i]==word2[j])
             dp[i][j] = dp[i-1][j-1];
          else
             dp[i][j] = min(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+2)
*/



#include<iostream>
#include<vector>
using namespace std;

//对于这种二维的dp画个矩阵来协助分析
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>>dp(word1.size()+1,vector<int>(word2.size()+1,0));
        //初始边界条件
        for(int i=0;i<=word2.size();i++)
        {
            dp[0][i]=i;
        }
        for(int i=0;i<=word1.size();i++)
        {
            dp[i][0]=i;
        }

        for(int i=1;i<=word1.size();i++)
        {
            for(int j=1;j<=word2.size();j++)
            {
                //如果当前word1[i-1] == word2[j-1]
                //说明不需要增加新的删除操作，直接延用 dp[i-1][j-1]
                if(word1[i-1]==word2[j-1])
                  dp[i][j] = dp[i-1][j-1];
                else
                //否则就从(i-1,j) (i,j-1) (i-1,j-1)里面选一个操作成(i,j)所需的最小操作数即可
                  dp[i][j] = min({dp[i - 1][j - 1] + 2, dp[i - 1][j] + 1, dp[i][j - 1] + 1});
            }
        }
        return dp[word1.size()][word2.size()];

    }
};

