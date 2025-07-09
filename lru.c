#include <stdio.h>
#include <stdlib.h>
#include "lru.h"

lru_cache_t* lru_create_easy(int capacity)
{
    lru_create(capacity, capacity);
}

lru_cache_t* lru_create(int capacity, int slots) {
    lru_cache_t* cache = (lru_cache_t*)malloc(sizeof(lru_cache_t));
    if(slots < capacity)
        slots = capacity;
    cache->nr_slot = slots;
    cache->size = 0;
    cache->capacity = capacity;
    cache->slots = malloc(cache->nr_slot * sizeof(struct list_head));

    list_inithead(&cache->lru_head);
    for (int i = 0; i < cache->nr_slot; i++) {
        list_inithead(&cache->slots[i]);
    }

    return cache;
}

void lru_destory(lru_cache_t* cache)
{
    list_for_each_entry_safe(lru_node_t, pos, &cache->lru_head, lru_list) {
        list_del(&pos->lru_list);
        free(pos);
    }

    free(cache->slots);
    free(cache);
}

void print_cache(lru_cache_t* cache)
{
    printf("cache: ");
    for (int i = 0; i < cache->nr_slot; i++) {
        if(list_is_empty(&cache->slots[i])) {
            printf(" [] ");
            continue;
        }

        list_for_each_entry_safe(lru_node_t, pos, &cache->slots[i], hash_list) {
                printf("%d:%d[%d] ", i, pos->key, pos->value);
        }
    }
    printf("\n--------------------------------------------------------------\n");
}

void print_list(lru_cache_t* cache)
{
    printf("--------------------------------------------------------------\n");
    printf("head <--> ");
    list_for_each_entry(lru_node_t, pos, &cache->lru_head, lru_list) {
        printf("%d[%d] <--> ", pos->key, pos->value);
    }
    printf("tail\n");
}

void print_lru_cache(lru_cache_t* cache)
{
    print_list(cache);
    print_cache(cache);
}

static void lru_removetail(lru_cache_t* cache, lru_node_t* new)
{
    lru_node_t* node = list_last_entry(&cache->lru_head, lru_node_t, lru_list);
    list_del(&node->lru_list);
    list_del(&node->hash_list);

    free(node);
    cache->size--;
}

void lru_put(lru_cache_t* cache, int key, int value)
{
    int index = key % cache->nr_slot;

    if(cache == NULL)
        return;

    if(!list_is_empty(&cache->slots[index])) {
        list_for_each_entry(lru_node_t, pos, &cache->slots[index], hash_list) {
            if(key == pos->key) {
                pos->value = value;
                list_move_to(&pos->lru_list, &cache->lru_head);
                return;
            }
        }
    }

    lru_node_t* node = malloc(sizeof(lru_node_t));
    node->value = value;
    node->key = key;
    list_inithead(&node->hash_list);
    list_inithead(&node->lru_list);
    cache->size++;
    list_add(&node->lru_list, &cache->lru_head);
    list_add(&node->hash_list, &cache->slots[index]);

    if (cache->size > cache->capacity) {
        lru_removetail(cache, node);
    }

    return;
}

int lru_get(lru_cache_t* cache, int key)
{
    int index = key % cache->nr_slot;

    if(cache == NULL)
        return -1;

    if(list_is_empty(&cache->slots[index]))
        return -1;

    list_for_each_entry_safe(lru_node_t, pos, &cache->slots[index], hash_list) {
        if(key == pos->key) {
            list_move_to(&pos->lru_list, &cache->lru_head);
            return pos->value;
        }
    }

    return -1;
}
