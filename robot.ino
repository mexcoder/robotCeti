
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


unsigned int ERRORNEGRO	= 35;

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
    
    int analog = 0;

    setVelocidad(0);
    
    //el robot se queda parado hasta que los dos sensores exteriores
    //se posicionen sobre la linea
    int val = LOW;
    
    do{
      printAllValuesAtLCD();
      val = digitalRead(siguienteEstado);
    }
    while(val == LOW);
    int vel = 80;
    lcd.clear();
    lcd.print("Boton Presionado");
    while(true){
      leerValores();
      /*
      *
      *  Detecta PWM en este punto
      *
      */
      
      if(vals[2] != _negro){
        setVelocidad(30);
        avanza();
        int lineaCentro = getColorOfValue(capturaUnColor(2),2);
        if(lineaCentro == _verde){
          lcd.setCursor(0,0);
          lcd.write("Verde 60% Porciento");
          vel = 60;
        }
        if(lineaCentro == _rojo){
          lcd.setCursor(0,0); 
          lcd.write("Rojo 80% Porciento");          
          vel = 80;
        }
        
        /******Este segmento de codigo se debe de poner mejor para que funcone correctamente
        */
        if(lineaCentro == _blanco){ 
          lcd.write("Blanco en S3!!! ");
          lcd.setCursor(0,1);
          lcd.write("Adios  :P");
          setVelocidad(0);
          while(true){}
        }
        
        
      }
      
      printAllValuesAtLCD();
      setVelocidad(vel);
      if(vals[1]==_negro &&  vals[3]==_negro){
        
        if(getPorcentageOfValue(temp[1],1)<getPorcentageOfValue(temp[3],3)) giraIzquierda();
        else giraDerecha();
        /*
        *
        *Si vas a detectar gris o estados especiales, hazlo aqui. No preguntes porque.
        *
        */
        
        
        
        
      }
      else{
        if(vals[3]==_blanco){//gira derecha especial
          giraDerechaEspecial();
        }
        else{
          if(vals[0]==_blanco){//gira Izquierda Especial
             giraIzquierdaEspecial();
          }
        }
      }
      
      
    }

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
  
  avanza();
  
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
