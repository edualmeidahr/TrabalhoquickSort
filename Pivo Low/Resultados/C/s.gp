set term png size 1350, 950
set output "C.png"

set title "C - Primeiro Elemento"
set xlabel "Tamanho dos vetores"
set ylabel "Médias de tempo"
set xrange [10000:50000]
set yrange [0:7000]
set grid

set datafile separator " "  # Define espaço como separador de dados
set logscale x

set format x "%.0f"  # Formato dos rótulos do eixo x para mostrar valores inteiros
set xtics ( \
    "10k" 10000, \
    "15k" 15000, \
    "20k" 20000, \
    "25k" 25000, \
    "30k" 30000, \
    "35k" 35000, \
    "40k" 40000, \
    "45k" 45000, \
    "50k" 50000, \
)

plot "LOWDesordenadoC.txt" using 1:2 with lines title 'Desordenado', \
     "LOWCrescenteC.txt" using 1:2 with lines title 'Crescente', \
     "LOWDecrescenteC.txt" using 1:2 with lines title 'Decrescente'	

