import os
import time

def quick_sort(vetor, esquerda, direita):
    if esquerda >= direita or esquerda < 0 or direita >= len(vetor):
        return

    i, j = esquerda, direita
    meio = (esquerda + direita) // 2
    pivo = sorted([vetor[esquerda], vetor[meio], vetor[direita]])[1]  # Mediana de três

    while i <= j:
        while vetor[i] < pivo:
            i += 1
        while vetor[j] > pivo:
            j -= 1
        if i <= j:
            vetor[i], vetor[j] = vetor[j], vetor[i]
            i += 1
            j -= 1

    if esquerda < j:
        quick_sort(vetor, esquerda, j)
    if i < direita:
        quick_sort(vetor, i, direita)

def ler_arquivo(nome_arquivo, num_elementos):
    try:
        with open(nome_arquivo, 'r') as file:
            conteudo = file.read()
        partes = conteudo.split()
        numeros = [int(parte) for parte in partes if parte.isdigit() and 0 <= int(parte) <= 1000000]
        return numeros[:num_elementos]
    except Exception as e:
        print(f"Erro ao ler o arquivo: {e}")
        return None

def criar_diretorio(path):
    if not os.path.exists(path):
        os.makedirs(path)

def main():
    num_elementos = int(input('Quantos números dos arquivos você quer utilizar? '))
    ordem = int(input('Você deseja utilizar o vetor de forma 1 (desordenada), 2 (crescente) ou 3 (decrescente)? '))

    if ordem == 1:
        pasta_resultados_base = 'QuickSort/Pivo Mediana Tres/Resultados/Python/'
        pasta_resultados_tipo = 'QuickSort/Pivo Mediana Tres/Resultados/Desordenado/'
    elif ordem == 2:
        pasta_resultados_base = 'QuickSort/Pivo Mediana Tres/Resultados/Python/'
        pasta_resultados_tipo = 'QuickSort/Pivo Mediana Tres/Resultados/Crescente/'
    elif ordem == 3:
        pasta_resultados_base = 'QuickSort/Pivo Mediana Tres/Resultados/Python/'
        pasta_resultados_tipo = 'QuickSort/Pivo Mediana Tres/Resultados/Decrescente/'
    else:
        print('Opção inválida. Por favor, selecione 1, 2 ou 3.')
        return

    criar_diretorio(pasta_resultados_base)
    criar_diretorio(pasta_resultados_tipo)

    nomes_arquivos = [
        'Vetor0.txt', 'Vetor1.txt', 'Vetor2.txt',
        'Vetor3.txt', 'Vetor4.txt', 'Vetor5.txt',
        'Vetor6.txt', 'Vetor7.txt', 'Vetor8.txt',
        'Vetor9.txt'
    ]

    duracao_total = 0.0

    for nome_arquivo in nomes_arquivos:
        caminho_arquivo = os.path.join('Vetores/', nome_arquivo)
        original = ler_arquivo(caminho_arquivo, num_elementos)
        if original is None or len(original) == 0:
            print(f'Erro ao ler o arquivo {caminho_arquivo} ou o arquivo está vazio.')
            continue

        # Ordenar o vetor conforme o caso
        if ordem == 2:  # Ordenar crescente
            original.sort()
        elif ordem == 3:  # Ordenar decrescente
            original.sort(reverse=True)

        inicio = time.time()
        for _ in range(10):
            dados = original[:]
            quick_sort(dados, 0, len(dados) - 1)
        fim = time.time()
        duracao = (fim - inicio) * 1000  # tempo em milissegundos
        duracao_total += duracao
        print(f'Tempo de execução para o arquivo {nome_arquivo}: {duracao:.2f} ms')

    duracao_media = duracao_total / 10
    print(f'Tempo médio de execução: {duracao_media:.2f} ms')

    arquivo_resultados_base = os.path.join(pasta_resultados_base, 'desordenadoPython.txt' if ordem == 1 else 'crescentePython.txt' if ordem == 2 else 'decrescentePython.txt')
    arquivo_resultados_tipo = os.path.join(pasta_resultados_tipo, 'desordenadoPython.txt' if ordem == 1 else 'crescentePython.txt' if ordem == 2 else 'decrescentePython.txt')

    with open(arquivo_resultados_base, 'a') as file:
        file.write(f'{num_elementos} {duracao_media:.2f} ms\n')
    with open(arquivo_resultados_tipo, 'a') as file:
        file.write(f'{num_elementos} {duracao_media:.2f} ms\n')
    print(f'Resultados salvos em {arquivo_resultados_base} e {arquivo_resultados_tipo}')

if __name__ == '__main__':
    main()
