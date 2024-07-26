using System;
using System.IO;
using System.Linq;
using System.Diagnostics;

class QuickSortCSharp
{
    static void QuickSort(int[] vetor, int esquerda, int direita)
    {
        if (esquerda >= direita || esquerda < 0 || direita >= vetor.Length)
        {
            return;
        }

        int i = esquerda, j = direita;
        int meio = (esquerda + direita) / 2;
        int pivo = new[] { vetor[esquerda], vetor[meio], vetor[direita] }
                    .OrderBy(x => x).Skip(1).First(); // Mediana de três

        while (i <= j)
        {
            while (vetor[i] < pivo) i++;
            while (vetor[j] > pivo) j--;
            if (i <= j)
            {
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
                i++;
                j--;
            }
        }

        if (esquerda < j) QuickSort(vetor, esquerda, j);
        if (i < direita) QuickSort(vetor, i, direita);
    }

    static int[] LerArquivo(string nomeArquivo, int numElementos)
    {
        try
        {
            var conteudo = File.ReadAllText(nomeArquivo);
            var partes = conteudo.Split(new[] { ' ', '\t', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            var numeros = partes.Select(parte =>
            {
                if (int.TryParse(parte, out int numero) && numero >= 0 && numero <= 1000000)
                {
                    return (int?)numero;
                }
                return null;
            }).Where(numero => numero.HasValue).Select(numero => numero.Value).ToArray();

            return numeros.Take(numElementos).ToArray();
        }
        catch (IOException ex)
        {
            Console.WriteLine("Erro ao ler o arquivo: " + ex.Message);
            return null;
        }
    }

    static void CriarDiretorio(string path)
    {
        if (!Directory.Exists(path))
        {
            Directory.CreateDirectory(path);
        }
    }

    static void Main()
    {
        Console.Write("Quantos números dos arquivos você quer utilizar? ");
        int numElementos = int.Parse(Console.ReadLine());

        Console.Write("Você deseja utilizar o vetor de forma 1 (desordenada), 2 (crescente) ou 3 (decrescente)? ");
        int ordem = int.Parse(Console.ReadLine());

        string pastaResultadosBase;
        string pastaResultadosTipo;
        switch (ordem)
        {
            case 1:
                pastaResultadosBase = "QuickSort/Pivo Mediana Tres/Resultados/C#/";
                pastaResultadosTipo = "QuickSort/Pivo Mediana Tres/Resultados/Desordenado/";
                break;
            case 2:
                pastaResultadosBase = "QuickSort/Pivo Mediana Tres/Resultados/C#/";
                pastaResultadosTipo = "QuickSort/Pivo Mediana Tres/Resultados/Crescente/";
                break;
            case 3:
                pastaResultadosBase = "QuickSort/Pivo Mediana Tres/Resultados/C#/";
                pastaResultadosTipo = "QuickSort/Pivo Mediana Tres/Resultados/Decrescente/";
                break;
            default:
                Console.WriteLine("Opção inválida. Por favor, selecione 1, 2 ou 3.");
                return;
        }

        CriarDiretorio(pastaResultadosBase);
        CriarDiretorio(pastaResultadosTipo);

        var nomesArquivos = new[]
        {
            "Vetor0.txt", "Vetor1.txt", "Vetor2.txt",
            "Vetor3.txt", "Vetor4.txt", "Vetor5.txt",
            "Vetor6.txt", "Vetor7.txt", "Vetor8.txt",
            "Vetor9.txt"
        };

        double duracaoTotal = 0.0;

        foreach (var nomeArquivo in nomesArquivos)
        {
            var caminhoArquivo = Path.Combine("Vetores/", nomeArquivo);
            var original = LerArquivo(caminhoArquivo, numElementos);
            if (original == null || original.Length == 0)
            {
                Console.WriteLine($"Erro ao ler o arquivo {caminhoArquivo} ou o arquivo está vazio.");
                continue;
            }

            // Ordenar o vetor conforme o caso
            if (ordem == 2)
            {
                Array.Sort(original); // Ordenar crescente
            }
            else if (ordem == 3)
            {
                Array.Sort(original);
                Array.Reverse(original); // Ordenar decrescente
            }

            var stopwatch = Stopwatch.StartNew();
            for (int i = 0; i < 10; i++)
            {
                var dados = (int[])original.Clone();
                QuickSort(dados, 0, dados.Length - 1);
            }
            stopwatch.Stop();
            double duracao = stopwatch.Elapsed.TotalMilliseconds;
            duracaoTotal += duracao;
            Console.WriteLine($"Tempo de execução para o arquivo {nomeArquivo}: {duracao:F2} ms");
        }

        double duracaoMedia = duracaoTotal / 10;
        Console.WriteLine($"Tempo médio de execução: {duracaoMedia:F2} ms");

        var arquivoResultadosBase = Path.Combine(pastaResultadosBase, ordem == 1 ? "desordenadoC#.txt" : ordem == 2 ? "crescenteC#.txt" : "decrescenteC#.txt");
        var arquivoResultadosTipo = Path.Combine(pastaResultadosTipo, ordem == 1 ? "desordenadoC#.txt" : ordem == 2 ? "crescenteC#.txt" : "decrescenteC#.txt");

        File.AppendAllText(arquivoResultadosBase, $"{numElementos} {duracaoMedia:F2} ms\n");
        File.AppendAllText(arquivoResultadosTipo, $"{numElementos} {duracaoMedia:F2} ms\n");
        Console.WriteLine($"Resultados salvos em {arquivoResultadosBase} e {arquivoResultadosTipo}");
    }
}
