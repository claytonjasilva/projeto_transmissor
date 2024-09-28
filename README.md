# Projeto Transmissor Analógico

Este projeto simula um transmissor analógico com múltiplos estágios, como captura de áudio, modulação e filtragem. O objetivo é permitir a captura de sinais de áudio, aplicar diferentes tipos de modulações (AM, FM, QAM, PSK, PAM), filtrar o sinal e analisar seu comportamento nos domínios do tempo e da frequência, além de visualizar gráficos para entender o comportamento dos sinais em cada etapa do processo.

## Estrutura do Projeto

O projeto está organizado nos seguintes módulos:

### 1. Captura de Áudio
- **Objetivo**: Capturar áudio mono de 10 segundos e salvar o arquivo em uma pasta específica. 
- **Saída**:
  - Um arquivo de áudio em formato WAV salvo na pasta `/audio`.
  - Um arquivo de dados (`sinal_tempo.csv`) contendo os instantes de amostragem e os valores de intensidade normalizada do áudio.

### 2. Resposta em Frequência
- **Objetivo**: Processar o sinal de áudio capturado e gerar o espectro no domínio da frequência.
- **Saída**:
  - Um arquivo de dados (`sinal_frequencia.csv`) com os valores de intensidade em função da frequência.

### 3. Filtro
- **Objetivo**: Aplicar filtros ao sinal de áudio capturado e gerar a versão filtrada nos domínios do tempo e da frequência.
- **Saída**:
  - Dois arquivos de dados: 
    - `sinal_filtrado_tempo.csv` (sinal filtrado no domínio do tempo).
    - `sinal_filtrado_frequencia.csv` (sinal filtrado no domínio da frequência).

### 4. Modulador
- **Objetivo**: Aplicar diferentes tipos de modulação ao sinal capturado (AM, FM, QAM, PSK, PAM).
- **Saída**:
  - Arquivos de dados contendo os sinais modulados nos domínios do tempo e da frequência, armazenados na pasta `sinal/modulados`.

### 5. Gráficos
- **Objetivo**: Gerar gráficos que representem os sinais em diferentes etapas do processo, tanto no domínio do tempo quanto no da frequência.
- **Saída**:
  - Gráficos gerados e salvos na pasta `/graficos`.

## Estrutura de Diretórios

O projeto segue a seguinte estrutura de diretórios:

```
/transmissor_projeto
│
├── /audio
│   └── audio_gravado.wav         # Arquivos de áudio gravados
│
├── /sinal
│   ├── sinal_tempo.csv           # Dados do sinal no domínio do tempo (amostragem e intensidade)
│   ├── sinal_frequencia.csv      # Dados do sinal no domínio da frequência
│   ├── sinal_filtrado_tempo.csv  # Dados do sinal filtrado no tempo
│   ├── sinal_filtrado_frequencia.csv # Dados do sinal filtrado na frequência
│   └── modulados/                # Subpasta para diferentes modulações
│       ├── am_tempo.csv
│       ├── am_frequencia.csv
│       ├── fm_tempo.csv
│       ├── fm_frequencia.csv
│       ├── qam_tempo.csv
│       ├── qam_frequencia.csv
│       ├── psk_tempo.csv
│       └── psk_frequencia.csv
│
├── /graficos
│   ├── grafico_tempo.png         # Gráficos de sinais no domínio do tempo
│   ├── grafico_frequencia.png    # Gráficos de sinais no domínio da frequência
│   └── grafico_filtrado.png      # Gráficos de sinais filtrados
│
├── src/
│   ├── captura_audio.c           # Código do módulo de captura de áudio
│   ├── resposta_frequencia.c     # Código do módulo de resposta de frequência
│   ├── filtro.c                  # Código do módulo de filtro
│   ├── modulador.c               # Código do módulo de modulação (AM, FM, etc.)
│   └── grafico.c                 # Código para geração de gráficos
│
├── include/
│   └── *.h                       # Arquivos de cabeçalho (.h) usados pelos módulos
│
└── Makefile                      # Makefile para automatizar a compilação e execução dos módulos
```

## Como Compilar

1. Clone o repositório.
2. Navegue até a pasta raiz do projeto.
3. Para compilar o audio_captura.c

```
g++ main.c src/captura_audio.c -o transmissor -I"C:/Program Files (x86)/OpenAL 1.1 SDK/include" -L"C:/Program Files (x86)/OpenAL 1.1 SDK/libs/Win64" -lopenal32
```

## Uso

- Após a compilação, você pode executar cada módulo individualmente conforme necessário, por exemplo:
  ```bash
  ./captura_audio
  ./resposta_frequencia
  ./filtro
  ./modulador
  ./grafico
