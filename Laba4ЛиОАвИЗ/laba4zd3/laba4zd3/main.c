#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* r, int data, int limit, int depth)
{
    if (depth > limit) {
        printf("Превышен лимит глубины: %d\n", limit);
        return r;
    }

    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти\n");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        return r;
    }

    if (data == r->data)
    {
        printf("Значение %d уже в дереве, добавление пропущено\n", data);
        return r;
    }
    else if (data > r->data)
    {
        r->left = CreateTree(r->left, data, limit, depth + 1);
    }
    else
    {
        r->right = CreateTree(r->right, data, limit, depth + 1);
    }
    return r;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL)
        return;

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
        printf("    ");
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;

    root = NULL;

    printf("Введите максимальную глубину дерева: ");
    int limit;
    scanf("%d", &limit);

    while (start)
    {
        printf("Введите число: ");
        scanf("%d", &D);

        if (D == -1)
        {
            printf("Построение остановлено\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, D, limit, 1); 
    }

    print_tree(root, 0);

    return 0;
}
