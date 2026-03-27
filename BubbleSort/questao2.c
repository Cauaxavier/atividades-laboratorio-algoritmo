#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define N 20

void bubbleSortSimples(int v[], int n, int *comparacoes, int *trocas) {
    int i, j, temp;
    *comparacoes = 0;
    *trocas = 0;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                (*trocas)++;
            }
        }
    }
}

void bubbleSortEarlyStop(int v[], int n, int *comparacoes, int *trocas) {
    int i, j, temp;
    bool trocou;
    *comparacoes = 0;
    *trocas = 0;

    for (i = 0; i < n - 1; i++) {
        trocou = false;

        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                (*trocas)++;
                trocou = true;
            }
        }

        if (trocou == false) {
            break; // early stop
        }
    }
}

void copiarVetor(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

void imprimirMetricas(char *titulo, int comparacoes, int trocas) {
    printf("%s\n", titulo);
    printf("Comparacoes: %d\n", comparacoes);
    printf("Trocas: %d\n\n", trocas);
}

int main() {
    int ordenado[N], reverso[N], aleatorio[N], v[N];
    int comparacoes, trocas;

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        ordenado[i] = i;
    }

    for (int i = 0; i < N; i++) {
        reverso[i] = N - i;
    }

    for (int i = 0; i < N; i++) {
        aleatorio[i] = rand() % 100;
    }

    copiarVetor(ordenado, v, N);
    bubbleSortSimples(v, N, &comparacoes, &trocas);
    imprimirMetricas("Bubble Sort Simples - Ordenado", comparacoes, trocas);

    copiarVetor(reverso, v, N);
    bubbleSortSimples(v, N, &comparacoes, &trocas);
    imprimirMetricas("Bubble Sort Simples - Reverso", comparacoes, trocas);

    copiarVetor(aleatorio, v, N);
    bubbleSortSimples(v, N, &comparacoes, &trocas);
    imprimirMetricas("Bubble Sort Simples - Aleatorio", comparacoes, trocas);

    copiarVetor(ordenado, v, N);
    bubbleSortEarlyStop(v, N, &comparacoes, &trocas);
    imprimirMetricas("Bubble Sort Early Stop - Ordenado", comparacoes, trocas);

    copiarVetor(reverso, v, N);
    bubbleSortEarlyStop(v, N, &comparacoes, &trocas);
    imprimirMetricas("Bubble Sort Early Stop - Reverso", comparacoes, trocas);

    copiarVetor(aleatorio, v, N);
    bubbleSortEarlyStop(v, N, &comparacoes, &trocas);
    imprimirMetricas("Bubble Sort Early Stop - Aleatorio", comparacoes, trocas);

    // Mais operações: vetor reverso, em ambas as versões

    // Menos operações: vetor ordenado, usando early stop

    // O Bubble Sort sem otimização faz sempre o mesmo número de comparações, mesmo se o vetor já estiver ordenado.

    // O early stop reduz drasticamente comparações no melhor case, mas não melhora o pior case (continua O(n²)).

    return 0;
}

