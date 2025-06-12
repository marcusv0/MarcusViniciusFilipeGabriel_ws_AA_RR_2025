#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
    RED,
    BLACK
} Color;

typedef struct Node
{
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node *createNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void rotateLeft(Node **root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node **root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixViolation(Node **root, Node *z)
{
    while (z != *root && z->parent->color == RED)
    {
        Node *gp = z->parent->parent;
        if (z->parent == gp->left)
        {
            Node *y = gp->right;
            if (y && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                rotateRight(root, gp);
            }
        }
        else
        {
            Node *y = gp->left;
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
    (*root)->color = BLACK;
}

void insert(Node **root, int key)
{
    Node *z = createNode(key);
    Node *y = NULL;
    Node *x = *root;

    while (x)
    {
        y = x;
        x = (z->key < x->key) ? x->left : x->right;
    }
    z->parent = y;
    if (!y)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    fixViolation(root, z);
}

// Função para liberar a árvore
void liberarArvore(Node *raiz)
{
    if (!raiz)
        return;
    liberarArvore(raiz->left);
    liberarArvore(raiz->right);
    free(raiz);
}

// Função de experimento com liberação
void testarInsercao(int n)
{
    Node *r = NULL;
    clock_t inicio = clock();
    for (int i = 0; i < n; i++)
    {
        insert(&r, rand() % (n * 10));
    }
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Inserção de %d elementos: %.5f segundos\n", n, tempo);
}

int main()
{
    srand(time(NULL));
    testarInsercao(1000000);
    testarInsercao(2000000);
    testarInsercao(3000000);
    testarInsercao(4000000);
    testarInsercao(5000000);
    testarInsercao(6000000);
    testarInsercao(7000000);
    testarInsercao(8000000);
    testarInsercao(9000000);
    testarInsercao(10000000);
    testarInsercao(11000000);
    testarInsercao(12000000);
    testarInsercao(13000000); // ou qualquer valor desejado

    return 0;
}
