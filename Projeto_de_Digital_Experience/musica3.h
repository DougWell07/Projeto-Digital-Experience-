#pragma once
#include <avr/pgmspace.h>
#include "notas.h"

// Pacman Intro Theme - Robson Couto, 2019
// https://github.com/robsoncouto/arduino-songs
// Partitura: https://musescore.com/user/85429/scores/107109
// Formato: nota, duração (4 = semínima, 8 = colcheia, negativo = pontuada)

const int tempo3 = 105;

const int melodia3[] PROGMEM = {
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16,
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32,
  NOTE_FS5, -16, NOTE_DS5, 8, NOTE_DS5, 32, NOTE_E5, 32, NOTE_F5, 32,
  NOTE_F5, 32, NOTE_FS5, 32, NOTE_G5, 32, NOTE_G5, 32, NOTE_GS5, 32, NOTE_A5, 16, NOTE_B5, 8
};

const int notas3 = sizeof(melodia3) / sizeof(melodia3[0]) / 2;