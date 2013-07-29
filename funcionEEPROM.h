void guardaColoresEnLaEEPROM(){
	
	int location = 0x10;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, negro[i]);	
	}
        for(int i=0; i<5; i++){
                EEPROM.write( location+5+i, (negro[i]>>8));	
	}
        		
	location = 0x20;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, verde[i]);		
	}		
	for(int i=0; i<5; i++){
		EEPROM.write( location+5+i, (verde[i]>>8));		
	}		
	location = 0x30;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, gris[i]);	
	}
        for(int i=0; i<5; i++){
		EEPROM.write( location+5+i, (gris[i]>>8));	
	}		
	location = 0x40;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, rojo[i]);		 
	}		
	for(int i=0; i<5; i++){
		EEPROM.write( location+5+i, (rojo[i]>>8));		 
	}		
	location = 0x50;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, blanco[i]);		
	}
        for(int i=0; i<5; i++){
		EEPROM.write( location+5+i, (blanco[i]>>8));		
	}		
}

void cargaColores(){

	int location = 0x10;
	for(int i=0; i<5; i++){
		negro[i]= EEPROM.read( location+i); 
	}		
	for(int i=0; i<5; i++){
		negro[i]+= (EEPROM.read( location+i+5))<<8; 
	}		
	location = 0x20;
	for(int i=0; i<5; i++){
		verde[i]= EEPROM.read( location+i);
		 
	}		
	for(int i=0; i<5; i++){
		verde[i]+= (EEPROM.read( location+i+5))<<8; 
	}		
        location = 0x30;
        for(int i=0; i<5; i++){
		gris[i]= EEPROM.read( location+i);
		 
	}		
        for(int i=0; i<5; i++){
		gris[i]+= (EEPROM.read( location+i+5))<<8; 
	}		
	
	location = 0x40;
	for(int i=0; i<5; i++){
		rojo[i]= EEPROM.read( location+i);
		 
	}		
        for(int i=0; i<5; i++){
		rojo[i]+= (EEPROM.read( location+i+5))<<8; 
	}		

	location = 0x50;
	for(int i=0; i<5; i++){
		blanco[i]= EEPROM.read( location+i);		
		 
	}
        for(int i=0; i<5; i++){
		blanco[i]+= (EEPROM.read( location+i+5))<<8; 
	}		
	
}
