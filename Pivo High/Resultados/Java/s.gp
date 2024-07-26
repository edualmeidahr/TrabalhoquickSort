set term png size 1350, 950
set output "Java.png"

set title "Java - Ultimo Elemento"
set xlabel "Tamanho dos vetores"
set ylabel "Médias de tempo"
set xrange [1000:15000]
set yrange [0:1000]
set grid

set datafile separator " "  # Define espaço como separador de dados
set logscale x

set format x "%.0f"  # Formato dos rótulos do eixo x para mostrar valores inteiros
set xtics ( \
    "1k" 1000, \
    "5k" 5000, \
    "10k" 10000, \
    "12k" 12000, \
    "14k" 14000, \
    "16k" 16000, \
)

plot "MAXdesordenadoJava.txt" using 1:2 with lines title 'Desordenado', \
     "MAXcrescenteJava.txt" using 1:2 with lines title 'Crescente', \
     "MAXdecrescenteJava.txt" using 1:2 with lines title 'Decrescente'

