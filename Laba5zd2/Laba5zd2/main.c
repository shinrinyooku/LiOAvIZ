#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_adjacency_matrix(int n, int** matrix) {
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            matrix[i][j] = matrix[j][i] = (i != j) ? rand() % 2 : 0;
}

int build_edge_list(int n, int** matrix, int (*edges)[2]) {
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (matrix[i][j])
                edges[k][0] = i, edges[k++][1] = j;
    return k;
}

void build_incidence_matrix(int n, int m, int (*edges)[2], int** inc_matrix) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            inc_matrix[i][j] = (edges[j][0] == i || edges[j][1] == i) ? 1 : 0;
}

void print_incidence_matrix(int n, int m, int** inc_matrix) {
    printf("Intsidentnosti matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", inc_matrix[i][j]);
        printf("\n");
    }
}

int graph_size_by_inc(int m) {
    return m;
}

void analyze_vertices_inc(int n, int m, int** inc_matrix) {
    printf("Isolated vershini: ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < m; j++) deg += inc_matrix[i][j];
        if (deg == 0) { printf("%d ", i + 1); found = 1; }
    }
    if (!found) printf("no");
    printf("\n");

    printf("Konechnie vershini: ");
    found = 0;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < m; j++) deg += inc_matrix[i][j];
        if (deg == 1) { printf("%d ", i + 1); found = 1; }
    }
    if (!found) printf("net");
    printf("\n");

    printf("Dominating vershini: ");
    found = 0;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < m; j++) deg += inc_matrix[i][j];
        if (deg == n - 1) { printf("%d ", i + 1); found = 1; }
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
        matrix[i] = calloc(n, sizeof(int));

    srand(time(NULL));
    generate_adjacency_matrix(n, matrix);

    int max_edges = n * (n - 1) / 2;
    int (*edges)[2] = malloc(max_edges * sizeof(int[2]));
    int m = build_edge_list(n, matrix, edges);

    int** inc_matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        inc_matrix[i] = calloc(m, sizeof(int));
    build_incidence_matrix(n, m, edges, inc_matrix);

    print_incidence_matrix(n, m, inc_matrix);
    printf("Size of graph (chislo reber): %d\n", graph_size_by_inc(m));
    analyze_vertices_inc(n, m, inc_matrix);

    for (int i = 0; i < n; i++) { free(matrix[i]); free(inc_matrix[i]); }
    free(matrix); free(inc_matrix); free(edges);

    return 0;
}
