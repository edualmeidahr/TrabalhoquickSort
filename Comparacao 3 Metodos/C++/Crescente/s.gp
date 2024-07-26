set term png size 1350, 950
set output "C++.png"

set title "C++ - Escolha Diferentes de Pivo - Crescente"
set xlabel "Tamanho dos vetores"
set ylabel "Médias de tempo"
set xrange [10000:5000000]
set yrange [0:5000]
set grid

set datafile separator " "  # Define espaço como separador de dados
set logscale x

set format x "%.0f"  # Formato dos rótulos do eixo x para mostrar valores inteiros
set xtics ( \
    "10k" 10000, \
    "50k" 50000, \
)

plot "crescenteC++.txt" using 1:2 with lines title 'Mediana de 3', \
     "MAXcrescenteC++.txt" using 1:2 with lines title 'Ultimo Elemento', \
     "LOWcrescenteC++.txt" using 1:2 with lines title 'Primeiro Elemento'	

