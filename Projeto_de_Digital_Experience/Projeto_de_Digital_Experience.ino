/*
Título: Projeto de Digital Experience
Autor: Douglas Wellington Pinto
Data: 03/11/2026
Versão: 1.0
Descrição de funcionamento do programa: 
*/

// ===========    Inclusão de Bibliotecas    =========== //



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
const int buzzer =  12;  

// ===========  Criação de variáveis globais =========== //
const int totalMusicas = 5;
const int 


// Leitura atual e anterior dos botões do menu //
int estadob1 = HIGH;
int estadob2 = HIGH;
int ultimoB1 = HIGH;
int ultimoB2 = HIGH;


// ===========      Criação de Objetos       =========== //




// ===========      Configurações iniciais   =========== //

void setup() 
{
  
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(12, OUTPUT);
  
  Serial.begin(9600);
  Serial.print("================= COMUNICACAO ESTABELECIDA =================");
}


// ===========         Loop Infinito       =========== //

void loop() 
{
  estadob1 = digitalRead(b1);
  if (estadob1 == LOW) && (ultimoB1 == HIGH)
  {
    if (musicaSelecionada > 0)
    {
      musicaSelecionada--; 
      Serial.print("Selecionada: ");
      Serial.println(musicaSelecionada);
    }
  }

  ultimoB1 = estadoB1;

  estadob2 = digitalRead(b2);
  if (estadob2 == HIGH) && (ultimoB2 == LOW)
  {
    if (musicaSelecionada < totalMusicas - 1)
    {
      musicaSelecionada++;
      Serial.print("Selecionada: ");
      Serial.print(musicaSelecionada);
    }
  }

  ultimoB2 = estadob2;

}
