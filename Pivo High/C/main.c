#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

void quickSort(int* vetor, int esquerda, int direita) {
    int i = esquerda, j = direita;
    int pivo = vetor[direita];  // Escolhendo o pivô como o elemento mais à direita

    while (i <= j) {
        while (vetor[i] < pivo)
            i++;
        while (vetor[j] > pivo)
            j--;
        if (i <= j) {
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }
    }

    if (esquerda < j)
        quickSort(vetor, esquerda, j);
    if (i < direita)
        quickSort(vetor, i, direita);
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

void ordenarCrescente(int* vetor, int tamanho) {
    quickSort(vetor, 0, tamanho - 1);
}

void ordenarDecrescente(int* vetor, int tamanho) {
    quickSort(vetor, 0, tamanho - 1);
    // Inverter o vetor após ordenar em crescente
    for (int i = 0; i < tamanho / 2; i++) {
        int temp = vetor[i];
        vetor[i] = vetor[tamanho - 1 - i];
        vetor[tamanho - 1 - i] = temp;
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

    char pasta_resultados[200];
    printf("Quantos números dos arquivos você quer utilizar? ");
    scanf("%d", &num_elementos);

    printf("Você deseja utilizar o vetor de forma 1 (desordenada), 2 (crescente) ou 3 (decrescente)? ");
    scanf("%d", &ordem);

    switch (ordem) {
        case 1:
            strcpy(pasta_resultados, "../Resultados/Desordenado/");
            break;
        case 2:
            strcpy(pasta_resultados, "../Resultados/Crescente/");
            break;
        case 3:
            strcpy(pasta_resultados, "../Resultados/Decrescente/");
            break;
        default:
            fprintf(stderr, "Opção inválida. Por favor, selecione 1, 2 ou 3.\n");
            return 1;
    }

    criarDiretorio(pasta_resultados);

    char arquivo_resultados[150];
    sprintf(arquivo_resultados, "%sMAX%sC.txt", pasta_resultados, ordem == 1 ? "Desordenado" : (ordem == 2 ? "Crescente" : "Decrescente"));

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
            ordenarCrescente(original, num_elementos);
        } else if (ordem == 3) {
            ordenarCrescente(original, num_elementos);
            ordenarDecrescente(original, num_elementos);
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

    // Salva o resultado em arquivo sem limpar os resultados anteriores
    FILE* arquivo_saida = fopen(arquivo_resultados, "a");
    if (arquivo_saida) {
        fprintf(arquivo_saida, "%d %lf ms\n", num_elementos, duracao_media);
        fclose(arquivo_saida);
        printf("Resultados salvos em %s\n", arquivo_resultados);
    } else {
        perror("Erro ao abrir o arquivo de resultados");
    }

    // Novo caminho de arquivo para o tempo médio
    char arquivo_resultados_c[150];
    sprintf(arquivo_resultados_c, "../Resultados/C/MAX%sC.txt", ordem == 1 ? "Desordenado" : (ordem == 2 ? "Crescente" : "Decrescente"));

    // Salva o resultado no novo caminho de arquivo sem limpar os resultados anteriores
    FILE* arquivo_saida_c = fopen(arquivo_resultados_c, "a");
    if (arquivo_saida_c) {
        fprintf(arquivo_saida_c, "%d %lf ms\n", num_elementos, duracao_media);
        fclose(arquivo_saida_c);
        printf("Resultados salvos em %s\n", arquivo_resultados_c);
    } else {
        perror("Erro ao abrir o arquivo de resultados");
    }

    return 0;
}
