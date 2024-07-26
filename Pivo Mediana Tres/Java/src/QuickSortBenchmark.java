import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.stream.*;

public class QuickSortBenchmark {

    public static void quickSort(int[] vetor, int esquerda, int direita) {
        if (esquerda >= direita || esquerda < 0 || direita >= vetor.length) {
            return;
        }

        int i = esquerda, j = direita;

        // Escolhendo o pivô usando o método da mediana de três
        int meio = (esquerda + direita) / 2;
        int pivo;
        // Ordenando os elementos esquerda, meio e direita
        if (vetor[esquerda] > vetor[meio])
            pivo = vetor[meio];
        else if (vetor[direita] < vetor[meio])
            pivo = vetor[meio];
        else
            pivo = vetor[direita];

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

    public static int[] lerArquivo(String nomeArquivo, int numElementos) {
        List<Integer> numerosList = new ArrayList<>();
        try {
            String conteudo = new String(Files.readAllBytes(Paths.get(nomeArquivo)));
            // Divide a string por espaços e tenta converter cada parte em número
            String[] partes = conteudo.split("\\s+");
            for (String parte : partes) {
                try {
                    if (!parte.isEmpty()) {
                        int numero = Integer.parseInt(parte.trim());
                        if (numero >= 0 && numero <= 1000000) { // Verifica se o número está dentro do intervalo esperado
                            numerosList.add(numero);
                        }
                    }
                } catch (NumberFormatException e) {
                    // Ignora partes que não podem ser convertidas em número
                    System.err.println("Número inválido ignorado: " + parte);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }

        // Limita o número de elementos para o que foi solicitado
        return numerosList.stream().limit(numElementos).mapToInt(i -> i).toArray();
    }

    public static void criarDiretorio(String path) {
        File diretorio = new File(path);
        if (!diretorio.exists()) {
            diretorio.mkdirs();
        }
    }

    public static void ordenarCrescente(int[] vetor) {
        quickSort(vetor, 0, vetor.length - 1);
    }

    public static void ordenarDecrescente(int[] vetor) {
        quickSort(vetor, 0, vetor.length - 1);
        // Reverter o vetor para decrescente
        for (int i = 0; i < vetor.length / 2; i++) {
            int temp = vetor[i];
            vetor[i] = vetor[vetor.length - 1 - i];
            vetor[vetor.length - 1 - i] = temp;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numElementos;
        int ordem;
        final int iteracoes = 1; // Reduzido para otimizar o tempo de execução
        final String pastaBase = "Vetores/";
        final String[] nomesArquivos = {
                "Vetor0.txt", "Vetor1.txt", "Vetor2.txt",
                "Vetor3.txt", "Vetor4.txt", "Vetor5.txt",
                "Vetor6.txt", "Vetor7.txt", "Vetor8.txt",
                "Vetor9.txt"
        };

        String pastaResultadosBase;
        String pastaResultadosTipo;
        System.out.print("Quantos números dos arquivos você quer utilizar? ");
        numElementos = scanner.nextInt();

        System.out.print("Você deseja utilizar o vetor de forma 1 (desordenada), 2 (crescente) ou 3 (decrescente)? ");
        ordem = scanner.nextInt();

        switch (ordem) {
            case 1:
                pastaResultadosBase = "QuickSort/Pivo Mediana Tres/Resultados/Java/";
                pastaResultadosTipo = "QuickSort/Pivo Mediana Tres/Resultados/Desordenado/";
                break;
            case 2:
                pastaResultadosBase = "QuickSort/Pivo Mediana Tres/Resultados/Java/";
                pastaResultadosTipo = "QuickSort/Pivo Mediana Tres/Resultados/Crescente/";
                break;
            case 3:
                pastaResultadosBase = "QuickSort/Pivo Mediana Tres/Resultados/Java/";
                pastaResultadosTipo = "QuickSort/Pivo Mediana Tres/Resultados/Decrescente/";
                break;
            default:
                System.err.println("Opção inválida. Por favor, selecione 1, 2 ou 3.");
                return;
        }

        criarDiretorio(pastaResultadosBase);
        criarDiretorio(pastaResultadosTipo);

        String arquivoResultadosBase;
        String arquivoResultadosTipo;
        switch (ordem) {
            case 1:
                arquivoResultadosBase = pastaResultadosBase + "desordenadoJava.txt";
                arquivoResultadosTipo = pastaResultadosTipo + "desordenadoJava.txt";
                break;
            case 2:
                arquivoResultadosBase = pastaResultadosBase + "crescenteJava.txt";
                arquivoResultadosTipo = pastaResultadosTipo + "crescenteJava.txt";
                break;
            case 3:
                arquivoResultadosBase = pastaResultadosBase + "decrescenteJava.txt";
                arquivoResultadosTipo = pastaResultadosTipo + "decrescenteJava.txt";
                break;
            default:
                arquivoResultadosBase = "";
                arquivoResultadosTipo = "";
                break;
        }

        double duracaoTotal = 0.0;

        for (int k = 0; k < 10; k++) {
            String caminhoArquivo = pastaBase + nomesArquivos[k];
            int[] original = lerArquivo(caminhoArquivo, numElementos);
            if (original == null || original.length == 0) {
                System.err.println("Erro ao ler o arquivo " + caminhoArquivo + " ou o arquivo está vazio.");
                continue;
            }

            // Ordena o vetor de acordo com a opção escolhida
            if (ordem == 2) {
                ordenarCrescente(original);
            } else if (ordem == 3) {
                ordenarCrescente(original);
                ordenarDecrescente(original);
            }

            long inicio = System.currentTimeMillis();
            // Executa a ordenação apenas uma vez para benchmarking
            int[] dados = Arrays.copyOf(original, original.length);
            quickSort(dados, 0, dados.length - 1);
            long fim = System.currentTimeMillis();
            double duracao = fim - inicio; // tempo em milissegundos
            duracaoTotal += duracao;
            System.out.printf("Tempo de execução para o arquivo %s: %.2f ms%n", nomesArquivos[k], duracao);
        }

        double duracaoMedia = duracaoTotal / 10;
        System.out.printf("Tempo médio de execução: %.2f ms%n", duracaoMedia);

        // Salva o resultado em ambos os arquivos sem limpar os resultados anteriores
        try (PrintWriter arquivoSaidaBase = new PrintWriter(new FileWriter(arquivoResultadosBase, true));
             PrintWriter arquivoSaidaTipo = new PrintWriter(new FileWriter(arquivoResultadosTipo, true))) {
            arquivoSaidaBase.printf("%d %.2f ms%n", numElementos, duracaoMedia);
            arquivoSaidaTipo.printf("%d %.2f ms%n", numElementos, duracaoMedia);
            System.out.printf("Resultados salvos em %s e %s%n", arquivoResultadosBase, arquivoResultadosTipo);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
