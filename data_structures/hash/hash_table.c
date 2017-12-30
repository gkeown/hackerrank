#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prime.h"
#include "hash_table.h"

#define HT_INITIAL_BASE_SIZE (50)
#define HT_PRIME_1 (151)
#define HT_PRIME_2 (157)

/* dummy pow() */
int
power(int value, int factor)
{
    int result = 1;
    for (int i = 0; i < factor; i++) {
        result *= value;
    }
    return (result);
}

static ht_item *
ht_new_item(const char *key, const char *value)
{
    ht_item *new_item = (ht_item *) malloc(sizeof(ht_item));
    new_item->key = strdup(key);
    new_item->value = strdup(value);
    return (new_item);
}

static ht_hash_table *
ht_new_sized(const int base_size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = calloc((size_t) ht->size, sizeof(ht_item *));
    return (ht);
}

ht_hash_table *
ht_new(void) {
    return (ht_new_sized(HT_INITIAL_BASE_SIZE));
}

void *
ht_delete_item(ht_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void
ht_delete_hash_table(ht_hash_table *ht) {
    /* remove items from table first */
    for (int i = 0; i < ht->size; i++) {
        if (ht->items[i] != NULL) {
            ht_delete_item(ht->items[i]);
        }
    }
    free(ht->items);
    free(ht);
}

/* takes a string, a prime number larger than the alphabet and the number of buckets in the hash table */
int
ht_hash(const char *s, const int a, const int num_buckets)
{
    long hash = 0;
    const int len = strlen(s);

    /* convert the string to a large integer and then assign it a bucket */
    for (int i = 0; i < len; i++) {
        hash += (power(a, len - 1) * s[i]);
    }
    hash = hash % num_buckets;

    return (int) hash;
}

static int
ht_get_hash(const char *s, const int num_buckets, const int attempt)
{
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);

    /* use hash b if collision with hash a */
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

/* common address space used for deleted items */
static ht_item HT_DELETED_ITEM = {NULL, NULL};

static void
ht_resize(ht_hash_table *ht, const int base_size)
{
    if (base_size < HT_INITIAL_BASE_SIZE) {
        /* cannot get any smaller */
        return;
    }

    /* create a new hash table with smaller/larger size */
    ht_hash_table *new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item *item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            /* move non NULL or deleted items to the resized hash table */
            ht_insert(new_ht, item->key, item->value);
        }
    }
    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    /* swap new ht into ht pointer */
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item ** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    /* then delete the new ht point and the old items */
    ht_delete_hash_table(new_ht);
}

static void
ht_resize_up(ht_hash_table *ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void
ht_resize_down(ht_hash_table *ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}

/* insert entry into hash table */
void
ht_insert(ht_hash_table *ht, const char *key, const char *value)
{
    /* create a new hash item */
    ht_item *item = ht_new_item(key, value);

    /* get the hash index for this item */
    int index = ht_get_hash(item->key, ht->size, 0);

    /* point to this hash in the hash table */
    ht_item *cur_item = ht->items[index];

    int i = 1;
    /*
     * If an item already exists in this location, search until we find an empty item.
     * If a previously deleted item, use the current index.
     */
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {

        /* detect if this key already exist and if so, update it */
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                /* matching entry, delete the previous entry at this index */
                ht_delete_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }

        /* increment the attempt used in hash computation for each collision */
        index = ht_get_hash(cur_item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }

    /* assign item to this hash index */
    ht->items[index] = item;
    ht->count++;

    /* check if we need to increase the size of the hash table */
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
}

/* search for entry in hash table */
char *
ht_search(ht_hash_table *ht, const char *key)
{
    /* get the hash entry for this key */
    int index = ht_get_hash(key, ht->size, 0);

    /* find that index in the hash table */
    ht_item *cur_item = ht->items[index];

    /* if NULL there was never an item in this bucket, there may however be items marked as deleted */    
    int i = 1;
    while (cur_item != NULL) {

        /* jump over deleted items */
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                /* item found */
                return (cur_item->value);
            }
        }

        /* move to next item */
        index = ht_get_hash(cur_item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }

    return (NULL);
}

/* delete entry in hash table */
void
ht_delete(ht_hash_table *ht, const char *key)
{
    /* find the item to delete using key */
    int index = ht_get_hash(key, ht->size, 0);
    ht_item *cur_item = ht->items[index];

    int i = 0;
    while (cur_item != NULL) {
        /* jump over deleted items */
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                /* found item to be deleted */
                ht_delete_item(cur_item);
                /* mark index as deleted item by point to common address space */
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }

        /* try the next item */
        index = ht_get_hash(key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }

    /* decrement the number of items in the hash table */
    ht->count--;

    /* check if we need to decrease the size of the hash table */
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
}

void
print_hash(ht_hash_table *ht)
{
    if (ht == NULL) {
        return;
    }

    ht_item *cur_item = NULL;
    for (int i = 0; i < ht->size; i++) {

        cur_item = ht->items[i];
        if (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
            printf("[%s][%s]\n", cur_item->key, cur_item->value);
        }
    }
}
