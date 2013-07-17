void leerValor(){
  int val;
  
   temp[0] = analogRead(s0);
   temp[1] = analogRead(s1);
   temp[2] = analogRead(s2);
   temp[3] = analogRead(s3);  
   temp[4] = analogRead(s4);
}

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
