void setVelocidad(int porcentaje){
  int val = map(porcentaje,100,0,0,255);
  analogWrite(pwm,val);
}
