void leerValor(){
  int val;
  
   temp[0] = analogRead(s0);
   temp[1] = analogRead(s1);
   temp[2] = analogRead(s2);
   temp[3] = analogRead(s3);  
   temp[4] = analogRead(s4);
   
   lcd.setCursor(0,1);
   lcd.print(temp[2]);
   lcd.write(".0");
   
}


