#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define MAX_NAME_SIZE (256)

void
test_hash()
{
    int option = 1;

    ht_hash_table* ht = ht_new();

    while (option != 0) {

        printf("Select an option:\n");
        printf("1 - insert new entry\n");
        printf("2 - remove entry\n");
        printf("3 - search for an entry\n");
        printf("4 - print hash items\n");
        printf("0 - exit\n");
        scanf("%d", &option);

        char *value = malloc(sizeof(char) * MAX_NAME_SIZE);
        char *key = malloc(sizeof(char) * MAX_NAME_SIZE);

        switch (option) {
            case 1:
                printf("Add a key/value pair:\n");
                scanf("%s", key);
                scanf("%s", value);
                ht_insert(ht, key, value);
                break;
            case 2:
                printf("Remove a key:\n");
                scanf("%s", key);
                ht_delete(ht, key);
                break;
            case 3:
                printf("Search for a key:\n");
                scanf("%s", key);
                char *result = ht_search(ht, key);
                if (value != NULL) {
                    printf("Found %s\n", result);
                }
                break;
            case 4:
                printf("Printing items:\n");
                print_hash(ht);
                break;
            case 0:
                printf("...exiting...\n");
                break;
            default:
                printf("Invalid option, try again\n");
        }

        printf("[size: %d][count: %d]\n", ht->size, ht->count);
    }

    ht_delete_hash_table(ht);
}

void
test_array_subset(void)
{
    char array1[] = {'g', 'e', 'r', 'a', 'r', 'd'};
    char array2[] = {'e', 'r', 'a', 'r'};
    char array3[] = {'e', 'r', 'x'};

    /* create hash table */
    ht_hash_table *ht = ht_new();

    char *key = malloc(sizeof(char));
    char *value = malloc(sizeof(char));

    /* add first array elements to hash table */
    for (int i = 0; array1[i]; i++) {
        printf("processing %c\n", array1[i]);
        *key = array1[i];
        sprintf(value, "%d", i);
        ht_insert(ht, key, value);
        print_hash(ht);
    }

    /* search for array2 values in array1 */
    for (int i = 0; array2[i]; i++) {
        *key = array2[i];
        if (ht_search(ht, key) == NULL) {
            printf("%c not in array, failure\n", array2[i]);
            break;
        }
    }

    /* search for array2 values in array1 */
    for (int i = 0; array3[i]; i++) {
        *key = array3[i];
        if (ht_search(ht, key) == NULL) {
            printf("%c not in array, failure\n", array3[i]);
            break;
        }
    }

    ht_delete_hash_table(ht);
}
