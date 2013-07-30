void capturaColor(){
	/*******Devuelve resultado en Mayor[]*************/
	for(int i=0; i<5; i++) mayor[i]=0;
	leerValor();
	
	do{
		check = 0;
		for(int i=0; i<5; i++){
			if( temp[i] > mayor[i] ) mayor[i] = temp[i];
			if( temp[i] > negro[i]-ERRORNEGRO)check = 1;
		}
		leerValor();
	}while(check == 1);
}
int capturaUnColor(int s){
	int mayor=0;
	while(true){
          	leerValor();
		if( temp[s] > mayor ) mayor = temp[s];
		if( getColorOfValue(temp[s],s)==_negro)break;
	}
        return mayor;
}
void programaCalibraColores(){
        lcd.clear();
        lcd.write("Calibracion:");
        lcd.setCursor(0,1);
        lcd.write("precione boton sig.");
        
        //while((PINB/0x80)== 0){}
        int val = LOW;
        do{
          val = digitalRead(siguienteEstado);
        }
        while(val == LOW);
        
	setVelocidad(25);
	
	leerValor();
	leerValor();
	leerValor();
	
	for(int i=0; i<5; i++)
          negro[i] = temp[i]+ERRORNEGRO;
	
        lcd.clear();
        lcd.write("N");
        
        
	while(temp[2]<(negro[2]+ERRORNEGRO)){
          leerValor();
        }
        
	//PORTD = 0x02;//capturando verde
	capturaColor();
	for(int i=0; i<5; i++) verde[i] =  mayor[i];
	//PORTD = 0x03;//capturado verde
	lcd.clear();
        lcd.write("V");
        
        int dif=2000;
        for(int i=0; i<5; i++){
          int j = verde[i]-negro[i];
          if(j<dif)dif = j;
        }
        for(int i =0; i<5; i++)
          negro[i] = negro[i] - ERRORNEGRO + (dif/2);
        ERRORNEGRO = dif/3;
        
	while(temp[2]<(negro[2]+ERRORNEGRO)){
          leerValor();
        }
	//PORTD = 0x04;//capturando gris
	capturaColor();
	for(int i=0; i<5; i++) gris[i] =  mayor[i];
	//PORTD = 0x05;
	lcd.clear();
        lcd.write("G");
        

	while(temp[2]<(negro[2]+ERRORNEGRO)){
          leerValor();
        }
	//PORTD = 0x06;//capturando rojo
	capturaColor();
	for(int i=0; i<5; i++) rojo[i] =  mayor[i];
	//PORTD = 0x07;
	lcd.clear();
        lcd.write("R");
        
	while(temp[2]<(negro[2]+ERRORNEGRO)){
          leerValor();
        }
	//PORTD = 0x08;//capturando blanco
	capturaColor();
	for(int i=0; i<5; i++) blanco[i] =  mayor[i];
	//PORTD = 0x09;//blanco capturado
	lcd.clear();
        lcd.write("B");
        
	/*
	for(int i=0; i<4; i++){
	  negro[i]  = negro[i]	+ ((verde[i] - negro[i])*2/5);
	  verde[i]  = gris[i];
	  gris[i]   = gris[i]	+ ((rojo[i] - gris[i])/2);
	  rojo[i]   = rojo[i]	+ ((blanco[i] - rojo[i])/2);
	  //La 4 por alguna razon se pasa, no ocupa estos incrementos
	}		
	
	
	/***************CALIBRACION ESPECIFICA*******************************/
	//negro -> verde -> gris -> rojo -> blanco
	/*******Sensor 0 - Derecho***********/
	verde[0] = 0;
	/*******Sensor 1*********************/
	verde[1] = 0;
	gris[1] = 0;
	rojo[1] = 0;
	//esto es para que todos me den negro u otra cosa
	/*******Sensor 2*********************/
	gris[2] = 0;
	//verde[2] = verde[2] - 5;
	/*******Sensor 3*********************/
	verde[3] = 0;
	gris[3] = 0;
	rojo[3] = 0;
	//esto es para que todos me den negro u otra cosa
	/*******Sensor 4 - Izquierdo*********/
	//rojo[4]		= gris[4];
	//gris[4]		= verde[4]	- ((verde[4] - negro[4])/2);
	verde[4]	= 0;
	//int lala = (rojo[4]-gris[4])/4;
	//rojo[4] = rojo[4] - lala;
	//gris[4] = gris[4] + lala;
	
	guardaColoresEnLaEEPROM();
	//OCR1A = 1023;//PWM = 255
        setVelocidad(0);
        lcd.clear();
        lcd.write("termine :)");
	while(1==1){}
	//DDRB = 0b00000010;
	
	
	/*
		
	int ADC_val;
	DDRD = 0xFF;
	DDRB = 0b00000010;
	ADCSRA = 0xC0;
	pos=0;
		while(1)
		{
			pos = ((PINB/0x04)&0x07);
			if(pos > 4) pos = 4;
			ADMUX = pos +0x20;
			
			ADCSRA|=_BV(ADSC);

			ADC_val=(ADCH*62)/254;
			PORTD = getColorOfValue(ADC_val, pos);
		}
*/

}

void printAllValuesAtLCD();
void programaPruebaCalibracion(){
  cargaColores();
  setVelocidad(25);
  while(true)
  {
    printAllValuesAtLCD();
  }
}


