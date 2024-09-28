#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <C:\Program Files (x86)\OpenAL 1.1 SDK\include/al.h>
#include <C:\Program Files (x86)\OpenAL 1.1 SDK\include/alc.h>
#include "include/captura_audio.h"

// Protótipo de funções futuras
void gerar_graficos();
void gerar_sinal_frequencia();

int main() {
    int opcao;
    char audio_filename[100];
    char data_filename[100];
    char continuar = 'n';
    char nome_base[50]; // Base para o nome do arquivo

    do {
        printf("Selecione a opcao:\n");
        printf("1. Gravar audio\n");
        printf("2. Gerar graficos\n");
        printf("3. Gerar sinal no dominio da frequencia\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("Gravar audio:\n");
                printf("Digite o nome base do arquivo (sem extensao): ");
                scanf("%s", nome_base);
                
                // Nomeia o arquivo de áudio e o arquivo de dados (tempo)
                snprintf(audio_filename, sizeof(audio_filename), "audio/%s.wav", nome_base);
                snprintf(data_filename, sizeof(data_filename), "sinal/%s_tempo.csv", nome_base);

                // Iniciar captura de áudio
                if (captura_audio(audio_filename, data_filename) != 0) {
                    printf("Erro durante a captura de áudio.\n");
                } else {
                    printf("Captura de áudio concluída e salva como: %s\n", audio_filename);
                }
                break;

            case 2:
                gerar_graficos();
                break;

            case 3:
                gerar_sinal_frequencia();
                break;

            case 0:
                printf("Encerrando...\n");
                exit(0);

            default:
                printf("Opcao invalida!\n");
        }

        printf("Deseja continuar? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    return 0;
}

// Função placeholder para gerar gráficos
void gerar_graficos() {
    printf("Funcao para gerar graficos ainda nao implementada.\n");
}

// Função placeholder para gerar sinal no domínio da frequência
void gerar_sinal_frequencia() {
    printf("Funcao para gerar sinal no dominio da frequencia ainda nao implementada.\n");
}
