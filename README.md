# Reprodutor de Músicas com Arduino UNO

Projeto da disciplina CCP020 - Digital Experience Ultimate (Centro Universitário FEI)
Professor: Isaac
Autores: Douglas Wellington Pinto e Lucas Bartoletti Sanches

---

## 1. Introdução

### Problema
Desenvolver um reprodutor de músicas simples, semelhante a um MP3 player básico, usando Arduino UNO. O aparelho deve ter músicas gravadas na memória, permitir que o usuário escolha uma delas em um menu e a reproduza no buzzer.

### Objetivos
- Armazenar no mínimo 5 músicas na memória do Arduino.
- Listar os nomes das músicas em um display LCD 16x2 I2C e permitir a seleção com os botões UP e DOWN.
- Tocar a música selecionada no buzzer ao apertar play.
- Permitir pausar, retomar e parar a música durante a execução.
- Indicar o estado com LEDs: verde mostra que a música está sendo executada e vermelho quando está pausada.

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
| Resistor [valor, ex.: 220 ohms] | 2 | Proteção dos LEDs |
| Buzzer | 1 | Reprodução do som |
| Protoboard | 1 | Montagem do circuito |
| Jumpers | 12 | Conexões |

### 2.2 Ligações (pinagem)

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

Os botões usam o resistor interno do Arduino (`INPUT_PULLUP`): um terminal vai ao pino e o outro ao GND, e o botão pressionado lê `LOW`.

<table>
  <tr>
    <td align="center" width="50%">
      <!-- Primeira foto: Quadrada -->
      <img src="https://github.com/user-attachments/assets/1bbb7d7c-8c0a-45d8-944c-12ad562199f8" width="400" height="400" style="object-fit: cover;" alt="Montagem física">
      <br>
      <sub><b>Figura 1:</b> Montagem prática</sub>
    </td>
    <td align="center" width="50%" valign="top">
      <!-- Segunda foto: Retangular (puxada para cima com valign="top") -->
      <img src="[URL_OU_CAMINHO_DA_FOTO_2](https://github.com/user-attachments/assets/51941b70-a004-4d2c-9284-60df95f88742)" width="500" height="281" style="object-fit: cover;" alt="Esquema do circuito">
      <br>
      <sub><b>Figura 2:</b> Diagrama esquemático</sub>
    </td>
  </tr>
</table>

### 2.3 Métodos: como o projeto foi desenvolvido

O desenvolvimento foi feito em etapas, e cada uma foi testada antes da seguinte (o histórico de commits mostra essa evolução):

1. **Estrutura e hardware:** organização do código e mapeamento dos pinos.
2. **Menu:** seleção com UP e DOWN, detectando o instante do aperto ao comparar a leitura atual com a do loop anterior.
3. **LCD:** exibição do menu com seta indicando a música selecionada.
4. **Estados:** máquina de estados com Menu, Tocando e Pausado, que define o que cada botão faz e qual LED acende.
5. **Dados das músicas:** cada música em um arquivo `.h`, armazenada na memória FLASH com `PROGMEM` e lida com `pgm_read_word()`.
6. **Reprodução:** toca uma nota por vez usando `millis()`, sem `delay()`, para que os botões continuem respondendo durante a música.

#### Músicas

| Arquivo | Música | BPM |
|---|---|---|
| `musica1.h` | Harry Potter (Hedwig's Theme) | 144 |
| `musica2.h` | Star Wars (Main Theme) | 108 |
| `musica3.h` | Pacman (Intro) | 105 |
| `musica4.h` | Take on me | 140 |
| `musica5.h` | Marcha Imperial (Star Wars) | 120 |

#### Organização dos arquivos

```
projeto/
├── projeto.ino    # setup, loop, estados e funções
├── notas.h        # tabela nota -> frequência
├── musica1.h      # Harry Potter
├── musica2.h      # Star Wars
├── musica3.h      # Pacman
├── musica4.h      # Take on me
└── musica5.h      # Marcha Imperial
```

#### Como o código funciona

- **Detecção do aperto:** o botão só conta quando a leitura atual é `LOW` e a do loop anterior era `HIGH`. Segurar o botão não repete a ação.
- **Máquina de estados:** a variável `estado` (Menu, Tocando, Pausado) define o que cada botão faz. A função `mudaEstado()` centraliza a troca, atualizando LEDs, LCD e som de uma vez.
- **Reprodução sem travar:** a função `tocaMusica()` roda a cada volta do `loop()` e compara `millis()` com o instante em que a nota começou. Quando a duração termina, `iniciaNota()` lê a próxima nota e a toca com `tone()`.
- **Pause e stop:** o pause silencia o buzzer com `noTone()` e guarda o índice da nota (`notaAtual`). O stop zera o índice e volta ao menu.
- **Pausas na música (`REST`):** apenas silenciam o buzzer pela duração.
- **Notas pontuadas:** duração negativa significa 1,5 vez a duração normal.

#### Decisões de projeto

- **Dados separados da lógica:** as músicas são vetores (nota, duração) e uma única função toca qualquer uma delas, evitando repetir código.
- **PROGMEM:** o Arduino UNO tem 2 KB de RAM; guardar os vetores na FLASH evita estourar a memória.
- **`millis()` no lugar de `delay()`:** o `delay()` travaria a leitura dos botões, impedindo o pause e o stop.
- **Um arquivo por música:** facilita trocar ou adicionar músicas sem mexer na lógica do player.

---

## 3. Experimentos

<!-- TODO: acrescentar fotos e escrever uma ou duas frases explicando cada foto/vídeo -->

Vídeos de demonstração:

- [Vídeo 1: útlimo teste realizado, com o projeto funcionando](https://github.com/user-attachments/assets/e2cb54dd-2cb5-40ce-953d-b92c3f56576a)
- [Vídeo 2: Dia da apresentação do projeto na FEI](https://github.com/user-attachments/assets/b63423f5-017c-4713-bdb5-ecd76530a51b)

### Problemas encontrados e soluções

<!-- TODO: manter só o que realmente aconteceu com vocês -->
- Nomes de constantes repetidos entre os arquivos de música causaram erro de compilação (`tempo1` em mais de um arquivo). Cada música passou a ter a sua (`tempo1` a `tempo5`.
- Uma nota declarada duas vezes no `notas.h` causou erro de redefinição. A linha repetida foi removida.
- A biblioteca `LiquidCrystal_I2C` não estava instalada no computador do laboratório. Foi instalada pelo Gerenciador de Bibliotecas.

---

## 4. Tecnologias utilizadas

- **Arduino UNO** (ATmega328P)
- **Linguagem C/C++** (Arduino)
- **Arduino IDE** [versão]
- **Tinkercad Circuits:** simulação antes da montagem real
- **Biblioteca LiquidCrystal_I2C** (Frank de Brabander) [versão]: controle do LCD I2C
- **Biblioteca Wire:** comunicação I2C
- **avr/pgmspace.h:** `PROGMEM` e `pgm_read_word()`
- **Funções `tone()` e `noTone()`:** geração do som no buzzer
- **Git e GitHub:** controle de versão e colaboração

---

## 5. Conclusão

O projeto atingiu o objetivo de criar um reprodutor de música com Arduino UNO que armazena cinco músicas, lista seus nomes no LCD, toca a música escolhida no buzzer e permite pausar, retomar e parar com indicação por LED's.

O principal desafio foi permitir pause e stop durante a música. A solução foi tocar uma nota por vez em 'millis()', em vez de usar 'delay()', o que manteve os botões sempre respondendo. Outro desafio foi o limite de memória, resolvido guardando as músicas na FLASH com 'PROGMEM'.

A criação deste projeto nos permitiu colocar em prática todos os conceitos adquiridos durante este semestre nas aulas de Digital Experience. Entre eles, destacam-se o funcionamento da biblioteca, a utilização do millis() em vez do delay(), o uso de funções e outros princípios fundamentais que propiciaram a realização bem-sucedida do trabalho.

---

### Créditos e referências 

- Melodias (Hedwig's Theme, Star Wars, Pacman, Take on me e Imperial March): Robson Couto, repositório https://github.com/robsoncouto/arduino-songs (2019).
- A lógica de cálculo de duração das notas (tempo, notas pontuadas e 90% de som por notas) é baseada no código original do mesmo repositório.
- Site que utilizei para ter detalhes do Buzzer,[Documentação Oficial do Modulino Buzzer](https://docs.arduino.cc/tutorials/modulino-buzzer/how-buzzer/).
