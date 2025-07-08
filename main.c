#include <stdio.h>
#include "lru.h"

#define TEST1
#define TEST2
#define TEST3
#define DEBUG
#define TEST_COUNT 20

void lru_put_and_print(lru_cache_t* cache, int key, int value)
{
    lru_put(cache, key, value);
    print_list();
    print_cache(cache);
}

void lru_get_and_print(lru_cache_t* cache, int key)
{
    printf("lru_get key=%d value=%d\n", key, lru_get(cache, key));
    print_list();
    print_cache(cache);
}

int main ()
{
    lru_cache_t* lru_cache = NULL;
#ifdef TEST1
    // https://www.geeksforgeeks.org/dsa/design-a-data-structure-for-lru-cache/
    lru_cache = lru_init(2);
    lru_put_and_print(lru_cache, 1, 1);
    lru_put_and_print(lru_cache, 2, 2);
    lru_get_and_print(lru_cache, 1);
    lru_put_and_print(lru_cache, 3, 3);
    lru_get_and_print(lru_cache, 2);
    lru_put_and_print(lru_cache, 4, 4);
    lru_get_and_print(lru_cache, 1);
    lru_get_and_print(lru_cache, 3);
    lru_get_and_print(lru_cache, 4);
    lru_deinit(lru_cache);
#endif

#ifdef TEST2
    lru_cache = lru_init(3);
    // https://www.geeksforgeeks.org/operating-systems/page-replacement-algorithms-in-operating-systems/
    int test[20] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    for (int i=0; i < TEST_COUNT; i++) {
        lru_put_and_print(lru_cache, i, test[i]);
    }
    lru_deinit(lru_cache);
#endif

#ifdef TEST3
    lru_cache = lru_init(3);
    // https://www.geeksforgeeks.org/system-design/lru-cache-implementation/
    int value = -1;
    lru_put_and_print(lru_cache, 1, 100);
    lru_put_and_print(lru_cache, 2, 200);
    lru_put_and_print(lru_cache, 3, 300);
    lru_get_and_print(lru_cache, 2);
    lru_get_and_print(lru_cache, 4);
    lru_put_and_print(lru_cache, 4, 400);
    lru_put_and_print(lru_cache, 3, 500);
    lru_get_and_print(lru_cache, 4);
    lru_put_and_print(lru_cache, 1, 100);
    lru_deinit(lru_cache);
#endif

}

