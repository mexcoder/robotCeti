void setVelocidad(int porcentaje){
  int val = map(porcentaje,0,100,0,255);
  analogWrite(pwm,val);
}
