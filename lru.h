#ifndef _LRU_H_
#define _LRU_H_

#include "list.h"

typedef struct {
    int key;
    int value;
    struct list_head hash_list;
    struct list_head lru_list;
} lru_node_t;

typedef struct {
    int size;
    int capacity;
    int nr_slot;
    struct list_head *slots;
    struct list_head lru_head;
} lru_cache_t;

lru_cache_t* lru_create(int capacity, int slots);
lru_cache_t* lru_create_easy(int capacity);
void lru_destory(lru_cache_t* cache);
int lru_get(lru_cache_t* cache, int key);
void lru_put(lru_cache_t* cache, int key, int value);

// debug function
void print_lru_cache(lru_cache_t* cache);
#endif
