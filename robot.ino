
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


#define ERRORNEGRO	30

#define _negro	0x01
#define _verde	0x02
#define _gris	0x03
#define _rojo	0x04
#define _blanco	0x05


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
      int analog = analogRead(s0);
      vals[0] = getColorOfValue(analog, 0);
      analog = analogRead(s1);
      vals[0] = getColorOfValue(analog, 1);
      analog = analogRead(s2);
      vals[0] = getColorOfValue(analog, 2);
      analog = analogRead(s3);
      vals[0] = getColorOfValue(analog, 3);
      analog = analogRead(s4);
      vals[0] = getColorOfValue(analog, 4);
}
void programaSiguePista(){
    cargaColores();
    boolean inicio = false;
    
    int analog = 0;

    setVelocidad(0);
    
    //el robot se queda parado hasta que los dos sensores exteriores
    //se posicionen sobre la linea
    while(!inicio){
     leerValores();
      
      if(vals[0] == _blanco && vals[5] == _blanco){
        inicio = true;
      }
    
    }
    int vel = 80;
    int colorI = _blanco;
    int colorD = _blanco;
    boolean reset = false;
    //avanzamos
    while(true){
      int color = digitalRead(selectorColor);
      leerValores();
      
      //guardar el color leido por los sensores
      if(vals[0]==_gris){
        colorI = _rojo;
        colorD = _gris;
      }
      else if(vals[4]==_gris){
        colorI = _gris;
        //ColorD= _rojo;
      }
      
      if(reset == true){
        colorI = _blanco;
        colorD = _blanco;
        reset = false;
      }
      
      //modificar la velocidad segun el valor leido por el sensor de en medio
      if(vals[2] == _verde)
         vel = 60;
      if(vals[2] == _rojo)
         vel = 80;
      setVelocidad(vel);
      
      if(vals[4] == _negro && vals[3] != _negro){
        
        //disminuir la velocidad para girar
        setVelocidad(20);
        //girar a la XXX parando el motor
        digitalWrite(motorDer0,HIGH);  
        digitalWrite(motorDer1,HIGH);
        digitalWrite(motorIzq0,LOW);  
        digitalWrite(motorIzq1,HIGH);
        do{
          leerValores();
        
        }while(vals[1] == _negro && vals[0] != _negro);
         setVelocidad(vel);
      }
      
      else if(vals[0] == _negro && vals[1] != _negro){
        
        
        //girar a la XXX parando el motor
        digitalWrite(motorDer0,LOW);  
        digitalWrite(motorDer1,HIGH);
        digitalWrite(motorIzq0,HIGH);  
        digitalWrite(motorIzq1,HIGH);
        do{
          leerValores();
        
        }while(vals[3] == _negro && vals[4] != _negro);
      
        //restaurar velocidad
        setVelocidad(vel);
      }
      
      else if((vals[1] == _negro && vals[3] == _negro && vals[4] == _negro ) &&
             ((color == 1 && colorD== _rojo) || (color == 0 && colorD== _verde) )){

                reset = true;
        boolean done = false;
        
        do{
          //disminuir la velocidad para girar
          setVelocidad(20);
          do{
            //girar a la XXX parando el motor
            digitalWrite(motorDer0,LOW);  
            digitalWrite(motorDer1,HIGH);
            digitalWrite(motorIzq0,HIGH);  
            digitalWrite(motorIzq1,HIGH);
            leerValores();
            
          }while(vals[4] != _blanco);
          
          //ESTA PARTE NO VA PORQUE ESTARIAS REGRESANDO AL PUNTO DE PARTIDA
          /*do{
            //girar a la XXX parando el motor
            digitalWrite(motorDer0,LOW);  
            digitalWrite(motorDer1,HIGH);
            digitalWrite(motorIzq0,HIGH);  
            digitalWrite(motorIzq1,HIGH);
            leerValores();
            
          }while(vals[4] != _blanco);*/
          
          do{
            //avanzar
            digitalWrite(motorDer0,LOW);  
            digitalWrite(motorDer1,HIGH);
            digitalWrite(motorIzq0,LOW);  
            digitalWrite(motorIzq1,HIGH);
            leerValores();
            
          }while(vals[0] != _blanco);
          
          do{
            //reverza
            digitalWrite(motorDer0,HIGH);  
            digitalWrite(motorDer1,LOW);
            digitalWrite(motorIzq0,HIGH);  
            digitalWrite(motorIzq1,HIGH);
            leerValores();
            
          }while(vals[0] != _blanco && vals[4] != _blanco);
          done = true;
        }while(done == false);
 
        //restaurar velocidad
        setVelocidad(vel);      
    }
    
    else if((vals[0] == _negro && vals[1] == _negro && vals[3] == _negro ) &&
             ((color == 0 && colorI == _rojo) || (color == 1 && colorI == _verde) )){
        reset = true;
        boolean done = false;
        
        do{
          //disminuir la velocidad para girar
          setVelocidad(20);
          do{
            //girar a la XXX parando el motor
            digitalWrite(motorDer0,HIGH);  
            digitalWrite(motorDer1,HIGH);
            digitalWrite(motorIzq0,LOW);  
            digitalWrite(motorIzq1,HIGH);
            leerValores();
            
          }while(vals[0] != _blanco);
          /*ESTA PARRTE NO VA TAMPOCO POR LO MISMO
          do{
            //girar a la XXX parando el motor
            digitalWrite(motorDer0,HIGH);  
            digitalWrite(motorDer1,HIGH);
            digitalWrite(motorIzq0,LOW);  
            digitalWrite(motorIzq1,HIGH);
            leerValores();
            
          }while(vals[0] != _blanco);
          */
          do{
            //avanzar
            digitalWrite(motorDer0,LOW);  
            digitalWrite(motorDer1,HIGH);
            digitalWrite(motorIzq0,LOW);  
            digitalWrite(motorIzq1,HIGH);
            leerValores();
            
          }while(vals[4] != _blanco);
          
          do{
            //reverza
            digitalWrite(motorDer0,HIGH);  
            digitalWrite(motorDer1,HIGH);
            digitalWrite(motorIzq0,HIGH);  
            digitalWrite(motorIzq1,LOW);
            leerValores();

          }while(vals[0] != _blanco && vals[4] != _blanco);
          done = true;
          
        }while(done == false);
 
        //restaurar velocidad
        setVelocidad(vel);      
    }
}
}

void programaPruebaCalibracion(){
  cargaColores();
  setVelocidad(25);
  while(true)
  {
    int analog = analogRead(s0);
    int val = getColorOfValue(analog, 0);
    lcd.write("1:");
    lcd.print(val);
    lcd.write(" ");
    
    analog = analogRead(s0);
    val = getColorOfValue(analog, 0);
    lcd.write("2:");
    lcd.print(val);
    lcd.write(" ");
    
    analog = analogRead(s0);
    val = getColorOfValue(analog, 0);
    lcd.write("3:");
    lcd.print(val);
    lcd.write(" ");
    
    analog = analogRead(s0);
    val = getColorOfValue(analog, 0);
    lcd.setCursor(0,1);
    lcd.write("4:");
    lcd.print(val);
    lcd.write(" ");
    
    analog = analogRead(s0);
    val = getColorOfValue(analog, 0);
    lcd.write("5:");
    lcd.print(val);
    lcd.write(" ");
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
