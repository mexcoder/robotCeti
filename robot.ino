//estos estan aqui por que es la declaracion de pines
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

unsigned int temp[5],
			 negro[5],
			 gris[5],
			 verde[5],
			 rojo[5],
			 blanco[5];

#define _negro	'N'
#define _verde	'V'
#define _gris   'G'
#define _rojo	'R'
#define _blanco	'B'


#include <LiquidCrystal.h>
#include <EEPROM.h>

//inicializar lcd
LiquidCrystal lcd(4, 5, 0, 1, 2, 3);  

#include "motor.h"
#include "funcionEEPROM.h"
#include "adc.h"
#include "calibracion.h"
#include "colores.h"

int vals[5] = {0,0,0,0,0};

void leerValores(){
      leerValor();
      vals[0] = getColorOfValue(temp[0], 0);
      vals[1] = getColorOfValue(temp[1], 1);
      vals[2] = getColorOfValue(temp[2], 2);
      vals[3] = getColorOfValue(temp[3], 3);
      vals[4] = getColorOfValue(temp[4], 4);
}
void programaSiguePista(){
    cargaColores();   
    
    lcd.clear();
    lcd.write("sigue pista:");
    lcd.setCursor(0,1);
    lcd.write("precione boton sig.");

    setVelocidad(40);
    paro();
    
    //el robot se queda parado hasta que los dos sensores exteriores
    //se posicionen sobre la linea
    int val = LOW;
    do{
      val = digitalRead(siguienteEstado);
    }
    while(val == LOW);
    
    //***************************
    
    //avanzamos
    boolean continuar = true;
    int temp=0;
    int lado=0;
    boolean temp1=false;
    boolean temp2=false;
    do
    {
      leerValores();
      if(vals[2]!=_negro)
      {
        if(vals[2]==_verde)
          temp=1;
        else
        {
          if(vals[2]==_rojo)
            temp=2;
          else
          continuar=false;
        }
        avanza();
      }else{
        if(temp==1)
        setVelocidad(70);
        else
        {
          if(temp==2)
          setVelocidad(80);
        }
        temp=0;
        if(vals[1]!=_negro)
          vueltaIzquierda();
        else
        {
          if(vals[1]!=_negro)
            vueltaDerecha();
          else
          {
            if(vals[0]==_negro && vals[4]==_negro)
              if(lado==0)
                while(vals[0]==_negro && vals[1]==_negro && vals[3]==_negro && vals[4]==_negro)
                {
                  avanza();
                }else{
                  if(lado==1)
                  {
                    while(vals[0]==_negro && vals[1]==_negro && vals[3]==_negro && vals[4]==_negro)
                    {
                      vueltaDerecha();
                    }
                  }else{
                    while(vals[0]==_negro && vals[1]==_negro && vals[3]==_negro && vals[4]==_negro)
                    {
                      vueltaIzquierda();
                    }
                  }
                  lado=0;
                }
            else
            {
              if(vals[0]==_gris||temp1)
              {
                if(vals[0]==_negro)
                  temp1=false;
                else
                {
                  if(vals[0]==_gris)
                  {
                    temp1=true;
                  }else{
                    if(temp1)
                    {
                      lado=1;
                    }
                  }
                }
              }
              if(vals[4]==_gris||temp2)
              {
                if(vals[4]==_negro)
                  temp2=false;
                else
                {
                  if(vals[4]==_gris)
                  {
                    temp2=true;
                  }else{
                    if(temp2)
                    {
                      lado=2;
                    }
                  }
                }
              }
              avanza();
            }
          }
        }
      }
    }while(continuar);
    paro();
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
  setVelocidad(0);
  lcd.begin(16, 2);
  lcd.write("ready!");
  
  //para los motores
  digitalWrite(motorDer0,LOW);  
  digitalWrite(motorDer1,HIGH);
  digitalWrite(motorIzq0,LOW);  
  digitalWrite(motorIzq1,HIGH);
  
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
