int vals[5] = {0,0,0,0,0};
int vel;
  void giraCaminoIzquierda(){
//    lcd.clear();
    //lcd.write("Girando A la Izquierda");
    while(vals[4]==_negro){
         leerValores();
         giraIzquierda();
     }
     while(vals[3]==_blanco){
         leerValores();
         giraIzquierda();
     }
     while(vals[0]==_negro){
         leerValores();
         giraDerecha();
     }
  }
  void giraCaminoDerecha(){
//    lcd.clear();
    //lcd.write("Girando A la Izquierda");
    while(vals[0]==_negro){
         leerValores();
         giraDerecha();
     }
     while(vals[1]==_negro){
         leerValores();
         giraDerecha();
     }
     while(vals[4]==_negro){
         leerValores();
         giraIzquierda();
     }
  }
