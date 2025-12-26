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

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("error videl\n");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;

        if (root == NULL) return r;

        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL)
    {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
    {
        printf("    ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

int count_occurrences(struct Node* r, int value)
{
    if (r == NULL)
        return 0;

    int count = 0;
    if (r->data == value)
        count = 1;

    return count + count_occurrences(r->left, value) + count_occurrences(r->right, value);
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;

    root = NULL;
    printf("-1 - stop postroenia\n");
    while (start)
    {
        printf("Enter chislo: ");
        scanf("%d", &D);
        if (D == -1)
        {
            printf("Postroenie stopped\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, root, D);
    }

    print_tree(root, 0);

    printf("Enter chislo for poisk povtoreniy: ");
    scanf("%d", &D);
    int occurrences = count_occurrences(root, D);
    printf("Count of fhozhdeniy is %d: %d\n", D, occurrences);

    return 0;
}
