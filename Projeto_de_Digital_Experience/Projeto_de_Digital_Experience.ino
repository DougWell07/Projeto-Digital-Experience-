/*
Título: Projeto de Digital Experience
Autor: Douglas Wellington Pinto e Lucas Bartoletti Sanches
Data: 03/11/2026
Versão: 1.0
Descrição de funcionamento do programa:
  Reprodutor de músicas com Arduino UNO, LCD I2C 16x2, 4 botões,
  2 LEDs e buzzer. (descrever melhor ao final do projeto)
*/

// ===========    Inclusão de Bibliotecas    =========== //
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "notas.h"

// ===========    Mapeamento de Hardware     =========== //

//  Botões //
const int b1 = 8;
const int b2 = 9;
const int b3 = 10;
const int b4 = 11;

// LED's //
const int led1 = 7;
const int led2 = 6;

// Buzzer //
const int buzzer = 12;

// ===========  Criação de variáveis globais =========== //

// Estado do player //
const int Menu = 0;
const int Tocando = 1;
const int Pausado = 2;
int estado = Menu;

// Músicas //
const int totalMusicas = 5;
int musicaSelecionada = 0;

const char* nomes[totalMusicas] = {
  "Harry Potter",
  "Star Wars",
  "Pacman",
  "Musica 4",
  "Musica 5"
};

// Leitura atual de cada botão //
int estadob1 = HIGH;
int estadob2 = HIGH;
int estadob3 = HIGH;
int estadob4 = HIGH;

// Leitura do loop anterior de cada botão //
int ultimoB1 = HIGH;
int ultimoB2 = HIGH;
int ultimoB3 = HIGH;
int ultimoB4 = HIGH;

// ===========      Criação de Objetos       =========== //
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===========      Configurações iniciais   =========== //

void setup()
{
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  Serial.println("================= COMUNICACAO ESTABELECIDA =================");

  mudaEstado(Menu);
}

// ===========         Loop Infinito         =========== //

void loop()
{
  // 1- Lê os 4 botões //
  estadob1 = digitalRead(b1);
  estadob2 = digitalRead(b2);
  estadob3 = digitalRead(b3);
  estadob4 = digitalRead(b4);

  // 2- Menu //
  if (estado == Menu)
  {
    // UP //
    if (estadob1 == LOW && ultimoB1 == HIGH)
    {
      if (musicaSelecionada > 0)
      {
        musicaSelecionada--;
        Serial.print("Selecionada: ");
        Serial.println(musicaSelecionada);
        atualizaMenu();
      }
    }

    // DOWN //
    if (estadob2 == LOW && ultimoB2 == HIGH)
    {
      if (musicaSelecionada < totalMusicas - 1)
      {
        musicaSelecionada++;
        Serial.print("Selecionada: ");
        Serial.println(musicaSelecionada);
        atualizaMenu();
      }
    }

    // PLAY //
    if (estadob3 == LOW && ultimoB3 == HIGH)
    {
      mudaEstado(Tocando);
    }
  }

  // 3- Estado Tocando //
  else if (estado == Tocando)
  {
    // PLAY: pausa //
    if (estadob3 == LOW && ultimoB3 == HIGH)
    {
      mudaEstado(Pausado);
    }

    // STOP: volta ao menu //
    if (estadob4 == LOW && ultimoB4 == HIGH)
    {
      mudaEstado(Menu);
    }
  }

  // 4- Estado Pausado //
  else if (estado == Pausado)
  {
    // PLAY: volta a tocar //
    if (estadob3 == LOW && ultimoB3 == HIGH)
    {
      mudaEstado(Tocando);
    }

    // STOP: volta ao menu //
    if (estadob4 == LOW && ultimoB4 == HIGH)
    {
      mudaEstado(Menu);
    }
  }

  // 5- Guarda as leituras para comparar no próximo loop //
  ultimoB1 = estadob1;
  ultimoB2 = estadob2;
  ultimoB3 = estadob3;
  ultimoB4 = estadob4;
}

// ===========           Funções             =========== //

void atualizaMenu()
{
  lcd.clear();

  if (musicaSelecionada < totalMusicas - 1)
  {
    // Selecionada na linha 1, próxima na linha 2
    lcd.setCursor(0, 0);
    lcd.print("-> ");
    lcd.print(nomes[musicaSelecionada]);

    lcd.setCursor(3, 1);
    lcd.print(nomes[musicaSelecionada + 1]);
  }
  else
  {
    // Última música: anterior na linha 1, selecionada na linha 2
    lcd.setCursor(3, 0);
    lcd.print(nomes[musicaSelecionada - 1]);

    lcd.setCursor(0, 1);
    lcd.print("-> ");
    lcd.print(nomes[musicaSelecionada]);
  }
}

void mudaEstado(int novoEstado)
{
  estado = novoEstado;

  Serial.print("Estado: ");
  if (estado == Menu)
  {
    Serial.println("MENU");
  }

  if (estado == Tocando)
  {
    Serial.println("Tocando");
  }

  if (estado == Pausado)
  {
    Serial.println("Pausado");
  }

  atualizaLeds();

  if (estado == Menu)
  {
    atualizaMenu();
  }
  else
  {
    atualizaTelaReproducao();
  }
}

void atualizaLeds()
{
  digitalWrite(led1, estado == Tocando ? HIGH : LOW);
  digitalWrite(led2, estado == Pausado ? HIGH : LOW);
}

void atualizaTelaReproducao()
{
  lcd.clear();

  lcd.setCursor(0, 0);
  if (estado == Tocando)
  {
    lcd.print("Reproduzindo");
  }
  else
  {
    lcd.print("Pausado");
  }

  lcd.setCursor(0, 1);
  lcd.print(nomes[musicaSelecionada]);
}
