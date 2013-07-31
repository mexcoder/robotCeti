int vals[5] = {0,0,0,0,0};
int vel;
void AvanzaCaminoFrente(){
        lcd.clear();
        lcd.write("A Cruzar calles!");  
        
        
        int primeroQueTocaLinea=0;
        boolean checa[2]={LOW,LOW};
        while(checa[0]==LOW || checa[0]==LOW ){
          leerValores();
          setVelocidad(40);
          reversa();
          if(vals[0]!=_negro){
            checa[0] = HIGH;
            if(primeroQueTocaLinea==0)
              primeroQueTocaLinea = 1;
          }
          if(vals[4]!=_negro ){
            checa[1] = HIGH;
            if(primeroQueTocaLinea==0)
              primeroQueTocaLinea = 2;
          }
        }
        
        lcd.clear();
        lcd.write("1");  
        

        if(vals[0]!=_negro && vals[4]!=_negro){//si los dos son blancos sigue al mayor
          if(primeroQueTocaLinea==1){
            lcd.setCursor(0,1);
            lcd.write("2");  
        
            while(vals[0]!=_negro){
              leerValores();
              setVelocidad(40);
              giraIzquierda();
            }
            lcd.setCursor(0,1);
            lcd.write("3");  
        
          }else{//2
            lcd.setCursor(0,1);
            lcd.write("4");  
          while(vals[4]!=_negro){
              leerValores();
              setVelocidad(40);
              giraDerecha();
            }
            lcd.setCursor(0,1);
            lcd.write("5");  
        
          }  
        }else{ 
          lcd.setCursor(0,1);
            lcd.write("6");  
        if(vals[0]==_negro){
          while(vals[0]==_negro){
            leerValores();
            setVelocidad(40);
            giraIzquierda();//Especial
          }
          lcd.setCursor(0,1);
            lcd.write("7");  
        }else{
          while(vals[4]==_negro){
            leerValores();
            setVelocidad(40);
            giraDerecha();//Especial
          }
          lcd.setCursor(0,1);
            lcd.write("8");  
          }
        }
        lcd.setCursor(0,1);
            lcd.write("9");  
        
        while(vals[0]!=_negro){
          leerValores();
          setVelocidad(40);
          giraIzquierda();
        }
        lcd.setCursor(0,1);
            lcd.write("10");  
        
        while(vals[4]!=_negro){
          leerValores();
          setVelocidad(40);
          giraDerecha();
        }
        lcd.setCursor(0,1);
            lcd.write("11");  
        
        while(vals[0]!=_negro || vals[4]!=_negro){
          leerValores();
          setVelocidad(40);
          avanza();
        }
        lcd.setCursor(0,1);
            lcd.write("12");  
        
        while(vals[0]==_negro && vals[4]==_negro){
          leerValores();
          setVelocidad(vel);
          avanza();
        }
        lcd.setCursor(0,1);
            lcd.write("13");  
        
        lcd.clear();
        lcd.write("Aprendi a cruzar");
        while(true){paro();}
        
        }
  void giraCaminoDerecha(){
     /*while(vals[4]==_negro){
          leerValores();
          giraDerecha();
     }*/
     while(vals[0]==_negro){
         leerValores();
         giraDerecha();
     }
//     while(vals[4]==_negro){
//         leerValores();
//         avanza();
//     }
//     while(vals[4]==_negro){
//         leerValores();
//         giraDerechaAtras();
//     }
     
  }
  void giraCaminoIzquierda(){
    while(vals[3]==_negro){
         leerValores();
         giraIzquierda();
     }
  }
