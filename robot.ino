
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

unsigned int temp[5], mayor[5], check=0,negro[5],gris[5],verde[5],rojo[5],blanco[5];


#define ERRORNEGRO	6

#define _negro	0x01
#define _verde	0x02
#define _gris	0x04
#define _rojo	0x08
#define _blanco	0x10


#include <LiquidCrystal.h>
#include <EEPROM.h>

//inicializar lcd
LiquidCrystal lcd(4, 5, 0, 1, 2, 3);  

#include "motor.h"
#include "funcionEEPROM.h"
#include "adc.h"
#include "calibracion.h"


void programaSiguePista(){
  //TODO: make this!!
}

void programaPruebaCalibracion(){
  //TODO: make this!!
}

void setup() {
  pinMode(selectorColor,INPUT);
  pinMode(motorDer0,OUTPUT);
  pinMode(motorDer1,OUTPUT);
  pinMode(motorIzq0,OUTPUT);
  pinMode(motorIzq1,OUTPUT);
  pinMode(selectorPrograma,INPUT);
  pinMode(siguienteEstado,INPUT);
  pinMode(selectorColor,INPUT);
  analogWrite(pwm,255);
  lcd.begin(16, 2);
  lcd.write("ready!");  
  
}

void loop() {
  
  int programa = digitalRead(selectorPrograma);
  
  if(programa == 1){
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
  lcd.clear();
  lcd.write("programa finalizado");
  
  while(true){
    lcd.setCursor(0,1);
    lcd.write(":)");
    delay(1000);//waste time
    lcd.setCursor(0,1);
    lcd.write(";)");
    delay(100);
  };
  
}
