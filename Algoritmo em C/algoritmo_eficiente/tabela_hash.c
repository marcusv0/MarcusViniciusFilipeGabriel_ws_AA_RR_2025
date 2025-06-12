#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define o tamanho da tabela hash como um número primo grande (boa prática para reduzir colisões)
#define TABLE_SIZE 100003

// Estrutura de nó da lista encadeada usada para tratar colisões (encadeamento separado)
typedef struct Node
{
    int key;           // Chave armazenada
    struct Node *next; // Ponteiro para o próximo nó na mesma "bucket" (lista encadeada)
} Node;

// Estrutura da tabela hash com um vetor de ponteiros para listas encadeadas
typedef struct
{
    Node *buckets[TABLE_SIZE]; // Vetor de buckets (listas) da hash table
} HashTable;

// Função de dispersão (hash function): calcula o índice a partir da chave
unsigned int hash_function(int key)
{
    return (unsigned int)(key % TABLE_SIZE); // Usa módulo do tamanho da tabela
}

// Inicializa todos os buckets da hash table com NULL
void hash_init(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL; // Nenhuma chave inserida inicialmente
}

// Insere uma chave na tabela hash com tratamento de colisão por encadeamento separado
void hash_insert(HashTable *ht, int key)
{
    unsigned int idx = hash_function(key);         // Calcula o índice da tabela
    Node *new_node = (Node *)malloc(sizeof(Node)); // Cria novo nó
    new_node->key = key;                           // Atribui a chave
    new_node->next = ht->buckets[idx];             // Aponta para o primeiro nó já presente no bucket (pode ser NULL)
    ht->buckets[idx] = new_node;                   // Atualiza o bucket para apontar para o novo nó
}

// Função principal que realiza o experimento
int main()
{
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    // Testa inserção em tamanhos crescentes: de 1 milhão até 13 milhões de elementos
    for (int i = 1; i <= 13; i++)
    {
        int total = i * 1000000; // Quantidade de chaves para inserir

        HashTable ht;   // Declara a tabela hash
        hash_init(&ht); // Inicializa todos os buckets com NULL

        clock_t inicio = clock(); // Marca tempo inicial

        // Insere 'total' elementos aleatórios na tabela hash
        for (int j = 0; j < total; j++)
        {
            hash_insert(&ht, rand() % (total * 10)); // Gera chave aleatória proporcional ao volume de dados
        }

        clock_t fim = clock(); // Marca tempo final

        // Calcula e imprime o tempo de execução
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Inserção de %d elementos: %.5f segundos\n", total, tempo);
    }

    return 0;
}
