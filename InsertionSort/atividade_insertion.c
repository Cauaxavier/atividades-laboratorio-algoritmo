#include <stdio.h>

typedef struct
{
    long comparacoes;
    long movimentacoes;
} Metrics;

void imprimeVetor(int *V, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", V[i]);
        if (i < n - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}

void copiarVetor(const int *origem, int *destino, int n)
{
    for (int i = 0; i < n; i++)
    {
        destino[i] = origem[i];
    }
}

void insertionSortOrdem(int *V, int n, int ordem)
{
    for (int i = 1; i < n; i++)
    {
        int chave = V[i];
        int j = i;

        while (j > 0 && ((ordem == 1) ? (chave < V[j - 1]) : (chave > V[j - 1])))
        {
            V[j] = V[j - 1];
            j--;
        }

        V[j] = chave;
    }
}

void insertionSort(int *V, int n)
{
    insertionSortOrdem(V, n, 1);
}

void insertionSortDecrescente(int *V, int n)
{
    insertionSortOrdem(V, n, -1);
}

void insertionSortComPassos(int *V, int n)
{
    for (int i = 1; i < n; i++)
    {
        int chave = V[i];
        int j = i;

        printf("i=%d, chave=%d | antes: ", i, chave);
        imprimeVetor(V, n);

        while (j > 0 && chave < V[j - 1])
        {
            V[j] = V[j - 1];
            j--;
        }
        V[j] = chave;

        printf("i=%d, chave=%d | depois: ", i, chave);
        imprimeVetor(V, n);
    }
}

void insertionSortMetricsOrdem(int *v, int n, Metrics *m, int ordem)
{
    m->comparacoes = 0;
    m->movimentacoes = 0;

    for (int i = 1; i < n; i++)
    {
        int chave = v[i];
        int j = i;

        while (j > 0)
        {
            m->comparacoes++;
            if ((ordem == 1 && chave < v[j - 1]) || (ordem == -1 && chave > v[j - 1]))
            {
                v[j] = v[j - 1];
                m->movimentacoes++;
                j--;
            }
            else
            {
                break;
            }
        }

        v[j] = chave;
        m->movimentacoes++;
    }
}

void insertionSortMetrics(int *v, int n, Metrics *m)
{
    insertionSortMetricsOrdem(v, n, m, 1);
}

void imprimeCasoAntesDepois(const char *nome, const int *base, int n, int decrescente)
{
    int copia[64];

    copiarVetor(base, copia, n);

    printf("%s\n", nome);
    printf("Antes: ");
    imprimeVetor(copia, n);

    if (decrescente)
    {
        insertionSortDecrescente(copia, n);
    }
    else
    {
        insertionSort(copia, n);
    }

    printf("Depois: ");
    imprimeVetor(copia, n);
    printf("\n");
}

void imprimeTabelaMetricas(const int *A, const int *B, const int *C, int n, int ordem)
{
    int vA[64], vB[64], vC[64];
    Metrics mA, mB, mC;

    copiarVetor(A, vA, n);
    copiarVetor(B, vB, n);
    copiarVetor(C, vC, n);

    insertionSortMetricsOrdem(vA, n, &mA, ordem);
    insertionSortMetricsOrdem(vB, n, &mB, ordem);
    insertionSortMetricsOrdem(vC, n, &mC, ordem);

    printf("Tabela de metricas (%s)\n", ordem == 1 ? "crescente" : "decrescente");
    printf("Caso A (aleatorio): comparacoes=%ld, movimentacoes=%ld\n", mA.comparacoes, mA.movimentacoes);
    printf("Caso B (ordenado): comparacoes=%ld, movimentacoes=%ld\n", mB.comparacoes, mB.movimentacoes);
    printf("Caso C (invertido): comparacoes=%ld, movimentacoes=%ld\n", mC.comparacoes, mC.movimentacoes);
    printf("\n");
}

int main(void)
{
    int A[] = {5, 2, 4, 6, 1, 3};
    int B[] = {1, 2, 3, 4, 5, 6};
    int C[] = {6, 5, 4, 3, 2, 1};
    int n = (int)(sizeof(A) / sizeof(A[0]));

    printf("Antes e depois - ordem crescente\n\n");
    imprimeCasoAntesDepois("Caso A", A, n, 0);
    imprimeCasoAntesDepois("Caso B", B, n, 0);
    imprimeCasoAntesDepois("Caso C", C, n, 0);

    printf("Passo a passo (vetor A = {5, 2, 4, 6, 1, 3})\n");
    int passoA[64];
    copiarVetor(A, passoA, n);
    insertionSortComPassos(passoA, n);
    printf("\n");

    imprimeTabelaMetricas(A, B, C, n, 1);

    printf("Antes e depois - ordem decrescente\n\n");
    imprimeCasoAntesDepois("Caso A", A, n, 1);
    imprimeCasoAntesDepois("Caso B", B, n, 1);
    imprimeCasoAntesDepois("Caso C", C, n, 1);

    imprimeTabelaMetricas(A, B, C, n, -1);

    return 0;
}
