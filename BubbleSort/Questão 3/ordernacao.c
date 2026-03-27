#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME 100
#define MAX_LINHA 256

void bubble_sort_float_desc(float vetor[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (vetor[j] < vetor[j + 1])
            {
                float temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou)
        {
            break;
        }
    }
}

void bubble_sort_nomes_asc(char nomes[][MAX_NOME], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(nomes[j], nomes[j + 1]) > 0)
            {
                char temp[MAX_NOME];
                strcpy(temp, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], temp);
                trocou = 1;
            }
        }
        if (!trocou)
        {
            break;
        }
    }
}

void remover_quebra_linha(char texto[])
{
    size_t tam = strlen(texto);
    if (tam > 0 && texto[tam - 1] == '\n')
    {
        texto[tam - 1] = '\0';
    }
}

char *trim(char *texto)
{
    while (*texto && isspace((unsigned char)*texto))
    {
        texto++;
    }

    if (*texto == '\0')
    {
        return texto;
    }

    char *fim = texto + strlen(texto) - 1;
    while (fim > texto && isspace((unsigned char)*fim))
    {
        *fim = '\0';
        fim--;
    }

    return texto;
}

FILE *abrir_csv(void)
{
    const char *caminhos[] = {"alunos.csv", "../alunos.csv", "..\\alunos.csv"};
    const int total_caminhos = (int)(sizeof(caminhos) / sizeof(caminhos[0]));

    for (int i = 0; i < total_caminhos; i++)
    {
        FILE *arquivo = fopen(caminhos[i], "r");
        if (arquivo != NULL)
        {
            return arquivo;
        }
    }

    return NULL;
}

int carregar_alunos_csv(char (**nomes)[MAX_NOME], float **notas, int *quantidade)
{
    FILE *arquivo = abrir_csv();
    if (arquivo == NULL)
    {
        return 0;
    }

    int capacidade = 10;
    int qtd = 0;
    *nomes = malloc(capacidade * sizeof(**nomes));
    *notas = malloc(capacidade * sizeof(**notas));

    if (*nomes == NULL || *notas == NULL)
    {
        fclose(arquivo);
        free(*nomes);
        free(*notas);
        return 0;
    }

    char linha[MAX_LINHA];

    if (fgets(linha, sizeof(linha), arquivo) == NULL)
    {
        fclose(arquivo);
        free(*nomes);
        free(*notas);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        remover_quebra_linha(linha);
        if (linha[0] == '\0')
        {
            continue;
        }

        char *virgula = strchr(linha, ',');
        if (virgula == NULL)
        {
            continue;
        }

        *virgula = '\0';
        char *nome = trim(linha);
        char *nota_txt = trim(virgula + 1);

        char *fim_nota;
        float nota = strtof(nota_txt, &fim_nota);
        if (fim_nota == nota_txt)
        {
            continue;
        }

        if (qtd == capacidade)
        {
            int nova_capacidade = capacidade * 2;
            char (*novos_nomes)[MAX_NOME] = realloc(*nomes, nova_capacidade * sizeof(**nomes));
            float *novas_notas = realloc(*notas, nova_capacidade * sizeof(**notas));

            if (novos_nomes == NULL || novas_notas == NULL)
            {
                free(novos_nomes);
                free(novas_notas);
                fclose(arquivo);
                free(*nomes);
                free(*notas);
                return 0;
            }

            *nomes = novos_nomes;
            *notas = novas_notas;
            capacidade = nova_capacidade;
        }

        strncpy((*nomes)[qtd], nome, MAX_NOME - 1);
        (*nomes)[qtd][MAX_NOME - 1] = '\0';
        (*notas)[qtd] = nota;
        qtd++;
    }

    fclose(arquivo);

    if (qtd == 0)
    {
        free(*nomes);
        free(*notas);
        return 0;
    }

    *quantidade = qtd;
    return 1;
}

int main()
{
    char (*nomes)[MAX_NOME] = NULL;
    float *notas = NULL;
    int quantidade = 0;

    if (!carregar_alunos_csv(&nomes, &notas, &quantidade))
    {
        printf("Erro ao ler 'alunos.csv'. Verifique se o arquivo existe e esta no formato nome,nota.\n");
        return 1;
    }

    float *notas_ordenadas = malloc(quantidade * sizeof(float));
    char (*nomes_ordenados)[MAX_NOME] = malloc(quantidade * sizeof(*nomes_ordenados));

    if (notas_ordenadas == NULL || nomes_ordenados == NULL)
    {
        printf("Erro de memoria durante o processamento.\n");
        free(nomes);
        free(notas);
        free(notas_ordenadas);
        free(nomes_ordenados);
        return 1;
    }

    float soma = 0.0f;
    for (int i = 0; i < quantidade; i++)
    {
        notas_ordenadas[i] = notas[i];
        strcpy(nomes_ordenados[i], nomes[i]);
        soma += notas[i];
    }

    printf("Dados carregados de alunos.csv: %d alunos\n\n", quantidade);

    printf("A) Ordenar notas (float), mostrar top-3 e media\n");
    bubble_sort_float_desc(notas_ordenadas, quantidade);

    printf("Notas ordenadas (maior para menor):\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("%.2f ", notas_ordenadas[i]);
    }

    int top = (quantidade < 3) ? quantidade : 3;
    printf("\nTop-%d:\n", top);
    for (int i = 0; i < top; i++)
    {
        printf("%do: %.2f\n", i + 1, notas_ordenadas[i]);
    }

    printf("Media: %.2f\n\n", soma / quantidade);

    printf("B) Ordenar nomes (strings) em ordem alfabetica usando strcmp (Bubble adaptado)\n");
    bubble_sort_nomes_asc(nomes_ordenados, quantidade);

    printf("Nomes em ordem alfabetica:\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("%s\n", nomes_ordenados[i]);
    }

    free(nomes_ordenados);
    free(notas_ordenadas);
    free(nomes);
    free(notas);

    return 0;
}