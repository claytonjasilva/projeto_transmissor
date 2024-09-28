#ifndef CAPTURA_AUDIO_H
#define CAPTURA_AUDIO_H

int captura_audio(const char* audio_filename, const char* data_filename);
void write_wav_header(FILE *file, int buffer_size);

#endif
