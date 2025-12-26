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

int count_occurrences(struct Node* root, int target) {
    if (root == NULL)
        return 0;

    int count = 0;

    if (root->data == target)
        count++;

    count += count_occurrences(root->left, target);
    count += count_occurrences(root->right, target);

    return count;
}

struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Error videl pam\n");
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

struct Node* search_tree(struct Node* root, int target) {
    if (root == NULL)
        return NULL;

    if (root->data == target)
        return root;

    if (target > root->data)
        return search_tree(root->left, target);
    else
        return search_tree(root->right, target);
}

void print_tree(struct Node* r, int l) {
    if (r == NULL)
        return;

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
        printf("    ");
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "");
    int D, start = 1;

    root = NULL;
    printf("-1 - stop postroenia\n");
    while (start) {
        printf("Enter chislo: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Postroenie stopped\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, root, D);
    }

    print_tree(root, 0);

    printf("Enter chislo for poisk: ");
    scanf("%d", &D);

    int count = count_occurrences(root, D);

    if (count > 0)
        printf("Znach %d found in derevo %d times.\n", D, count);
    else
        printf("Znach %d ne found in derevo.\n", D);

    return 0;
}
