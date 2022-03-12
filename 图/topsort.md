# 拓扑排序

#### [课程表](https://leetcode-cn.com/problems/course-schedule/)

> 你这个学期必须选修 `numCourses `门课程，记为 `0 `到 `numCourses - 1` 。
>
> 在选修某些课程之前需要一些先修课程。 先修课程按数组` prerequisites` 给出，其中 `prerequisites[i] = [ai, bi] `，表示如果要学习课程` ai` 则 必须 先学习课程  `bi` 。
>
> 例如，先修课程对` [0, 1] `表示：想要学习课程 `0` ，你需要先完成课程 `1` 。
> 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。
>
> **示例 1：**
>
> ```
> 输入：numCourses = 2, prerequisites = [[1,0]]
> 输出：true
> 解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
> ```

```
没啥好说的直接 拓扑排序
```

```cpp
class Solution {
public:
    vector<vector<int>>Graph;//图结构
    vector<int>in_du;//入度
    unordered_set<int> visited;//备忘录 
    void topsort()
    {
        //拓扑排序实际上就是基于bfs来找入度为0的节点，然后进行遍历
        deque<int>queue;
        
        //结点入度一个个找
        for(int i=0;i<in_du.size();i++)
        {
            if(in_du[i]==0)
            {   
                //找到入度为0的就加入队列中
                queue.push_back(i);
                visited.insert(i); //记录
            }
        }
        //队列不空
        while(queue.size()!=0)
        {
            //移除当前节点后，再找结点入度为0的结点
            for(int j=0;j<Graph[queue[0]].size();j++)
            {
                //[from,to] 将to结点的入度--
                in_du[Graph[queue[0]][j]]--;
                //同时查看是否入度为0且没有被遍历过
                if(visited.count(Graph[queue[0]][j])==0&&in_du[Graph[queue[0]][j]]==0)
                {
                    queue.push_back(Graph[queue[0]][j]);
                    visited.insert(Graph[queue[0]][j]);
                }                  
            }
            queue.pop_front();
        }
    }
  
  
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        Graph.assign(numCourses,vector<int>());
        in_du.assign(numCourses,0);
        //建图
        for(int i=0;i<prerequisites.size();i++)
        {
            int from = prerequisites[i][1];
            int to = prerequisites[i][0];
            Graph[from].push_back(to);
            in_du[to]++;
        }
        topsort();
        if(visited.size()==numCourses) 
          return true;
        
        return false;

    }
};
```

