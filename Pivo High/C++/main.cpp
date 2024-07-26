#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
#include <sys/stat.h>
#include <algorithm> // Adicionando a biblioteca para std::sort e std::reverse

void quickSort(std::vector<int>& vetor, int esquerda, int direita) {
    int i = esquerda, j = direita;
    int pivo = vetor[direita];  // Escolhendo o pivô como o último elemento

    while (i <= j) {
        while (vetor[i] < pivo) i++;
        while (vetor[j] > pivo) j--;
        if (i <= j) {
            std::swap(vetor[i], vetor[j]);
            i++;
            j--;
        }
    }

    if (esquerda < j)
        quickSort(vetor, esquerda, j);
    if (i < direita)
        quickSort(vetor, i, direita);
}

std::vector<int> lerArquivo(const std::string& nome_arquivo, int num_elementos) {
    std::ifstream arquivo(nome_arquivo);
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return {};
    }

    std::vector<int> numeros(num_elementos);
    for (int i = 0; i < num_elementos && arquivo >> numeros[i]; ++i);
    return numeros;
}

void criarDiretorio(const std::string& path) {
    struct stat st = {0};
    if (stat(path.c_str(), &st) == -1) {
        mkdir(path.c_str(), 0700);
    }
}

int main() {
    int num_elementos, ordem;
    const int iteracoes = 10;
    const std::string pasta_base = "Vetores/";
    const std::string nomes_arquivos[10] = {
        "Vetor0.txt", "Vetor1.txt", "Vetor2.txt",
        "Vetor3.txt", "Vetor4.txt", "Vetor5.txt",
        "Vetor6.txt", "Vetor7.txt", "Vetor8.txt",
        "Vetor9.txt"
    };

    std::string pasta_resultados_base, pasta_resultados_tipo;
    std::cout << "Quantos números dos arquivos você quer utilizar? ";
    std::cin >> num_elementos;

    std::cout << "Você deseja utilizar o vetor de forma 1 (desordenada), 2 (crescente) ou 3 (decrescente)? ";
    std::cin >> ordem;

    switch (ordem) {
        case 1:
            pasta_resultados_base = "QuickSort/Pivo High/Resultados/C++/";
            pasta_resultados_tipo = "QuickSort/Pivo High/Resultados/Desordenado/";
            break;
        case 2:
            pasta_resultados_base = "QuickSort/Pivo High/Resultados/C++/";
            pasta_resultados_tipo = "QuickSort/Pivo High/Resultados/Crescente/";
            break;
        case 3:
            pasta_resultados_base = "QuickSort/Pivo High/Resultados/C++/";
            pasta_resultados_tipo = "QuickSort/Pivo High/Resultados/Decrescente/";
            break;
        default:
            std::cerr << "Opção inválida. Por favor, selecione 1, 2 ou 3." << std::endl;
            return 1;
    }

    criarDiretorio(pasta_resultados_base);
    criarDiretorio(pasta_resultados_tipo);

    std::string arquivo_resultados_base, arquivo_resultados_tipo;
    switch (ordem) {
        case 1:
            arquivo_resultados_base = pasta_resultados_base + "MAXdesordenadoC++.txt";
            arquivo_resultados_tipo = pasta_resultados_tipo + "MAXdesordenadoC++.txt";
            break;
        case 2:
            arquivo_resultados_base = pasta_resultados_base + "MAXcrescenteC++.txt";
            arquivo_resultados_tipo = pasta_resultados_tipo + "MAXcrescenteC++.txt";
            break;
        case 3:
            arquivo_resultados_base = pasta_resultados_base + "MAXdecrescenteC++.txt";
            arquivo_resultados_tipo = pasta_resultados_tipo + "MAXdecrescenteC++.txt";
            break;
    }

    double duracao_total = 0.0;

    for (const auto& nome_arquivo : nomes_arquivos) {
        std::string caminho_arquivo = pasta_base + nome_arquivo;
        auto original = lerArquivo(caminho_arquivo, num_elementos);
        if (original.empty()) {
            std::cerr << "Erro ao ler o arquivo " << caminho_arquivo << std::endl;
            continue;
        }

        // Ordena o vetor original conforme a opção escolhida
        if (ordem == 2) {
            std::sort(original.begin(), original.end());
        } else if (ordem == 3) {
            std::sort(original.begin(), original.end());
            std::reverse(original.begin(), original.end());
        }

        clock_t inicio = clock();
        for (int i = 0; i < iteracoes; i++) {
            std::vector<int> dados = original;
            quickSort(dados, 0, num_elementos - 1);
        }
        clock_t fim = clock();
        double duracao = (static_cast<double>(fim - inicio) / CLOCKS_PER_SEC) * 1000; // tempo em milissegundos
        duracao_total += duracao;
        std::cout << "Tempo de execução para o arquivo " << nome_arquivo << ": " << duracao << " ms" << std::endl;
    }

    double duracao_media = duracao_total / 10;
    std::cout << "Tempo médio de execução: " << duracao_media << " ms" << std::endl;

    std::ofstream arquivo_saida_base(arquivo_resultados_base, std::ios::app);
    std::ofstream arquivo_saida_tipo(arquivo_resultados_tipo, std::ios::app);
    if (arquivo_saida_base && arquivo_saida_tipo) {
        arquivo_saida_base << num_elementos << " " << duracao_media << " ms\n";
        arquivo_saida_tipo << num_elementos << " " << duracao_media << " ms\n";
        std::cout << "Resultados salvos em " << arquivo_resultados_base << " e " << arquivo_resultados_tipo << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo de resultados" << std::endl;
    }

    return 0;
}
