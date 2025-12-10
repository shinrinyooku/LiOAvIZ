#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
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

void BFSD(int** G, int numG, int** GD, int s) {
    queue<int> q;
    int v;
    int* dist = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {

        dist[i] = INT_MAX;

    }


    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {

        v = q.front();
        q.pop();
        //printf("%3d", v);

        for (int i = 0; i < numG; i++) {
            if (G[v][i] > 0 && dist[i] > dist[v] + G[v][i]) {
                q.push(i);
                dist[i] = dist[v] + G[v][i];
            }

        }
    }
    for (int i = 0; i < numG; i++) {

        GD[s][i] = (dist[i] == INT_MAX ? -1 : dist[i]);

    }


    //printf("\n\nDist from %d to: ", s);
    //for (int i = 0; i < numG; i++) {
        //printf("\n%3d : %3d", i, dist[i]);
    //}
    free(dist);
}

void printM(int** Matr, int numG) {
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", Matr[i][j]);

        }
        printf("\n");
    }


}


int main() {
    int** G;
    int** GD;
    int* ecc;
    int numG, current;

    printf("Input number of vershini: ");
    scanf("%d", &numG);

    ecc = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    GD = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
        GD[i] = (int*)malloc(numG * sizeof(int));
    }

    srand(time(NULL));

    for (int i = 0; i < numG; i++) {
        ecc[i] = 0;
        for (int j = i; j < numG; j++) {
            G[i][j] = G[j][i] = (i == j ? 0 : (rand() % 2) ? rand() % 11 : 0);
        }
    }

    printM(G, numG);



    for (int i = 0; i < numG; i++) {
        BFSD(G, numG, GD, i);
    }
    printf("\n");

    printf("Matritsa rastoyaniya: \n");
    printM(GD, numG);



    printf("\n");


    printf("Vector ecc: \n");

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {

            ecc[i] = (ecc[i] < GD[i][j] ? GD[i][j] : ecc[i]);

        }
        printf("%4d", ecc[i]);
    }
    printf("\n");


    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 0; i < numG; i++) {
        if (ecc[i] < radius)
            radius = ecc[i];
        if (ecc[i] > diameter)
            diameter = ecc[i];
    }

    printf("Radius (min ecc) = %d\n", radius);
    printf("Diameter (max ecc) = %d\n", diameter);

    printf("Central vershini (ecc == radius): ");
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == radius) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Periferiinye vershini (ecc == diameter): ");
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == diameter) {
            printf("%d ", i);
        }
    }
    printf("\n");


    free(ecc);
    for (int i = 0; i < numG; i++)
        free(G[i]);
    free(G);

    getchar();
    getchar();

    return 0;

}
