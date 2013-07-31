void setVelocidad(int porcentaje){
  int val = map(porcentaje,100,0,0,255);
  analogWrite(pwm,val);
}

void avanza(){
  //poner ambos motores asia adelante
  digitalWrite(motorDer0,LOW);  
  digitalWrite(motorDer1,HIGH);
  digitalWrite(motorIzq0,LOW);  
  digitalWrite(motorIzq1,HIGH);
}

void paro(){
  
  digitalWrite(motorDer0,HIGH); //GVE THE MOTOR SOME POT 
  digitalWrite(motorDer1,HIGH);
  digitalWrite(motorIzq0,HIGH);  
  digitalWrite(motorIzq1,HIGH);
  
}

void giraDerecha(){
  //PARAR EL MOTOR PARA QUE EL OTRO SIGA GIRANDO
  digitalWrite(motorDer0,HIGH);  
  digitalWrite(motorDer1,HIGH);
  digitalWrite(motorIzq0,LOW);  
  digitalWrite(motorIzq1,HIGH);
}

void giraIzquierda(){

  digitalWrite(motorDer0,LOW);  
  digitalWrite(motorDer1,HIGH);
  //PARAR EL MOTOR PARA QUE EL OTRO SIGA GIRANDO
  digitalWrite(motorIzq0,HIGH);  
  digitalWrite(motorIzq1,HIGH);
  
}

void giraIzquierdaAtras(){
  //PARAR EL MOTOR PARA QUE EL OTRO SIGA GIRANDO
  digitalWrite(motorDer0,LOW);  
  digitalWrite(motorDer1,LOW);
  digitalWrite(motorIzq0,HIGH);  
  digitalWrite(motorIzq1,LOW);
}

void giraDerechaAtras(){

  digitalWrite(motorDer0,HIGH);  
  digitalWrite(motorDer1,LOW);
  //PARAR EL MOTOR PARA QUE EL OTRO SIGA GIRANDO
  digitalWrite(motorIzq0,LOW);  
  digitalWrite(motorIzq1,LOW);
  
}



void giraDerechaEspecial(){
    //girar el motor hacia atras para que de una vuelta mas cerrada
  digitalWrite(motorDer0,HIGH);  
  digitalWrite(motorDer1,LOW);
  digitalWrite(motorIzq0,LOW);  
  digitalWrite(motorIzq1,HIGH);
}

void giraIzquierdaEspecial(){
  
  digitalWrite(motorDer0,LOW);  
  digitalWrite(motorDer1,HIGH);
  digitalWrite(motorIzq0,HIGH);  
  digitalWrite(motorIzq1,LOW);
}

void reversa(){
  
  digitalWrite(motorDer0,HIGH);  
  digitalWrite(motorDer1,LOW);
  digitalWrite(motorIzq0,HIGH);  
  digitalWrite(motorIzq1,LOW);

}
