#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

using namespace std;

void DFS(int** G, int numG, int* dist, int current) {
    dist[current] = 1;
    printf("%3d", current);

    for (int i = 0; i < numG; i++) {
        if (G[current][i] == 1 && dist[i] == 0) {
            DFS(G, numG, dist, i);
        }

    }
}

void BFSD(int** G, int numG, int* dist, int s) {
    queue<int> q;
    int v;

    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {

        v = q.front();
        q.pop();
        printf("%3d", v);

        for (int i = 0; i < numG; i++) {
            if (G[v][i] == 1 && dist[i] == -1) {
                q.push(i);
                dist[i] = dist[v] + 1;
            }

        }
    }

    printf("\n\nDist from %d to: ", s);
    for (int i = 0; i < numG; i++) {
        printf("\n%3d : %3d", i, dist[i]);
    }
}

int main() {
    int** G;
    int* dist;
    int numG, current;

    printf("Input number of vershini: ");
    scanf("%d", &numG);

    dist = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++)
        G[i] = (int*)malloc(numG * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < numG; i++) {
        dist[i] = -1;
        for (int j = i; j < numG; j++) {
            G[i][j] = G[j][i] = (i == j ? 0 : rand() % 2);

        }
    }

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);

        }
        printf("\n");
    }

    printf("input start vershinka: ");
    scanf("%d", &current);

    printf("\nPath: ");
    BFSD(G, numG, dist, current);
    printf("\n\n");

    free(dist);
    for (int i = 0; i < numG; i++)
        free(G[i]);
    free(G);

    return 0;

}