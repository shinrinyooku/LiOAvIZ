#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


void DFS(int** G, int numG, int* visited, int current) {
	visited[current] = 1;
	printf("%3d", current);

	for (int i = 0; i < numG; i++) {
		if (G[current][i] == 1 && visited[i] == 0) {
			DFS(G, numG, visited, i);
		}
	}
}


int main() {
	int** G;
	int numG, current;
	int* visited;

	printf("Input number of vershini: ");
	scanf("%d", &numG);
	visited = (int*)malloc(numG * sizeof(int));
	G = (int**)malloc(numG * sizeof(int*));
	for (int i = 0; i < numG; i++)
		G[i] = (int*)malloc(numG * sizeof(int));
	
	srand(time(NULL));

	for (int i = 0; i < numG; i++) {
		visited[i] = 0;
		for (int j = i; j < numG; j++) {
			G[i][j] = G[j][i] =  (i == j ? 0 : rand() % 2);

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


	printf("Path: ");
	DFS(G, numG, visited, current);
	free(visited);
	for (int i = 0; i < numG; i++)
		free(G[i]);
	free(G);

	return 0;

}