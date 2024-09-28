#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <C:\Program Files (x86)\OpenAL 1.1 SDK\include/al.h>
#include <C:\Program Files (x86)\OpenAL 1.1 SDK\include/alc.h>
#include "include/captura_audio.h"
#include "include/gera_audio.h"

int main() {
    int opcao;
    const char *csv_arquivo = "C:\\Users\\ASUS\\Documents\\GitHub\\projeto_transmissor\\sinal\\"; // Caminho base para o nome do arquivo
    char caminho_completo[300];  // Buffer para armazenar o caminho completo (base + nome do arquivo)
    char continuar;
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
            case 1: {
                char nome_arquivo[50];
                printf("Gravar audio:\n");
                printf("Digite o nome base do arquivo (sem extensao): ");
                scanf("%s", nome_arquivo);
                
                // Nome completo para áudio e dados de tempo
                char audio_filename[300];
                char data_filename[300];

                // Concatena o nome do arquivo fornecido com o caminho base para os dados de áudio e tempo
                snprintf(audio_filename, sizeof(audio_filename), "audio/%s.wav", nome_arquivo);
                snprintf(data_filename, sizeof(data_filename), "%s%s_tempo.csv", nome_base, nome_arquivo);

                // Iniciar captura de áudio
                if (captura_audio(audio_filename, data_filename) != 0) {
                    printf("Erro durante a captura de áudio.\n");
                } else {
                    printf("Captura de áudio concluída e salva como: %s\n", audio_filename);
                    printf("Dados de tempo salvos como: %s\n", data_filename);
                }
                break;
            }
            case 2: {
                char nome_arquivo[50];
                printf("Digite o nome base do arquivo (sem extensao): ");
                scanf("%s", nome_arquivo);
                strcpy(caminho_completo, csv_arquivo);  // Copiar o caminho base para o buffer mutável
                gerar_grafico_tempo(strcat(caminho_completo, nome_arquivo));  // Chamar função de gráfico no domínio do tempo
            
                break;
            }
            case 3:
                printf("Futura implementacao");  // Placeholder para futura implementação
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
