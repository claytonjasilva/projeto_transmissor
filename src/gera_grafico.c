#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para gerar gráfico no domínio do tempo
void gerar_grafico_tempo(char *filepath) {
    // Abrindo o pipe para o Gnuplot
    FILE *gnuplotPipe = _popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        // Definir o terminal e o título do gráfico
        fprintf(gnuplotPipe, "set terminal windows\n");  // Ajuste para o terminal apropriado
        fprintf(gnuplotPipe, "set title 'Audio Signal - Time Domain'\n");
        fprintf(gnuplotPipe, "set xlabel 'Tempo (seg)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Intensidade do Sinal'\n");

        // Assumindo que o arquivo CSV tem duas colunas: tempo e intensidade
        // Plota a primeira coluna como 'x' e a segunda como 'y'
        fprintf(gnuplotPipe, "set datafile separator ','\n");  // Define o separador do CSV como vírgula
        fprintf(gnuplotPipe, "plot '%s' using 1:2 with lines title 'Audio Signal'\n", filepath);  // Comando para plotar
        
        fflush(gnuplotPipe);  // Enviar todos os comandos ao Gnuplot
        
        // Fechar o pipe
        _pclose(gnuplotPipe);
    } else {
        printf("Erro ao abrir o pipe para o Gnuplot.\n");
    }
}
