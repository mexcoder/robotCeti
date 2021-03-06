int color;
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


unsigned int errorNegro[5];

#define _negro	'N'
#define _verde	'V'
#define _gris   'G'
#define _rojo	'R'
#define _blanco	'B'


#include <LiquidCrystal.h>
#include <EEPROM.h>

//inicializar lcd
LiquidCrystal lcd(4, 5, 3, 2, 1, 0);  

#include "motor.h"
#include "funcionEEPROM.h"
#include "adc.h"
#include "calibracion.h"
#include "Giros.h"



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
    vel = 100;
 
    #define _derecha 1
    #define _izquierda 2
    #define _avanza 0
    int direccion = _avanza;
    int message = _avanza;//este solo muestra los valores de calibracion
    
    /*Variables Lic*/
    int lado=0;
    boolean temp1=false;
    boolean temp1_2=false;
    boolean temp2_2=false;
    boolean temp2=false;
    ///////////////////////
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
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.write("Verde 80% Porciento");
          vel = 80;
          message=80;
        }
        if(lineaCentro == _rojo){
          lcd.clear();
          lcd.setCursor(0,0); 
          lcd.write("Rojo 60% Porciento");          
          vel = 60;
          message = 60;
        }
        
        /******Este segmento de codigo se debe de poner mejor para que funcone correctamente
        */
        if(lineaCentro == _blanco){ 
          lcd.clear();
          lcd.write("Blanco en S3!!! ");
          lcd.setCursor(0,1);
          lcd.write("Adios  :P");
          setVelocidad(0);
          while(true){}
        }
        
        
      }
      /////Segmento para pruebas
      lcd.setCursor(0,0);
      switch (message){
        case 60:
            lcd.write("Velocidad 60%");
        break;
        case 80:
            lcd.write("Velocidad 80%");
        break;
        case _izquierda:
            lcd.write("Gris a La Izquierda :D");
        break;
        case _derecha:
            lcd.write("Gris a La Derecha D:");
        break;
        default:
            printAllValuesAtLCD();
        break;
      }
      setVelocidad(vel);
      if(vals[1]==_negro &&  vals[3]==_negro){
        int por = getPorcentageOfValue(temp[1],1)-getPorcentageOfValue(temp[3],3);
        if(por<0) por*=-1;
       if(por<10){
         avanza();
       }else{ 
        if(getPorcentageOfValue(temp[1],1)<getPorcentageOfValue(temp[3],3)) giraIzquierda();
        else giraDerecha();
      }
        if(vals[0]==_negro && vals[4]==_negro && vals[2]==_negro){
          /*
          *
          * Este es el segmento de bifurcaciones:
          *    -Toda bifurcacion existente cae aqui
          *
          */
          switch(lado)
          {
            case 1: if(color!=0)
                    {
                      giraCaminoDerecha();
                      temp2_2=true;
                      temp1_2=true;
                      temp1=false;
                    }
                    else
                    {
                      giraCaminoIzquierda();
                      temp1_2=true;
                      temp2_2=true;
                      temp1=false;
                    }
                    lado=0;
                    message = _avanza;
                    break;
            case 2: if(color!=0)
                    {
                      giraCaminoIzquierda();
                      temp2_2=true;
                      temp1_2=true;
                      temp2=false;
                    }
                    else
                    {
                      giraCaminoDerecha();
                      temp2_2=true;
                      temp1_2=true;
                      temp2=false;
                    }
                    lado=0;
                    message=_avanza;
                    break;
                    
          }
        }
        /*
        *
        *Si vas a detectar gris o estados especiales, hazlo aqui.
        *
        */ 
        int calculoDeDiferencia = (getPorcentageOfValue(temp[1],1)-getPorcentageOfValue(temp[3],3));
        if(calculoDeDiferencia < 0)calculoDeDiferencia*=-1;
        if((getPorcentageOfValue(temp[1],1)*5/100)>calculoDeDiferencia && vals[0]!=_negro && vals[4]!=_negro){
          /*
          *
          *Hacer aqui la deteccion de color lateral
          *
          */
          
          if(vals[0]==_gris||temp1)
              {
                if(vals[0]==_negro||vals[1]==_blanco)
                {
                  temp1=false;
                  setVelocidad(vel);
                  temp1_2=true;
                }
                else
                {
                  if(vals[0]==_gris&&!temp1_2)
                  {
                   // /*
                    giraDerecha();  
                    while(temp[0] > negro[0]-(errorNegro[0]/2))
                      {
                        leerValor();
                      }
                      setVelocidad(25);
                      giraIzquierda();
                      while(temp[0]<(negro[0]+errorNegro[0])){
                        leerValorMostrandoEnLCD();
                      }
                      if(getColorOfValue(capturaUnColor(0),0)==_gris){//*/
                        temp1=true;  
                      ///*
                    }else temp1_2=true;
                       while(temp[0] > negro[0]-(errorNegro[0]/2))
                       {
                         leerValores();
                         giraDerecha();
                       }
                       setVelocidad(vel);//*/
                  }else{
                    temp1_2=false;
                    if(temp1&&lado==0)
                    {
                      temp1=false;
                      lado=1;
                      lcd.clear();
                      message = _derecha;
                      setVelocidad(vel);
                    }
                  }
                }
              }
              if(vals[4]==_gris||temp2)
              {
                if(vals[4]==_negro||vals[3]==_blanco)
                {
                  temp2=false;
                  setVelocidad(vel);
                  temp2_2=true;
                }
                else
                {
                  if(vals[4]==_gris&&!temp2_2)
                  {
                     /*while(temp[i] > negro[i]-(errorNegro[i]/2))
                      {
                        leerValor();
                        giraIzquierda();
                      }
                      setVelocidad(25);
                      giraDerecha();
                      while(temp[4]<(negro[4]+errorNegro[4])){
                        leerValorMostrandoEnLCD();
                      }
                      if(getColorOfValue(capturaUnColor(4),4)==_gris){*/
                        temp2=true;  
                     /* }else temp2_2=true;
                       while(temp[4]  negro[4]+(errorNegro[4]))
                       {
                         leerValores();
                         giraIzquierda();
                       }
                       setVelocidad(vel);*/
                  }else{
                    temp2_2=false;
                    if(temp2&&lado==0)
                    {
                      lado=2;
                      temp2=false;
                      lcd.clear();
                      message = _izquierda;
                      setVelocidad(vel);
                    }
                  }
                }
              }
        }
        
      }
      else{
        if(vals[1]==_blanco &&  vals[3]==_blanco){
          if(getPorcentageOfValue(temp[1],1)<getPorcentageOfValue(temp[3],3)) giraDerecha();
          else giraIzquierda();
         }else{
            if(vals[3]==_blanco){//gira derecha especial
              giraDerechaEspecial();
            if(vals[0]==_negro)//este if lo agrego lic para que funcione el algoritmo para la deteccion de colores laterales
              temp1_2=true;
            }
            else{
              if(vals[0]==_blanco){//gira Izquierda Especial
                 giraIzquierdaEspecial();
              if(vals[3]==_negro)//este if tambien es para la deteccion de colores laterales
                temp2_2=true;
              }
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
  for(int i=0; i<5; i++){
    errorNegro[i]=20;
  }
  setVelocidad(0);
  lcd.begin(16, 2);
  lcd.write("ready!");
  
  avanza();
  
}

void loop() {
  
  int programa = digitalRead(selectorPrograma);
  
  if(programa == 1){
    color = digitalRead(selectorColor);
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
