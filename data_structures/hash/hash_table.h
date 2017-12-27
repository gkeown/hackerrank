/* HASH TABLE */
typedef struct ht_item {
    char *key;
    char *value;
} ht_item;

typedef struct hash_table {
    int base_size;
    int size;
    int count;
    ht_item **items;
} ht_hash_table;

void ht_insert(ht_hash_table* ht, const char *key, const char *value);
char * ht_search(ht_hash_table* ht, const char *key);
void ht_delete(ht_hash_table* h, const char *key);
