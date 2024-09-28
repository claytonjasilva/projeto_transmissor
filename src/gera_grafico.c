#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para gerar gráficos usando GNUplot
void gerar_grafico(const char* data_filename, const char* grafico_filename, const char* titulo, const char* eixo_x, const char* eixo_y) {
    char gnuplot_command[512];
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    
    if (gnuplot == NULL) {
        printf("Erro ao abrir GNUplot.\n");
        return;
    }

    // Comandos para configurar o gráfico
    fprintf(gnuplot, "set terminal png size 800,600\n"); // Gráfico em PNG
    fprintf(gnuplot, "set output '%s'\n", grafico_filename); // Nome do arquivo do gráfico
    fprintf(gnuplot, "set title '%s'\n", titulo); // Título do gráfico
    fprintf(gnuplot, "set xlabel '%s'\n", eixo_x); // Rótulo do eixo X
    fprintf(gnuplot, "set ylabel '%s'\n", eixo_y); // Rótulo do eixo Y
    fprintf(gnuplot, "plot '%s' using 1:2 with lines title 'Sinal'\n", data_filename); // Plotando o arquivo de dados

    pclose(gnuplot);
    printf("Gráfico gerado e salvo como %s.\n", grafico_filename);
}

void gerar_grafico_tempo(const char* audio_name) {
    char data_filename[100];
    char grafico_filename[100];
    char titulo[150];
    
    // Definir os arquivos de dados e gráficos
    printf("Digite o nome do arquivo de dados de tempo (sem extensao): ");
    scanf("%s", data_filename);
    snprintf(data_filename, sizeof(data_filename), "sinal/%s_tempo.csv", data_filename);
    
    printf("Digite o nome do arquivo de gráfico (sem extensao): ");
    scanf("%s", grafico_filename);
    snprintf(grafico_filename, sizeof(grafico_filename), "graficos/%s_tempo.png", grafico_filename);

    // Título do gráfico
    snprintf(titulo, sizeof(titulo), "%s - domínio do tempo", audio_name);

    // Gerar o gráfico
    gerar_grafico(data_filename, grafico_filename, titulo, "tempo (seg)", "intensidade sinal");
}

void gerar_grafico_frequencia(const char* audio_name) {
    char data_filename[100];
    char grafico_filename[100];
    char titulo[150];
    
    // Definir os arquivos de dados e gráficos
    printf("Digite o nome do arquivo de dados de frequência (sem extensao): ");
    scanf("%s", data_filename);
    snprintf(data_filename, sizeof(data_filename), "sinal/%s_frequencia.csv", data_filename);
    
    printf("Digite o nome do arquivo de gráfico (sem extensao): ");
    scanf("%s", grafico_filename);
    snprintf(grafico_filename, sizeof(grafico_filename), "graficos/%s_frequencia.png", grafico_filename);

    // Título do gráfico
    snprintf(titulo, sizeof(titulo), "%s - domínio da frequência", audio_name);

    // Gerar o gráfico
    gerar_grafico(data_filename, grafico_filename, titulo, "frequência (Hz)", "intensidade sinal");
}
