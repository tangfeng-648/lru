#include <stdio.h>
#include <stdlib.h>
#include "lru.h"

// #define DEBUG

static struct list_head* lru_head;

static lru_cache_t* lru_create(int capacity) {
    lru_cache_t* cache = (lru_cache_t*)malloc(sizeof(lru_cache_t));
    cache->size = 0;
    cache->capacity = capacity;
    cache->items = calloc(capacity, sizeof(lru_node_t));

    for(int i=0; i < capacity; i++) {
        cache->items[i].key = i;
        cache->items[i].value = -1;
    }

    return cache;
}

static void lru_destory(lru_cache_t* cache)
{
    list_for_each_entry_safe(lru_node_t, pos, lru_head, list) {
        list_del(&pos->list);
        free(pos);
    }

    free(cache->items);
    free(cache);
}

void print_cache(lru_cache_t* cache)
{
    printf("cache list: ");
    for(int i=0; i < cache->capacity; i++) {
        if(cache->items[i].value == -1)
            continue;
        printf("%d[%d] ", cache->items[i].key, cache->items[i].value);
    }
    printf("\n");
}

void print_list()
{
    printf("--------------------------------------------------------------\n");
    printf("head <--> ");
    list_for_each_entry(lru_node_t, pos, lru_head, list) {
        printf("%d[%d] <--> ", pos->key, pos->value);
    }
    printf("tail");
    printf("\n--------------------------------------------------------------\n");
}

static void lru_removetail(lru_cache_t* cache, lru_node_t* new)
{
    lru_node_t* node = list_last_entry(lru_head, lru_node_t, list);
    list_del(lru_head->prev);

#ifdef DEBUG
    printf("key:%d free:%p\n", node->key, node);
#endif

    for (int i=0; i < cache->capacity; i++) {
        if(cache->items[i].value != -1 && cache->items[i].key == node->key) {
            cache->items[i] = *new;
        }
    }

    free(node);
    cache->size--;
}

void lru_put(lru_cache_t* cache, int key, int value)
{
    int index = key % cache->capacity;
    
    for (int i=0; i < cache->capacity; i++) {
        if(cache->items[i].value != -1 && cache->items[i].key == key) {
            list_for_each_entry_safe(lru_node_t, pos, lru_head, list) {
                if (key == pos->key) {
                    pos->value = value;
                    list_move_to(&pos->list, lru_head);
                }
            }
            cache->items[i].value = value;
            return ;
        }
    }

    lru_node_t* node = malloc(sizeof(lru_node_t));
    node->value = value;
    node->key = key;
    cache->size++;
    list_add(&node->list, lru_head);
#ifdef DEBUG
    printf("key:%d new:%p list:%p\n", node->key, node, node->list);
#endif

    if (cache->size > cache->capacity) {
        lru_removetail(cache, node);
    } else{
        cache->items[index] = *node;
    }

    return;
}

int lru_get(lru_cache_t* cache, int key)
{
    for (int i=0; i < cache->capacity; i++) {
        if (cache->items[i].value != -1 && cache->items[i].key == key) {
            list_for_each_entry_safe(lru_node_t, pos, lru_head, list) {
                if (key == pos->key) {
                    list_move_to(&pos->list, lru_head);
                    return pos->value;
                }
            }
        }
    }
    return -1;
}

lru_cache_t* lru_init(int capacity)
{
    lru_head = malloc(sizeof(struct list_head));
    list_inithead(lru_head);
    return lru_create(capacity);
}

void lru_deinit(lru_cache_t* cache)
{
    lru_destory(cache);
    free(lru_head);
}
