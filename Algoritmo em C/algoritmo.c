#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enum para representar as cores dos nós (vermelho ou preto)
typedef enum
{
    RED,
    BLACK
} Color;

// Estrutura do nó da árvore Red-Black
typedef struct Node
{
    int key;                   // Chave do nó
    Color color;               // Cor do nó (RED ou BLACK)
    struct Node *left, *right; // Ponteiros para filhos esquerdo e direito
    struct Node *parent;       // Ponteiro para o nó pai
} Node;

// Função para criar um novo nó com chave dada
Node *createNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->color = RED; // Novos nós são sempre inseridos como vermelhos
    node->left = node->right = node->parent = NULL;
    return node;
}

// Rotação à esquerda em torno do nó x
void rotateLeft(Node **root, Node *x)
{
    Node *y = x->right; // y será promovido no lugar de x
    x->right = y->left; // Subárvore esquerda de y vira subárvore direita de x
    if (y->left)
        y->left->parent = x;

    y->parent = x->parent; // Liga y ao pai de x
    if (!x->parent)
        *root = y; // Se x era a raiz, y passa a ser a nova raiz
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x; // x vira filho esquerdo de y
    x->parent = y;
}

// Rotação à direita em torno do nó y
void rotateRight(Node **root, Node *y)
{
    Node *x = y->left;  // x será promovido no lugar de y
    y->left = x->right; // Subárvore direita de x vira subárvore esquerda de y
    if (x->right)
        x->right->parent = y;

    x->parent = y->parent; // Liga x ao pai de y
    if (!y->parent)
        *root = x; // Se y era a raiz, x passa a ser a nova raiz
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y; // y vira filho direito de x
    y->parent = x;
}

// Função para corrigir violações das propriedades da Red-Black Tree após inserção
void fixViolation(Node **root, Node *z)
{
    while (z != *root && z->parent->color == RED)
    {
        Node *gp = z->parent->parent; // Avô do nó z

        // Caso o pai de z seja filho esquerdo do avô
        if (z->parent == gp->left)
        {
            Node *y = gp->right; // Tio de z
            // Caso 1: tio é vermelho (recoloração)
            if (y && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp; // Sobe para continuar checando violações
            }
            else
            {
                // Caso 2: z é filho direito → rotação esquerda
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                // Caso 3: z é filho esquerdo → rotação direita no avô
                z->parent->color = BLACK;
                gp->color = RED;
                rotateRight(root, gp);
            }
        }
        else // Caso espelhado: pai de z é filho direito do avô
        {
            Node *y = gp->left; // Tio de z
            if (y && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                rotateLeft(root, gp);
            }
        }
    }
    (*root)->color = BLACK; // Garante que a raiz sempre será preta
}

// Função principal de inserção na árvore Red-Black
void insert(Node **root, int key)
{
    Node *z = createNode(key); // Cria novo nó
    Node *y = NULL;
    Node *x = *root;

    // Busca posição correta na árvore binária de busca (BST)
    while (x)
    {
        y = x;
        x = (z->key < x->key) ? x->left : x->right;
    }

    z->parent = y; // Define o pai do novo nó
    if (!y)
        *root = z; // Caso a árvore esteja vazia
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    fixViolation(root, z); // Corrige possíveis violações da RB Tree
}

// Libera todos os nós da árvore (evita vazamento de memória)
void liberarArvore(Node *raiz)
{
    if (!raiz)
        return;
    liberarArvore(raiz->left);
    liberarArvore(raiz->right);
    free(raiz);
}

// Realiza experimento de tempo de inserção de n elementos
void testarInsercao(int n)
{
    Node *r = NULL;
    clock_t inicio = clock(); // Marca o tempo de início

    for (int i = 0; i < n; i++)
    {
        insert(&r, rand() % (n * 10)); // Insere números aleatórios
    }

    clock_t fim = clock(); // Marca o tempo de fim
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Inserção de %d elementos: %.5f segundos\n", n, tempo);

    liberarArvore(r); // Libera memória após o teste
}

// Função principal
int main()
{
    srand(time(NULL));        // Inicializa gerador de números aleatórios
    testarInsercao(13000000); // Chama a função testaInsercao com uma entrada de elementos

    return 0;
}
