#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100003

typedef struct Node
{
    int key;
    struct Node *next;
} Node;

typedef struct
{
    Node *buckets[TABLE_SIZE];
} HashTable;

unsigned int hash_function(int key)
{
    return (unsigned int)(key % TABLE_SIZE);
}

void hash_init(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL;
}

void hash_insert(HashTable *ht, int key)
{
    unsigned int idx = hash_function(key);
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = key;
    new_node->next = ht->buckets[idx];
    ht->buckets[idx] = new_node;
}

int main()
{
    srand(time(NULL));

    for (int i = 1; i <= 13; i++)
    {
        int total = i * 1000000;

        HashTable ht;
        hash_init(&ht);

        clock_t inicio = clock();
        for (int j = 0; j < total; j++)
        {
            hash_insert(&ht, rand() % (total * 10));
        }
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Inserção de %d elementos: %.5f segundos\n", total, tempo);
    }

    return 0;
}
