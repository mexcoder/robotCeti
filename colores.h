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