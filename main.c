#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "lru.h"

#define TEST1
#define TEST2
#define TEST3
#define TEST4
#define TEST5

int get_random(void)
{
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    return (rand() % 65536);
}

void lru_put_and_print(lru_cache_t* cache, int key, int value)
{
    lru_put(cache, key, value);
    print_lru_cache(cache);
}

void lru_get_and_print(lru_cache_t* cache, int key)
{
    printf("lru_get key=%d value=%d\n", key, lru_get(cache, key));
    print_lru_cache(cache);
}

int main ()
{
    lru_cache_t* lru_cache = NULL;
#ifdef TEST1
    // https://www.geeksforgeeks.org/dsa/design-a-data-structure-for-lru-cache/
    lru_cache = lru_create_easy(2);
    lru_put_and_print(lru_cache, 1, 1);
    lru_put_and_print(lru_cache, 2, 2);
    lru_get_and_print(lru_cache, 1);
    lru_put_and_print(lru_cache, 3, 3);
    lru_get_and_print(lru_cache, 2);
    lru_put_and_print(lru_cache, 4, 4);
    lru_get_and_print(lru_cache, 1);
    lru_get_and_print(lru_cache, 3);
    lru_get_and_print(lru_cache, 4);
    lru_destory(lru_cache);
#endif

#ifdef TEST2
    // https://www.geeksforgeeks.org/operating-systems/page-replacement-algorithms-in-operating-systems/
    lru_cache = lru_create_easy(4);
    int test2[14] = {7,0,1,2,0,3,0,4,2,3,0,3,2,3};
    for (int i=0; i < sizeof(test2)/sizeof(int); i++) {
        lru_put_and_print(lru_cache, test2[i], test2[i]);
    }
    lru_destory(lru_cache);
#endif

#ifdef TEST3
    // https://www.scaler.com/topics/lru-page-replacement-algorithm/
    lru_cache = lru_create_easy(3);
    int test3[9] = {1,2,1,0,3,0,4,2,4};
    for (int i=0; i < sizeof(test3)/sizeof(int); i++) {
        lru_put_and_print(lru_cache, test3[i], test3[i]);
    }
    lru_destory(lru_cache);
#endif

#ifdef TEST4
    // https://www.geeksforgeeks.org/system-design/lru-cache-implementation/
    lru_cache = lru_create_easy(3);
    lru_put_and_print(lru_cache, 1, 100);
    lru_put_and_print(lru_cache, 2, 200);
    lru_put_and_print(lru_cache, 3, 300);
    lru_get_and_print(lru_cache, 2);
    lru_get_and_print(lru_cache, 4);
    lru_put_and_print(lru_cache, 4, 400);
    lru_put_and_print(lru_cache, 3, 500);
    lru_get_and_print(lru_cache, 4);
    lru_put_and_print(lru_cache, 1, 100);
    lru_destory(lru_cache);
#endif

#ifdef TEST5
    int count = 0;
    lru_cache = lru_create(5, 10);
    while(1){
        lru_put_and_print(lru_cache, get_random(), get_random());
        if(count = 10)
            lru_get_and_print(lru_cache, get_random());
        usleep(100000);
    }
    lru_destory(lru_cache);
#endif

    return 0;
}
