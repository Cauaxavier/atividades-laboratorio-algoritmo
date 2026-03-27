#include <stdio.h>

void bubbleSortOrdem(int v[], int n, int ordem) {
	if (ordem != 1 && ordem != -1) {
		return;
	}

	for (int i = 0; i < n - 1; i++) {
		int trocou = 0;

		for (int j = 0; j < n - i - 1; j++) {
			int precisaTrocar = (ordem == 1) ? (v[j] > v[j + 1]) : (v[j] < v[j + 1]);

			if (precisaTrocar) {
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
				trocou = 1;
			}
		}

		if (!trocou) {
			break;
		}
	}
}

void copiarVetor(const int origem[], int destino[], int n) {
	for (int i = 0; i < n; i++) {
		destino[i] = origem[i];
	}
}

void imprimirVetor(const int v[], int n) {
	printf("[");
	for (int i = 0; i < n; i++) {
		printf("%d", v[i]);
		if (i < n - 1) {
			printf(", ");
		}
	}
	printf("]\n");
}

void executarCaso(const char *nomeCaso, const int entrada[], int n) {
	int crescente[20];
	int decrescente[20];

	copiarVetor(entrada, crescente, n);
	copiarVetor(entrada, decrescente, n);

	bubbleSortOrdem(crescente, n, 1);
	bubbleSortOrdem(decrescente, n, -1);

	printf("%s (n=%d)\n", nomeCaso, n);
	printf("Entrada:      ");
	imprimirVetor(entrada, n);
	printf("Crescente:    ");
	imprimirVetor(crescente, n);
	printf("Decrescente:  ");
	imprimirVetor(decrescente, n);
	printf("\n");
}

int main() {
	int vazio[1] = {0};
	int unico[] = {42};
	int repetidos[] = {5, 5, 2, 2, 9, 9, 2};
	int misto[] = {3, -1, 0, -8, 7, -3, 2};

	executarCaso("Vetor vazio", vazio, 0);
	executarCaso("Um elemento", unico, 1);
	executarCaso("Elementos repetidos", repetidos, 7);
	executarCaso("Positivos e negativos", misto, 7);

	return 0;
}
