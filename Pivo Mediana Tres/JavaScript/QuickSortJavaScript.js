const fs = require('fs');
const path = require('path');

function quickSort(arr, left, right) {
    if (left >= right || left < 0 || right >= arr.length) {
        return;
    }

    let i = left;
    let j = right;

    // Escolhendo o pivô usando o método da mediana de três
    const mid = Math.floor((left + right) / 2);
    if (arr[left] > arr[mid]) {
        [arr[left], arr[mid]] = [arr[mid], arr[left]];
    }
    if (arr[left] > arr[right]) {
        [arr[left], arr[right]] = [arr[right], arr[left]];
    }
    if (arr[mid] > arr[right]) {
        [arr[mid], arr[right]] = [arr[right], arr[mid]];
    }
    const pivot = arr[mid];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            [arr[i], arr[j]] = [arr[j], arr[i]];
            i++;
            j--;
        }
    }

    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

function readFile(fileName, numElements) {
    try {
        const data = fs.readFileSync(fileName, 'utf8');
        const numbers = data.split(/\s+/).map(part => {
            const num = parseInt(part, 10);
            return (Number.isInteger(num) && num >= 0 && num <= 1000000) ? num : null;
        }).filter(num => num !== null);

        return numbers.slice(0, numElements);
    } catch (err) {
        console.error(`Erro ao ler o arquivo ${fileName}:`, err);
        return [];
    }
}

function createDirectory(dirPath) {
    if (!fs.existsSync(dirPath)) {
        fs.mkdirSync(dirPath, { recursive: true });
    }
}

function sortAscending(arr) {
    quickSort(arr, 0, arr.length - 1);
}

function sortDescending(arr) {
    return arr.reverse();
}

const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const iteracoes = 10;
const pastaBase = 'Vetores/';
const nomesArquivos = [
    "Vetor0.txt", "Vetor1.txt", "Vetor2.txt",
    "Vetor3.txt", "Vetor4.txt", "Vetor5.txt",
    "Vetor6.txt", "Vetor7.txt", "Vetor8.txt",
    "Vetor9.txt"
];

rl.question('Quantos números dos arquivos você quer utilizar? ', (numElementos) => {
    rl.question('Você deseja utilizar o vetor de forma 1 (desordenada), 2 (crescente) ou 3 (decrescente)? ', (ordem) => {
        let pastaResultadosBase;
        let pastaResultadosTipo;

        switch (ordem) {
            case '1':
                pastaResultadosBase = 'QuickSort/Pivo Mediana Tres/Resultados/JavaScript';
                pastaResultadosTipo = 'QuickSort/Pivo Mediana Tres/Resultados/Desordenado/';
                break;
            case '2':
                pastaResultadosBase = 'QuickSort/Pivo Mediana Tres/Resultados/JavaScript/';
                pastaResultadosTipo = 'QuickSort/Pivo Mediana Tres/Resultados/Crescente/';
                break;
            case '3':
                pastaResultadosBase = 'QuickSort/Pivo Mediana Tres/Resultados/JavaScript/';
                pastaResultadosTipo = 'QuickSort/Pivo Mediana Tres/Resultados/Decrescente/';
                break;
            default:
                console.error('Opção inválida. Por favor, selecione 1, 2 ou 3.');
                rl.close();
                return;
        }

        createDirectory(pastaResultadosBase);
        createDirectory(pastaResultadosTipo);

        const arquivoResultadosBase = path.join(pastaResultadosBase, ordem === '1' ? 'desordenadoJavaScript.txt' : ordem === '2' ? 'crescenteJavaScript.txt' : 'decrescenteJavaScript.txt');
        const arquivoResultadosTipo = path.join(pastaResultadosTipo, ordem === '1' ? 'desordenadoJavaScript.txt' : ordem === '2' ? 'crescenteJavaScript.txt' : 'decrescenteJavaScript.txt');

        let duracaoTotal = 0;

        let promises = nomesArquivos.map((nomeArquivo) => {
            const caminhoArquivo = path.join(pastaBase, nomeArquivo);
            const original = readFile(caminhoArquivo, parseInt(numElementos, 10));
            if (original.length === 0) {
                console.error(`Erro ao ler o arquivo ${caminhoArquivo} ou o arquivo está vazio.`);
                return Promise.resolve();
            }

            if (ordem === '2') {
                sortAscending(original);
            } else if (ordem === '3') {
                sortAscending(original);
                sortDescending(original);
            }

            const start = process.hrtime.bigint();
            for (let i = 0; i < iteracoes; i++) {
                const dados = [...original];
                quickSort(dados, 0, dados.length - 1);
            }
            const end = process.hrtime.bigint();
            const duracao = Number(end - start); // Tempo total em nanosegundos
            duracaoTotal += duracao;
            console.log(`Tempo de execução para o arquivo ${nomeArquivo}: ${(duracao / 1_000_000).toFixed(4)} ms`); // Convertendo para milissegundos

            return Promise.resolve();
        });

        Promise.all(promises).then(() => {
            const duracaoMedia = duracaoTotal / (iteracoes * 1_000_000); // Tempo médio em milissegundos
            console.log(`Tempo médio de execução: ${duracaoMedia.toFixed(4)} ms`);

            fs.appendFileSync(arquivoResultadosBase, `${numElementos} ${duracaoMedia.toFixed(4)} ms\n`);
            fs.appendFileSync(arquivoResultadosTipo, `${numElementos} ${duracaoMedia.toFixed(4)} ms\n`);
            console.log(`Resultados salvos em ${arquivoResultadosBase} e ${arquivoResultadosTipo}`);

            rl.close();
        });
    });
});