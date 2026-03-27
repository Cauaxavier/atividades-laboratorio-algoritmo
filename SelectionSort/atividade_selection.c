#include <stdio.h>

void selectionSort(int v[], int n, int ordem, int *comparacoes, int *trocas)
{
    if (ordem != 1 && ordem != -1)
    {
        return;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int escolhido = i;

        for (int j = i + 1; j < n; j++)
        {
            (*comparacoes)++;
            if ((ordem == 1 && v[j] < v[escolhido]) ||
                (ordem == -1 && v[j] > v[escolhido]))
            {
                escolhido = j;
            }
        }

        if (escolhido != i)
        {
            int temp = v[i];
            v[i] = v[escolhido];
            v[escolhido] = temp;
            (*trocas)++;
        }
    }
}

void bubbleSort(int v[], int n, int ordem, int *comparacoes, int *trocas)
{
    if (ordem != 1 && ordem != -1)
    {
        return;
    }

    int trocou;

    for (int i = 0; i < n - 1; i++)
    {
        trocou = 0;

        for (int j = 0; j < n - 1 - i; j++)
        {
            (*comparacoes)++;

            if ((ordem == 1 && v[j] > v[j + 1]) ||
                (ordem == -1 && v[j] < v[j + 1]))
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                (*trocas)++;
                trocou = 1;
            }
        }

        if (!trocou)
        {
            break;
        }
    }
}

void copiarVetor(int origem[], int destino[], int n)
{
    for (int i = 0; i < n; i++)
    {
        destino[i] = origem[i];
    }
}

void testarCaso(char nome[], int v[], int n, int ordem)
{
    int vSel[100], vBub[100];
    int compSel = 0, trocSel = 0;
    int compBub = 0, trocBub = 0;

    copiarVetor(v, vSel, n);
    copiarVetor(v, vBub, n);

    selectionSort(vSel, n, ordem, &compSel, &trocSel);
    bubbleSort(vBub, n, ordem, &compBub, &trocBub);

    printf("%-15s | Sel Comp: %-3d Trocas: %-3d | Bub Comp: %-3d Trocas: %-3d\n",
           nome, compSel, trocSel, compBub, trocBub);
}

int main()
{

    // int vazio[] = {};
    int um[] = {7};
    int ordenado[] = {1, 2, 3, 4, 5};
    int inverso[] = {5, 4, 3, 2, 1};
    int repetidos[] = {3, 1, 3, 2, 3};

    printf("ORDEM CRESCENTE (ordem = 1)\n");
    printf("CASO            | SELECTION                 | BUBBLE (early stop)\n");
    printf("-------------------------------------------------------------------\n");

    testarCaso("Vazio", NULL, 0, 1);
    testarCaso("1 elemento", um, 1, 1);
    testarCaso("Ordenado", ordenado, 5, 1);
    testarCaso("Inverso", inverso, 5, 1);
    testarCaso("Repetidos", repetidos, 5, 1);

    printf("\n crescente: Selection tende a fazer menos trocas; ");
    printf("mais comparacoes ficam mais evidentes no caso ordenado (Bubble para cedo).\n\n");

    printf("ORDEM DECRESCENTE (ordem = -1)\n");
    printf("CASO            | SELECTION                 | BUBBLE (early stop)\n");
    printf("-------------------------------------------------------------------\n");

    testarCaso("Vazio", NULL, 0, -1);
    testarCaso("1 elemento", um, 1, -1);
    testarCaso("Ordenado", ordenado, 5, -1);
    testarCaso("Inverso", inverso, 5, -1);
    testarCaso("Repetidos", repetidos, 5, -1);

    printf("\n decrescente: Selection continua com menos trocas na maioria dos casos; ");
    printf("mais comparacoes aparecem quando Bubble consegue early stop no vetor ja alinhado com a ordem.\n");

    return 0;
}