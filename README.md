# LRU
LRU算法的C语言实现版本，用作C语言环境下的缓存版本
## API
简单的API接口:
``
lru_cache_t* lru_create(int capacity, int slots);
lru_cache_t* lru_create_easy(int capacity);
void lru_destory(lru_cache_t* cache);
int lru_get(lru_cache_t* cache, int key);
void lru_put(lru_cache_t* cache, int key, int value);
```
## 说明
`lru_create`提供了lru算法的创建函数，支持缓存容量capacity，hash的加载槽数量slots两个参数。  
capacity越大则lru缓存算法容量越大，slots越大，则hash碰撞概率越底，算法更趋向于O(1)，slots不小于capacity。
`lru_create_easy`提供了lru算法的简单创建函数，默认将slots设置为capacity。
`lru_destory`lru算法的销毁函数，和`lru_create`成对出现
`lru_get`提供lru算法的查询，如果在缓存中，则通过hash直接取出，否则返回-1
`lru_put`提供lru算法的插入，如果在缓存中，则更新缓存的值，然后移动到双链表头，如果不在缓存中，则添加节点，并踢出最后一个节点

## 测试
如下编译
`gcc -I. main.c lru.c -o lru`

提供五种测试案例:
1. 来自https://www.geeksforgeeks.org/dsa/design-a-data-structure-for-lru-cache/的数据测试
2. 来自https://www.geeksforgeeks.org/operating-systems/page-replacement-algorithms-in-operating-systems/的数据测试
3. 来自https://www.scaler.com/topics/lru-page-replacement-algorithm/的数据测试
4. 来自https://www.geeksforgeeks.org/system-design/lru-cache-implementation/的数据测试
5. 循环压力测试

测试结果可观测
