void leerValor(){
  int val;
  
   temp[0] = analogRead(s0);
   temp[1] = analogRead(s1);
   temp[2] = analogRead(s2);
   temp[3] = analogRead(s3);  
   temp[4] = analogRead(s4);
   
/*   lcd.setCursor(0,1);
   lcd.print(temp[2]);
   lcd.write(" N:");
   lcd.print(negro[2]);
   lcd.write(".0");
   */
}

int getColorOfValue(int value, int pos){
	int result=0;
				if(value < negro[pos]) result = _negro;
				else{
					if(value < verde[pos]) result = _verde;
					else{
						if(value < gris[pos]) result = _gris;
						else{
							if(value < rojo[pos]) result = _rojo;
							else 			result = _blanco; // Blanco
						}
					}
				}
	return result;
}



int getPorcentageOfValue(int value, int pos){
	int result=0;
				if(value < negro[pos]) result = negro[pos] - value;
				else{
					if(value < verde[pos]) result = ((float)(value-negro[pos])/(float)(verde[pos]-negro[pos]))*100;
					else{
						if(value < gris[pos]) result = ((float)(value-verde[pos])/(float)(gris[pos]-verde[pos]))*100;
						else{
							if(value < rojo[pos]) result = ((float)(value-gris[pos])/(float)(rojo[pos]-gris[pos]))*100;
							else 			result = ((float)(value-rojo[pos])/(float)(blanco[pos]-rojo[pos]))*100;
						}
					}
				}
	return result;
}

