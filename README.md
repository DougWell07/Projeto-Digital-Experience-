# Projeto-Digital-Experience-

## 1. Introdução

### Problema 
Desenvolver um reprodutor de músicas simples, semelhante a um MP3 player básico, usando Arduino UNO. O aparelho deve ter músicas gravadas na memória, permitir que o usuário escola uma delas em um menu e a reproduza em buzzer. 

### Objetivos 
- Armazenar no mínimo 5 músicas na memória do Arduino.
- Listar os nomes das músicas em um display LCD 16x2 I2C e permitir a seleção com os botões UP e DOWN.
- Tocar a música selecionada no buzzer ao apertar play.
- Permitir pausar, retomar e parar a música durante a execução.
- Indicar o estado com LED's: verde mostra que a música esta sendo executada e vermelho quando esta pausada.

---

## 2. Metodologia 

### 2.1 Materiais utilizados 

| Componente | Quantidade | Função |
|---|---|---|
| Arduino UNO | 1 | Microcontrolador |
| Display LCD 16x2 com módulo I2C | 1 | Exibe o menu e o estado |
| Botões (push button) | 4 | UP, DOWN, PLAY/PAUSE e STOP |
| LED verde | 1 | Indica música tocando |
| LED vermelho | 1 | Indica música pausada |
| Resistor [valor, ex: 220 ohms] | 2 | Proteção dos LED's |
| Buzzer | 1 | Reprodução do som |
| Protoboard e jumpers | 1 / 12 | Conexões | 

### 2.2. Ligações (pinagem)

| Componente | Pino do Arduino |
|---|---|
| Botão UP | 8 |
| Botão DOWN | 9 |
| Botão PLAY/PAUSE | 10 |
| Botão STOP | 11 |
| LED verde | 7 |
| LED vermelho | 6 |
| Buzzer | 12 |
| LCD (SDA / SCL) | A4 / A5 |

Os botões usam o resistor interno do Arduino ('INPUT_PULLUP'): um terminal vai ao pino e o outro ao GND, e o botão pressionado lê 'LOW'.

<!-- Tem que colocar as fotos do TinkerCad e a do projeto já finalizado -->


### 2.3  Métodos: como o projeto foi desenvolvido 

O desenvolvimento foi feiro em etapas, e cada uma for testada antes da seguinte (o histórico de commits mostra essa evolução): 

1. **Estrutura e hardware:** organização do código e mapeamento dos pinos.
2. **Menu:** seleção com UP e DOWN, detectando o instante do aperto ao comparar a leitura atual com o a do loop anterior.
3. **LCD:** exibição do menu com esta indicando a música selecionada.
4. **Estados:** máquina de estados com Menu, Tocando e Pausado, que define o que cada botão faz e qual LED acende.
5. **Dados das músicas:** cada música em um arquivo '.h', armazenada na memória FLASH com 'PROGMEM' e lida com 'pmg_read_word()'.
6. **Reprodução:** toca uma nota por vez usando 'millis()', sem 'delay()', para que os botões continuem respondendo durante a música.

#### Músicas

| Arquivo | Música | BPM |
|---|---|---|
| 'musica1.h' | Harry Potter (Hedwig's Theme) | 144 |
| 'musica2.h' | Star Wars (Main Theme) | 108 |
| 'musica3.h' | Pacman (Intro) | 105 |
| 'musica4.h' | Take on me  | 140 |
| 'musica5.h' | Marcha Imperial (Star Wars) | 120 |

#### Organização dos arquivos 

'''
projeto/
├── projeto.ino    # setup, loop, estados e funções
├── notas.h        # tabela nota -> frequência
├── musica1.h      # Harry Potter
├── musica2.h      # Star Wars
├── musica3.h      # Pacman
├── musica4.h      # Take on me
└── musica5.h      # Marcha Imperial
'''
