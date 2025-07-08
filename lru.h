#ifndef _LRU_H_
#define _LRU_H_

#include "list.h"

typedef struct {
    int key;
    int value;
    struct list_head list;
} lru_node_t;

typedef struct {
    int size;
    int capacity;
    lru_node_t* items;
} lru_cache_t;

lru_cache_t* lru_init(int capacity);
void lru_deinit(lru_cache_t* cache);
int lru_get(lru_cache_t* cache, int key);
void lru_put(lru_cache_t* cache, int key, int value);

// debug function
void print_cache(lru_cache_t* cache);
void print_list();

#endif
