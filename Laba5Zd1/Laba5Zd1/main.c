#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_adjacency_matrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int r = rand() % 2;
            matrix[i][j] = matrix[j][i] = r;
            
        }
    }
}

void print_matrix(int n, int** matrix) {
    printf("Matr smezh:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int graph_size(int n, int** matrix) {
    int edges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j]) edges++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (matrix[i][i]) edges++;
    }
    return edges;
}


void analyze_vertices(int n, int** matrix) {
    printf("Isolated vershini: ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            if (i == j)
                degree += 2 * matrix[i][j]; 
            else
                degree += matrix[i][j];
        }
        if (degree == 0) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("no");
    printf("\n");

    printf("Konechnie vershini: ");
    found = 0;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            if (i == j)
                degree += 2 * matrix[i][j];
            else
                degree += matrix[i][j];
        }
        if (degree == 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("net");
    printf("\n");

    printf("Dominating vershini: ");
    found = 0;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            if (i == j)
                degree += 2 * matrix[i][j];
            else
                degree += matrix[i][j];
        }
        if (degree == n - 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("no");
    printf("\n");
}


int main() {
    int n;
    printf("Enter kolvo vershin of graph: ");
    scanf("%d", &n);

    int** matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matrix[i] = malloc(n * sizeof(int));

    srand(time(NULL));
    generate_adjacency_matrix(n, matrix);
    print_matrix(n, matrix);
    printf("Size of graph (chislo reber): %d\n", graph_size(n, matrix));
    analyze_vertices(n, matrix);

    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);

    return 0;
}
 