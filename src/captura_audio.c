#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <C:\Program Files (x86)\OpenAL 1.1 SDK\include/al.h>
#include <C:\Program Files (x86)\OpenAL 1.1 SDK\include/alc.h>
#include "../include/captura_audio.h"

#define SAMPLING_RATE 44100
#define DURATION 10  // Duração da gravação em segundos
#define BUFFER_SIZE (SAMPLING_RATE * DURATION)
#define AMPLIFICATION_FACTOR 2.0  // Fator de amplificação do áudio após a normalização

int captura_audio(const char* audio_filename, const char* data_filename) {
    // Inicialização do dispositivo e contexto OpenAL
    ALCdevice *device = alcCaptureOpenDevice(NULL, SAMPLING_RATE, AL_FORMAT_MONO16, BUFFER_SIZE);
    if (!device) {
        fprintf(stderr, "Erro ao abrir dispositivo de captura.\n");
        return 1;
    }

    alcCaptureStart(device);
    printf("Capturando áudio por %d segundos...\n", DURATION);

    // Buffer para armazenar o áudio capturado
    short *buffer = (short*)malloc(sizeof(short) * BUFFER_SIZE);
    if (!buffer) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        alcCaptureCloseDevice(device);
        return 1;
    }

    // Aguardar 10 segundos para capturar o áudio
    int total_samples = 0;
    time_t start_time = time(NULL);

    while (time(NULL) - start_time < DURATION) {
        ALint samples_available;
        alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, (ALCsizei)sizeof(ALint), &samples_available);

        if (samples_available > 0) {
            int samples_to_read = (samples_available < (BUFFER_SIZE - total_samples)) ? samples_available : (BUFFER_SIZE - total_samples);
            alcCaptureSamples(device, buffer + total_samples, samples_to_read);
            total_samples += samples_to_read;

            // Evitar que ultrapasse o buffer
            if (total_samples >= BUFFER_SIZE) {
                break;
            }
        }
    }

    // Parar captura e fechar o dispositivo
    alcCaptureStop(device);
    alcCaptureCloseDevice(device);

    // Salvar o áudio em arquivo .wav
    FILE *audio_file = fopen(audio_filename, "wb");
    if (!audio_file) {
        fprintf(stderr, "Erro ao abrir arquivo de áudio.\n");
        free(buffer);
        return 1;
    }

    // Escrever cabeçalho WAV
    write_wav_header(audio_file, total_samples);

    // Escrever os dados de áudio
    fwrite(buffer, sizeof(short), total_samples, audio_file);
    fclose(audio_file);

    // Normalizar dados e salvar em CSV para gráficos
    FILE *data_file = fopen(data_filename, "w");
    if (!data_file) {
        fprintf(stderr, "Erro ao abrir arquivo de dados.\n");
        free(buffer);
        return 1;
    }

    // Escreve os dados no formato CSV: tempo, intensidade amplificada e normalizada
    for (int i = 0; i < total_samples; i++) {
        float time = (float)i / SAMPLING_RATE;
        // Normalizando o valor do áudio entre -1 e 1
        float normalized_intensity = (float)buffer[i] / 32768.0;
        // Amplificando o sinal após a normalização
        float amplified_intensity = normalized_intensity * AMPLIFICATION_FACTOR;

        // Garantir que o valor não exceda o intervalo [-1, 1] após a amplificação
        if (amplified_intensity > 1.0) {
            amplified_intensity = 1.0;
        } else if (amplified_intensity < -1.0) {
            amplified_intensity = -1.0;
        }

        // Escreve o tempo e a intensidade amplificada no arquivo CSV
        fprintf(data_file, "%f, %f\n", time, amplified_intensity);
    }
    fclose(data_file);

    free(buffer);
    return 0;
}

void write_wav_header(FILE *file, int buffer_size) {
    // Escreve cabeçalho simples de arquivo WAV
    unsigned int sample_rate = SAMPLING_RATE;
    unsigned short num_channels = 1;
    unsigned short bits_per_sample = 16;
    unsigned int byte_rate = sample_rate * num_channels * bits_per_sample / 8;
    unsigned short block_align = num_channels * bits_per_sample / 8;
    unsigned int data_size = buffer_size * sizeof(short);
    unsigned int chunk_size = 36 + data_size;

    // Cabeçalho RIFF
    fwrite("RIFF", 4, 1, file);
    fwrite(&chunk_size, 4, 1, file);
    fwrite("WAVE", 4, 1, file);

    // Subchunk "fmt"
    fwrite("fmt ", 4, 1, file);
    unsigned int subchunk1_size = 16;
    fwrite(&subchunk1_size, 4, 1, file);
    unsigned short audio_format = 1;
    fwrite(&audio_format, 2, 1, file);
    fwrite(&num_channels, 2, 1, file);
    fwrite(&sample_rate, 4, 1, file);
    fwrite(&byte_rate, 4, 1, file);
    fwrite(&block_align, 2, 1, file);
    fwrite(&bits_per_sample, 2, 1, file);

    // Subchunk "data"
    fwrite("data", 4, 1, file);
    fwrite(&data_size, 4, 1, file);
}
