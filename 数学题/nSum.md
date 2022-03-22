## Two Sum

1. 给你一个**无序**数组和一个整数`target`，可以保证数组中**存在**两个数的和为`target`，请你返回这两个数的**索引**。

直接的做法就是暴力穷举，那么在暴力穷举的基础上优化一下，就可以用一个哈希表来记录，用空间换时间

```cpp
vector<int> twosum(vector<int>nums,int target)
{
    unordered_map<int,int>mymap;
    vector<int>res(2,-1);
    for(int i=0;i<nums.size();i++)
    {
        mymap[nums[i]]=i;
    }
    
    for(int i=0;i<nums.size();i++)
    {
        int other = target - nums[i];
        //如果other存在且不是nums[i]本身
        if(mymap.count(other)&&mymap[other]!=i)
        {
            res[0]=i;
            res[1] = mymap[other];
            return res;
        }
    }
    return res;
}
```

2. 给你一个数组和一个整数`target`，可以保证数组中**存在**两个数的和为`target`，请你返回这两个数。

因为是返回两个值，所以就不必在意原始次序，那么解法就是先对数组进行排序，之后通过双指针来操作即可

> 题目：**`nums` 中可能有多对儿元素之和都等于 `target`，请你的算法返回所有和为 `target` 的元素对儿，其中不能出现重复**。
>
> 示例1：
>
> ```
> 输入: nums = [1,3,1,2,2,3], target = 4
> 输出: [[1,3],[2,2]]
> ```

```cpp
vector<vector<int>> twoSumTarget(vector<int>& nums, int target) {
    // nums 数组必须有序
    sort(nums.begin(), nums.end());
    int lo = 0, hi = nums.size() - 1;
    vector<vector<int>> res;
    while (lo < hi) {
        int sum = nums[lo] + nums[hi];
        int left = nums[lo], right = nums[hi];
        if (sum < target) 
        {
            while (lo < hi && nums[lo] == left) lo++;
        } 
        else if (sum > target) 
        {
            while (lo < hi && nums[hi] == right) hi--;
        } 
        else 
        {
            res.push_back({left, right});
            while (lo < hi && nums[lo] == left) lo++;
            while (lo < hi && nums[hi] == right) hi--;
        }
    }
    return res;
}
```







## 3 Sum



## 4 Sum

