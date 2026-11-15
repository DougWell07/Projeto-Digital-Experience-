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
| Protoboard e jumpers | - | Conexões | <!-- colocar dps do trabalho concluído o valor real de jumpers utilizados -->

