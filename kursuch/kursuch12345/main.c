#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <time.h>
#include <string.h>

int n;
int** graf = NULL;
int** inc = NULL;
int reb_count = 0;
int* matching = NULL;
int matching_size = 0;
int* available = NULL;
FILE* output_file = NULL;
char filename[256];

void free_graph() {
    if (graf) {
        for (int i = 0; i < n; i++) {
            if (graf[i]) free(graf[i]);
        }
        free(graf);
        graf = NULL;
    }
    if (inc) {
        for (int i = 0; i < n; i++) {
            if (inc[i]) free(inc[i]);
        }
        free(inc);
        inc = NULL;
    }
    if (matching) {
        free(matching);
        matching = NULL;
    }
    if (available) {
        free(available);
        available = NULL;
    }
    reb_count = 0;
    matching_size = 0;
}

void print_adjacency_matrix_console() {
    if (!graf) {
        printf("\nGraf eshche ne sozdan.\n");
        return;
    }
    printf("\nMatrica smezhnosti:\n");
    printf("     ");
    for (int i = 0; i < n; i++) printf("[%d] ", i + 1);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%3d ", graf[i][j]);
        }
        printf("\n");
    }
}

void print_adjacency_matrix_file() {
    if (!graf || !output_file) return;
    fprintf(output_file, "\nMATRICA SMEZHNOSTI:\n");
    fprintf(output_file, "   ");
    for (int i = 0; i < n; i++) fprintf(output_file, "%d ", i + 1);
    fprintf(output_file, "\n");
    for (int i = 0; i < n; i++) {
        fprintf(output_file, "%d  ", i + 1);
        for (int j = 0; j < n; j++) {
            fprintf(output_file, "%d ", graf[i][j]);
        }
        fprintf(output_file, "\n");
    }
}

void allocate_graph() {
    free_graph();
    graf = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        graf[i] = (int*)calloc(n, sizeof(int));
    }
}

void allocate_incidence() {
    inc = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        inc[i] = (int*)calloc(reb_count, sizeof(int));
    }
    available = (int*)calloc(reb_count, sizeof(int));
}

void build_incidence_matrix() {
    reb_count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (graf[i][j]) reb_count++;

    if (reb_count == 0) {
        printf("\nV grafe net reber.\n");
        return;
    }

    allocate_incidence();

    int edge_id = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graf[i][j]) {
                inc[i][edge_id] = 1;
                inc[j][edge_id] = 1;
                edge_id++;
            }
        }
    }
}

void print_incidence_matrix_console() {
    if (!inc) {
        printf("\nMatrica incidencii eshche ne postroena.\n");
        return;
    }
    printf("\nMatrica incidencii:\n");
    printf("    ");
    for (int i = 0; i < reb_count; i++) printf("[%d] ", i + 1);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("[%d]", i + 1);
        for (int j = 0; j < reb_count; j++) {
            printf("%3d ", inc[i][j]);
        }
        printf("\n");
    }
}

void print_incidence_matrix_file() {
    if (!inc || !output_file) return;
    fprintf(output_file, "\nMATRICA INCIDENCII:\n");
    fprintf(output_file, "   ");
    for (int i = 0; i < reb_count; i++) fprintf(output_file, "%d ", i + 1);
    fprintf(output_file, "\n");
    for (int i = 0; i < n; i++) {
        fprintf(output_file, "%d ", i + 1);
        for (int j = 0; j < reb_count; j++) {
            fprintf(output_file, "%d ", inc[i][j]);
        }
        fprintf(output_file, "\n");
    }
}

int edges_share_vertex(int edge1, int edge2) {
    for (int v = 0; v < n; v++) {
        if (inc[v][edge1] && inc[v][edge2]) return 1;
    }
    return 0;
}

void find_matching() {
    if (!inc || reb_count == 0) {
        printf("\nNet reber dlya poiska parosochetaniya.\n");
        return;
    }

    if (matching) free(matching);
    matching = (int*)calloc(reb_count, sizeof(int));

    for (int i = 0; i < reb_count; i++) available[i] = 1;
    matching_size = 0;

    for (int i = 0; i < reb_count; i++) {
        if (available[i]) {
            matching[matching_size++] = i;
            for (int j = i + 1; j < reb_count; j++) {
                if (available[j] && edges_share_vertex(i, j)) {
                    available[j] = 0;
                }
            }
        }
    }
}

void print_matching_console() {
    if (!matching) {
        printf("\nParosochetanie eshche ne naideno.\n");
        return;
    }
    printf("\nKolichestvo nezavisimykh reber = %d:\n", matching_size);
    for (int i = 0; i < matching_size; i++) {
        printf("Rebro %d ", matching[i] + 1);
    }
    printf("\n");
}

void print_result_file() {
    if (!output_file || !matching) return;
    fprintf(output_file, "\nREZULTAT:\n");
    fprintf(output_file, "Razmer parosochetaniya: %d\n", matching_size);
    fprintf(output_file, "Rebra: ");
    for (int i = 0; i < matching_size; i++) {
        fprintf(output_file, "%d ", matching[i] + 1);
    }
    fprintf(output_file, "\n");
}

void menu_avto() {
    printf("Razmer grafa n x n: ");
    while (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Nekorrektnyy razmer! Vvedite polozhitelnoe chislo: ");
        while (getchar() != '\n');
    }
    allocate_graph();
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            graf[i][j] = graf[j][i] = rand() % 2;
    if (output_file)
        fprintf(output_file, "\n--- Avtogen eraciya ---\n");
}

void menu_ruchnoy() {
    printf("Razmer grafa n x n: ");
    while (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Nekorrektnyy razmer! Vvedite polozhitelnoe chislo: ");
        while (getchar() != '\n');
    }
    allocate_graph();
    printf("Vvedite matricu smezhnosti (0/1):\n");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int val;
            do {
                printf("a[%d][%d] = ", i + 1, j + 1);
                if (scanf_s("%d", &val) != 1 || val < 0 || val > 1) {
                    printf("Oshibka! Vvedite TOLKO 0 ili 1: ");
                    val = 2;
                    while (getchar() != '\n');
                }
            } while (val < 0 || val > 1);
            graf[i][j] = graf[j][i] = val;
        }
    }
    if (output_file)
        fprintf(output_file, "\n--- Ruchnoy vvod ---\n");
}

int open_output_file() {
    while (1) {
        printf("Nazvanie fayla dlya rezultatov: ");
        scanf_s("%s", filename, (unsigned)_countof(filename));

        int has_cyrillic = 0;
        for (int i = 0; filename[i]; i++) {
            if (filename[i] >= 0xC0 && filename[i] <= 0xFF) {
                has_cyrillic = 1;
                break;
            }
        }

        if (has_cyrillic) {
            printf("Preduprezhdenie! Ispolzuyte latinskie");
            while (getchar() != '\n');
            continue;
        }

        errno_t err = fopen_s(&output_file, filename, "w");
        if (err == 0 && output_file) {
            return 1;
        }
        printf("Oshibka otkrytiya fayla! Poprobuyte drugoe imya: ");
        while (getchar() != '\n');
    }
    return 0;
}

void menu_naiti() {
    if (!graf) {
        printf("Snachala sozdaite graf (punkt 1 ili 2).\n");
        return;
    }

    print_adjacency_matrix_console();
    print_adjacency_matrix_file();

    build_incidence_matrix();
    if (reb_count == 0) {
        printf("\nV grafe net reber, nezavisimykh reber net.\n");
        return;
    }

    print_incidence_matrix_console();
    print_incidence_matrix_file();

    printf("\nAlgoritm: poisk maksimalnogo nezavisimogo mnozhestva reber\n");
    find_matching();
    print_matching_console();
    print_result_file();

    printf("\nRezultaty sokhranyeny v fayle: %s\n", filename);
}

int main() {
    setlocale(LC_ALL, "Russian");

    open_output_file();

    fprintf(output_file, "ALGORITM POISKA NEZAVISIMOGO MNOZHESTVA REBER\n");
    fprintf(output_file, "---------------------------------------------\n");

    printf("ALGORITM POISKA NEZAVISIMOGO MNOZHESTVA REBER\n");
    printf("---------------------------------------------\n");

    int choice;
    do {
        printf("\n--- MENYU ---\n");
        printf("1 - Avto generaciya\n");
        printf("2 - Ruchnoy vvod\n");
        printf("3 - Naiti nezavisimykh reber\n");
        printf("4 - Vykhod\n");
        printf("> ");

        if (scanf_s("%d", &choice) != 1) {
            printf("Nekorrektnyy vvod! Vvedite chislo.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            menu_avto();
            break;
        case 2:
            menu_ruchnoy();
            break;
        case 3:
            menu_naiti();
            break;
        case 4:
            printf("Vykhod\n");
            break;
        default:
            printf("Nekorrektnyy vybor! Vvedite 1-4.\n");
        }
    } while (choice != 4);

    free_graph();
    if (output_file) fclose(output_file);
    return 0;
}
