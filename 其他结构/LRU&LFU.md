#### [LRU 缓存](https://leetcode-cn.com/problems/lru-cache/)

> 请你设计并实现一个满足  `LRU` (最近最少使用) 缓存 约束的数据结构。
> 实现 `LRUCache `类：
> `LRUCache(int capacity)` 以 正整数 作为容量` capacity `初始化 LRU 缓存
> `int get(int key)` 如果关键字` key `存在于缓存中，则返回关键字的值，否则返回 -1 。
> `void put(int key, int value) `如果关键字 key 已经存在，则变更其数据值` value` ；如果不存在，则向缓存中插入该组` key-value `。如果插入操作导致关键字数量超过 `capacity` ，则应该 逐出 最久未使用的关键字。
> 函数 `get` 和 `put `必须以 O(1) 的平均时间复杂度运行。
>
> 示例：
>
> ```
> 输入
> ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
> [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
> 输出
> [null, null, null, 1, null, -1, null, -1, 3, 4]
> 
> 解释
> LRUCache lRUCache = new LRUCache(2);
> lRUCache.put(1, 1); // 缓存是 {1=1}
> lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
> lRUCache.get(1);    // 返回 1
> lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
> lRUCache.get(2);    // 返回 -1 (未找到)
> lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
> lRUCache.get(1);    // 返回 -1 (未找到)
> lRUCache.get(3);    // 返回 3
> lRUCache.get(4);    // 返回 4
> ```

简单分析一下：

1. LRU需要能直接通过`key`找到对应的`value`，那么就需要一个哈希表来存储
2. 对于许久未用要弹出，对于最近使用要更新记录，对于可以以O(1)插入删除的数据结构就是链表，而因为要处理前后关系，所以用双链表比较合适

![LRU](LRU&LFU.assets/LRU.jpeg)

```cpp

//外部定义一个双链表
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用头部和尾部节点
        head = new DLinkedNode();//靠近头部则最近使用过
        tail = new DLinkedNode();//靠近尾部说明较久没用
        head->next = tail; 
        tail->prev = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);//移到头部
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
    
    //将节点添加到头节点的后面
    //头节点的后面表示最近刚访问过的节点
    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    //删除链表中的节点
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    //移除链表中的节点，需要先删除，然后再插入到头节点的后面
    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }
    //删除末尾节点，当且仅当存储的节点个数超过预设容量时
    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};
```

