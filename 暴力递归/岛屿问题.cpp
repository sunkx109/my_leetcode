/*
leetcode 200 岛屿问题
https://leetcode-cn.com/problems/number-of-islands/

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

示例 1：
输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1

*/

#include<iostream>
#include<vector>

class Solution {
public:
    //每次dfs时就按题目给定的移动规则进行dfs深度遍历
    //每次dfs之后都会把与入口位置直接或间接相邻的位置都访问到
    void dfs(vector<vector<char>>& grid,int r,int c)
    {
        if(r<grid.size()&&r>=0&&c<grid[0].size()&&c>=0&&grid[r][c]=='1')
        {
            grid[r][c]='2';
            dfs(grid,r+1,c);
            dfs(grid,r-1,c);
            dfs(grid,r,c-1);
            dfs(grid,r,c+1);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int res=0;
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0;j<grid[0].size();j++)
            {
                //进入df
                if(grid[i][j]=='1')
                {
                    res++;
                    dfs(grid,i,j);
                }
                
            }
        }
        return res;
    }
};


