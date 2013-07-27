void guardaColoresEnLaEEPROM(){
	
	int location = 0x10;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, negro[i]);	
	}		
	location = 0x20;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, verde[i]);		
	}		
	location = 0x30;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, gris[i]);	
	}		
	location = 0x40;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, rojo[i]);		 
	}		
	location = 0x50;
	for(int i=0; i<5; i++){
		EEPROM.write( location+i, blanco[i]);		
	}		
}

void cargaColores(){

	int location = 0x10;
	for(int i=0; i<5; i++){
		negro[i]= EEPROM.read( location+i);
		 
	}		
	location = 0x20;
	for(int i=0; i<5; i++){
		verde[i]= EEPROM.read( location+i);
		 
	}		
	location = 0x30;
	for(int i=0; i<5; i++){
		gris[i]= EEPROM.read( location+i);
		 
	}		
	location = 0x40;
	for(int i=0; i<5; i++){
		rojo[i]= EEPROM.read( location+i);
		 
	}		
	location = 0x50;
	for(int i=0; i<5; i++){
		blanco[i]= EEPROM.read( location+i);		
		 
	}
	
}
