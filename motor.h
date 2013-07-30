void setVelocidad(int porcentaje){
  int val = map(porcentaje,100,0,0,255);
  analogWrite(pwm,val);
}

void vueltaDerecha()
{
  digitalWrite(motorIzq0,LOW);
  digitalWrite(motorIzq1,HIGH);
  digitalWrite(motorDer0,LOW);
  digitalWrite(motorDer1,LOW);  
}

void vueltaIzquierda()
{
  digitalWrite(motorIzq0,LOW);
  digitalWrite(motorIzq1,LOW);
  digitalWrite(motorDer0,LOW);
  digitalWrite(motorDer1,HIGH);
}

void paro()
{
  digitalWrite(motorIzq0,LOW);
  digitalWrite(motorIzq1,LOW);
  digitalWrite(motorDer0,LOW);
  digitalWrite(motorDer1,LOW);
  
}

void avanza()
{
  digitalWrite(motorIzq0,LOW);
  digitalWrite(motorIzq1,HIGH);
  digitalWrite(motorDer0,LOW);
  digitalWrite(motorDer1,HIGH);
}

void reversa()
{
  digitalWrite(motorIzq0,HIGH);
  digitalWrite(motorIzq1,LOW);
  digitalWrite(motorDer0,HIGH);
  digitalWrite(motorDer1,LOW);
}

void reversaDerecha()
{
  digitalWrite(motorIzq0,LOW);
  digitalWrite(motorIzq1,LOW);
  digitalWrite(motorDer0,HIGH);
  digitalWrite(motorDer1,LOW);
}

void reversaIzquierda()
{
  digitalWrite(motorIzq0,HIGH);
  digitalWrite(motorIzq1,LOW);
  digitalWrite(motorDer0,LOW);
  digitalWrite(motorDer1,LOW);
}
