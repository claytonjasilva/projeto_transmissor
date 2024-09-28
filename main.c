#include <stdio.h>
#include "include/captura_audio.h"

int main() {
    printf("Iniciando captura de áudio...\n");

    // Iniciar captura de áudio por 10 segundos
    if (captura_audio("audio/audio_gravado.wav", "sinal/sinal_tempo.csv") != 0) {
        printf("Erro durante a captura de áudio.\n");
        return 1;
    }

    printf("Captura de áudio concluída.\n");
    return 0;
}
