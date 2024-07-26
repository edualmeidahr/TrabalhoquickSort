set term png size 1350, 950
set output "Desordenado.png"

set title "Desordenado - Mediana de 3"
set xlabel "Tamanho dos vetores"
set ylabel "Médias de tempo"
set xrange [10000:5000000]
set yrange [0:12000]
set grid

set datafile separator " "  # Define espaço como separador de dados
set logscale x

set format x "%.0f"  # Formato dos rótulos do eixo x para mostrar valores inteiros
set xtics ( \
    "10k" 10000, \
    "50k" 50000, \
    "100k" 100000, \
    "500k" 500000, \
    "1M" 1000000, \
    "2.5M" 2500000, \
    "5M" 5000000 \
)

plot "desordenadoC.txt" using 1:2 with lines title 'C', \
     "desordenadoC++.txt" using 1:2 with lines title 'C++', \
     "desordenadoC#.txt" using 1:2 with lines title 'C#', \
     "desordenadoJava.txt" using 1:2 with lines title 'Java', \
     "desordenadoJavaScript.txt" using 1:2 with lines title 'JavaScript', \
     "desordenadoPython.txt" using 1:2 with lines title 'Python'

