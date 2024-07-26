#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

// Função para trocar dois elementos
void troca(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para calcular a mediana de três
int medianaDeTres(int* vetor, int esquerda, int direita) {
    int meio = (esquerda + direita) / 2;
    if (vetor[esquerda] > vetor[meio])
        troca(&vetor[esquerda], &vetor[meio]);
    if (vetor[esquerda] > vetor[direita])
        troca(&vetor[esquerda], &vetor[direita]);
    if (vetor[meio] > vetor[direita])
        troca(&vetor[meio], &vetor[direita]);
    return meio;
}

void quickSort(int* vetor, int esquerda, int direita) {
    if (esquerda >= direita)
        return;

    int i = esquerda, j = direita;
    int pivoIndex = medianaDeTres(vetor, esquerda, direita); // Pivô é a mediana de três
    int pivo = vetor[pivoIndex];
    troca(&vetor[pivoIndex], &vetor[direita]);

    while (i < j) {
        while (i < j && vetor[i] < pivo)
            i++;
        while (i < j && vetor[j] >= pivo)
            j--;
        if (i < j) {
            troca(&vetor[i], &vetor[j]);
        }
    }

    vetor[direita] = vetor[i];
    vetor[i] = pivo;

    quickSort(vetor, esquerda, i - 1);
    quickSort(vetor, i + 1, direita);
}

int* lerArquivo(const char* nome_arquivo, int num_elementos) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    int* numeros = (int*)malloc(num_elementos * sizeof(int));
    if (!numeros) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return NULL;
    }

    int i = 0, numero;
    while (fscanf(arquivo, "%d", &numero) == 1 && i < num_elementos) {
        numeros[i++] = numero;
    }
    fclose(arquivo);
    return numeros;
}

void criarDiretorio(const char* path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

void reverterVetor(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho / 2; i++) {
        troca(&vetor[i], &vetor[tamanho - 1 - i]);
    }
}

int main() {
    int num_elementos;
    int ordem;
    const int iteracoes = 10;
    const char* pasta_base = "Vetores/";
    const char* nomes_arquivos[10] = {
        "Vetor0.txt", "Vetor1.txt", "Vetor2.txt",
        "Vetor3.txt", "Vetor4.txt", "Vetor5.txt",
        "Vetor6.txt", "Vetor7.txt", "Vetor8.txt",
        "Vetor9.txt"
    };

    char pasta_resultados_base[150];
    char pasta_resultados_tipo[150];
    printf("Quantos números dos arquivos você quer utilizar? ");
    scanf("%d", &num_elementos);

    printf("Você deseja utilizar o vetor de forma 1 (desordenada), 2 (crescente) ou 3 (decrescente)? ");
    scanf("%d", &ordem);

    switch (ordem) {
        case 1:
            strcpy(pasta_resultados_base, "QuickSort/Pivo Mediana Tres/Resultados/C/");
            strcpy(pasta_resultados_tipo, "QuickSort/Pivo Mediana Tres/Resultados/Desordenado/");
            break;
        case 2:
            strcpy(pasta_resultados_base, "QuickSort/Pivo High/Resultados/C/");
            strcpy(pasta_resultados_tipo, "QuickSort/Pivo Mediana Tres/Resultados/Crescente/");
            break;
        case 3:
            strcpy(pasta_resultados_base, "QuickSort/Pivo Mediana Tres/Resultados/C/");
            strcpy(pasta_resultados_tipo, "QuickSort/Pivo Mediana Tres/Resultados/Decrescente/");
            break;
        default:
            fprintf(stderr, "Opção inválida. Por favor, selecione 1, 2 ou 3.\n");
            return 1;
    }

    criarDiretorio(pasta_resultados_base);
    criarDiretorio(pasta_resultados_tipo);

    char arquivo_resultados_base[150];
    char arquivo_resultados_tipo[150];
    switch (ordem) {
        case 1:
            sprintf(arquivo_resultados_base, "%sMAXdesordenadoC.txt", pasta_resultados_base);
            sprintf(arquivo_resultados_tipo, "%sMAXdesordenadoC.txt", pasta_resultados_tipo);
            break;
        case 2:
            sprintf(arquivo_resultados_base, "%sMAXcrescenteC.txt", pasta_resultados_base);
            sprintf(arquivo_resultados_tipo, "%sMAXcrescenteC.txt", pasta_resultados_tipo);
            break;
        case 3:
            sprintf(arquivo_resultados_base, "%sMAXdecrescenteC.txt", pasta_resultados_base);
            sprintf(arquivo_resultados_tipo, "%sMAXdecrescenteC.txt", pasta_resultados_tipo);
            break;
    }

    double duracao_total = 0.0;

    for (int k = 0; k < 10; k++) {
        char caminho_arquivo[150];
        sprintf(caminho_arquivo, "%s%s", pasta_base, nomes_arquivos[k]);
        int* original = lerArquivo(caminho_arquivo, num_elementos);
        if (!original) {
            fprintf(stderr, "Erro ao ler o arquivo %s\n", caminho_arquivo);
            continue;
        }

        if (ordem == 2) {
            quickSort(original, 0, num_elementos - 1);
        } else if (ordem == 3) {
            quickSort(original, 0, num_elementos - 1);
            reverterVetor(original, num_elementos);
        }

        clock_t inicio = clock();
        for (int i = 0; i < iteracoes; i++) {
            int* dados = (int*)malloc(num_elementos * sizeof(int));
            memcpy(dados, original, num_elementos * sizeof(int));
            quickSort(dados, 0, num_elementos - 1);
            free(dados);
        }
        clock_t fim = clock();
        double duracao = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000; // tempo em milissegundos
        duracao_total += duracao;
        printf("Tempo de execução para o arquivo %s: %lf ms\n", nomes_arquivos[k], duracao);
        free(original);
    }

    double duracao_media = duracao_total / 10;
    printf("Tempo médio de execução: %lf ms\n", duracao_media);

    // Salva o resultado em ambos os arquivos sem limpar os resultados anteriores
    FILE* arquivo_saida_base = fopen(arquivo_resultados_base, "a");
    FILE* arquivo_saida_tipo = fopen(arquivo_resultados_tipo, "a");
    if (arquivo_saida_base && arquivo_saida_tipo) {
        fprintf(arquivo_saida_base, "%d %lf ms\n", num_elementos, duracao_media);
        fprintf(arquivo_saida_tipo, "%d %lf ms\n", num_elementos, duracao_media);
        fclose(arquivo_saida_base);
        fclose(arquivo_saida_tipo);
        printf("Resultados salvos em %s e %s\n", arquivo_resultados_base, arquivo_resultados_tipo);
    } else {
        perror("Erro ao abrir o arquivo de resultados");
    }

    return 0;
}
