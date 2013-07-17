
const int selectorColor = 8;
const int pwm = 9;
const int motorDer0 = 10;
const int motorDer1 = 11;
const int motorIzq0 = 12;
const int motorIzq1 = 13;
const int selectorPrograma = 6;
const int siguienteEstado = 7;
const int selectorColor = 8;
const int s0 = A0;
const int s1 = A1;
const int s2 = A2;
const int s3 = A3;
const int s4 = A4;

/**
 * LCD RS pin to digital pin 4
 * LCD Enable pin to digital pin 5
 * LCD D4 pin to digital pin 0
 * LCD D5 pin to digital pin 1
 * LCD D6 pin to digital pin 2
 * LCD D7 pin to digital pin 3
**/

#define ERRORNEGRO	6

#define _negro	0x01
#define _verde	0x02
#define _gris	0x04
#define _rojo	0x08
#define _blanco	0x10


#include <LiquidCrystal.h>
#include "funcionEEPROM.h"

//inicializar lcd
LiquidCrystal lcd(4, 5, 0, 1, 2, 3);

unsigned int temp[5], mayor[5], check=0;

void setup() {
  pinMode(selectorColor,INPUT);
  pinMode(motorDer0,OUTPUT);
  pinMode(motorDer1,OUTPUT);
  pinMode(motorIzq0,OUTPUT);
  pinMode(motorIzq1,OUTPUT);
  pinMode(selectorPrograma,INPUT);
  pinMode(siguienteEstado,INPUT);
  pinMode(selectroColor,INPUT);
  analogWrite(pwm,255);
    
  
}

void loop() {
  
  int programa = digitalRead(selectorPrograma);
  
  if(program == 1){
    int color = digitalRead(selectorColor);
    if(color== 1) 
        programaCalibraColores(); //rojo
    else
        programaPruebaCalibracion(); // gris
  }
  else{
    cargaColores();
    programaSiguePista();
  }
  // remplazar por mensage de fin de programa
  // PORTD = 0x99;
  while(true);
  
}
