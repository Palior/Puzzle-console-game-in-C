#include <stdio.h>
#include <stdlib.h>

//funciones que se utilizan a lo largo del programa


void leer(char* nombreArchivo, char ** destino){
	char linea[29];
	FILE * imagen; 
	imagen = fopen(nombreArchivo, "r");
	int i=0;
	while(fgets(linea, 225, (FILE*) imagen)) {
		int j=0;
		while(j<29){
			destino[i][j]=linea[j];
			j++;
		}
		i++;
	}
	fclose(imagen);
}

void borrarEspacios(char ** imagen, char ** nuevaImagen){

	int fila=0;
	while(fila<15){
		int columna=0;
		while(columna<15){
			if(columna==0){
				nuevaImagen[fila][columna]=imagen[fila][columna];
			}else{
				nuevaImagen[fila][columna]=imagen[fila][(2*columna)+1];
			}columna++;
		}fila++;
	}
}



//funcion que imprime por pantalla el puzzle y guarda la posicion de la casilla faltante
//entradas: char doble puntero que contiene el puzzle que se esta resolviendo, y las variables posicion de x
//muestra en pantalla el puzzle y guarda la posicion
void mostrarPantalla(char ** imagen){
	printf("\n\n");
	int fila=0;
	while(fila<15){
		int columna=0;
		while(columna<15){
			printf("%c", imagen[fila][columna]);
			columna++;
		}
		printf("\n");
		fila++;
	}printf("\n\n");
}


//funcion que asigna numeros a los movimientos, siendo el 1 subir, 2 bajar, 3 izquierda, 4 derecha
//entrada: recibe un char de un elemento que contiene el moviemiento
//salida: retorna el equivalente del movimiento en un numero
int asignarNumero(char opcion){
	if(opcion=='S'||opcion=='s'){
		return 1;
	}if(opcion=='B'||opcion=='b'){
		return 2;
	}if(opcion=='I'||opcion=='i'){
		return 3;
	}if(opcion=='D'||opcion=='d'){
		return 4;
	}if(opcion=='F'||opcion=='f'){
		exit();
	}return 5;
}




//FUNCIONES COMPARTIDAS POR AUTOMATICO Y JUGADOR


//funcion que comprueba si se puede realizar el movimiento de la izquierda
int comprobarIzq(int posY){
	if(posY==0){
		return 0;
	}
	return 1; 
}

//funcion que comprueba si se puede realizar el movimiento de la derecha
int comprobarDer(int posY){
	if(posY==28){
		return 0;
	}
	return 1; 
}

//funcion que comprueba si se puede realizar el movimiento de arriba
int comprobarArr(int posX){
	if(posX==0){
		return 0;
	}
	return 1; 
}

//funcion que comprueba si se puede realizar el movimiento de abajo
int comprobarAb(int posX){
	if(posX==14){
		return 0;
	}
	return 1; 
}

//funcion que pide al usuario el movimiento a realizar
//entrada: recibe la posicion de la x, tanto la fila como la columna
//salida: retorna el movimiento escogido por el usuario en forma de la inicial del movimiento, si no es valida la opcion es una N
int pedirMov(int posX, int posY){
	char opcion; //la opcion escogida se guarda en esta variable
	if(comprobarIzq(posY)==0){ //si la x esta en la primera columna
		printf("\nD - Derecha\n");  //se imprime derecha, ya que al ser la primera columna siempre tendra esta opcion
		if(comprobarArr(posX)==0){  //si es la primera fila
			printf("B - Bajar\n");  //se imprime la opcion opuesta
			printf("\nF - Salir del programa\n\n\n");
			scanf("%c%*c", &opcion);  //recibe la opcion, excluyendo el salto de linea con %*c porque sino genera un problema en 
			if(opcion!='D' && opcion!='d' && opcion!='B' && opcion!='b' && opcion!='F' && opcion!='f'){ //el funcionamiento de la funcion
				printf("Opcion no valida\n\n");
				opcion='N';
			}
			return asignarNumero(opcion);
		}if(comprobarAb(posX)==0){ //si es la ultima fila
			printf("S - Subir\n");  //se repite lo del primer segmento en los siguientes pasos
			printf("\nF - Salir del programa\n\n");   
			scanf("%c%*c", &opcion);
			if(opcion!='D' && opcion!='d' && opcion!='S' && opcion!='s' && opcion!='F' && opcion!='f'){
				printf("Opcion no valida\n\n");
				opcion='N';
			}
			return asignarNumero(opcion);
		}printf("S - Subir\n");  //si no es ni la primera ni ultima fila, aun perteneciendo a la primera columna
		printf("B - Bajar\n");
		printf("\nF - Salir del programa\n\n\n");   
		scanf("%c%*c", &opcion);
		if(opcion!='D' && opcion!='d' && opcion!='S' && opcion!='s' && opcion!='B' && opcion!='b' && opcion!='F' && opcion!='f'){
			printf("Opcion no valida\n\n");
				opcion='N';
		}
		return asignarNumero(opcion);
	}else if(comprobarDer(posY)==0){ //si es ultima columna
		printf("\nI - izquierda\n");
		if(comprobarArr(posX)==0){  //primera fila
			printf("B - Bajar\n");
			printf("\nF - Salir del programa\n\n\n");   
			scanf("%c%*c", &opcion);
			if(opcion!='I' && opcion!='i' && opcion!='B' && opcion!='b' && opcion!='F' && opcion!='f'){
				printf("Opcion no valida\n\n");
				opcion='N';
			}
			return asignarNumero(opcion);
		}if(comprobarAb(posX)==0){  //ultima fila
			printf("S - Subir\n");
			printf("\nF - Salir del programa\n\n\n");   
			scanf("%c%*c", &opcion);
			if(opcion!='I' && opcion!='i' && opcion!='S' && opcion!='s' && opcion!='F' && opcion!='f'){
				printf("Opcion no valida\n\n");
				opcion='N';
			}
			return asignarNumero(opcion);
		}printf("S - Subir\n");  //ni primer ni ultima fila pero si ultima columna
		printf("B - Bajar\n");
		printf("\nF - Salir del programa\n\n\n");   
		scanf("%c%*c", &opcion);
		if(opcion!='I' && opcion!='i' && opcion!='S' && opcion!='s' && opcion!='B' && opcion!='b' && opcion!='F' && opcion!='f'){
			printf("Opcion no valida\n\n");
				opcion='N';
		}
		return asignarNumero(opcion);
	}else if(comprobarArr(posX)==0){  //primera fila, sin ser primera ni ultima columna
		printf("B - Bajar\n");
		printf("I - Izquierda\n");
		printf("D - Derecha\n");
		printf("\nF - Salir del programa\n\n\n");   
		scanf("%c%*c", &opcion);
		if(opcion!='I' && opcion!='i' && opcion!='D' && opcion!='d' && opcion!='B' && opcion!='b' && opcion!='F' && opcion!='f'){
			printf("Opcion no valida\n\n");
				opcion='N';
		}
		return asignarNumero(opcion);
	}else if(comprobarAb(posX)==0){  //ultima fila, sin ser primera ni ultima columna
		printf("S - Subir\n");
		printf("I - Izquierda\n");
		printf("D - Derecha\n");
		printf("\nF - Salir del programa\n\n\n");   
		scanf("%c%*c", &opcion);
		if(opcion!='I' && opcion!='i' && opcion!='D' && opcion!='d' && opcion!='S' && opcion!='s' && opcion!='F' && opcion!='f'){
			printf("Opcion no valida\n\n");
				opcion='N';
		}
		return asignarNumero(opcion);
	}printf("S - Subir\n");  //si no es ninguna de los casos anteriores se dan todas las opciones
	printf("B - Bajar\n");
	printf("I - Izquierda\n");
	printf("D - Derecha\n");
	printf("\nF - Salir del programa\n\n\n");   
	scanf("%c%*c", &opcion);
	if(opcion!='I' && opcion!='i' && opcion!='D' && opcion!='d' && opcion!='B' && opcion!='b' && opcion!='S' && opcion!='s' && opcion!='F' && opcion!='f'){
		printf("Opcion no valida\n\n");
		opcion='N';
	}
	return asignarNumero(opcion);
}


void moverPersonaje(int posX, int posY, char ** piso){
	int jugar=0;
	while(jugar==0){
		int movimiento=5;
		while(movimiento==5){
			movimiento=pedirMov(posX, posY);
		}

		if(movimiento==1){
			piso[posX-1][posY]=piso[posX][posY];
			piso[posX][posY]='_';
		}else if(movimiento==2){
			piso[posX+1][posY]=piso[posX][posY];
			piso[posX][posY]='_';
		}else if(movimiento==3){
			piso[posX][posY-1]=piso[posX][posY];
			piso[posX][posY]='_';
		}else if(movimiento==4){
			piso[posX][posY+1]=piso[posX][posY];
			piso[posX][posY-1]='_';
		}else if(movimiento==0){
			jugar=4;
		}
		mostrarPantalla(piso);
	}
}


int main(){
	//piso1
	char ** piso1 = (char **)malloc(sizeof(char*)*(15));
		for (int k = 0; k < 29; ++k){
			piso1[k]= (char *)malloc(sizeof(char*)*(29));
		}
	leer("piso1.in", piso1);
	
	char ** uno = (char **)malloc(sizeof(char*)*(15));
		for (int k = 0; k < 15; ++k){
			uno[k]= (char *)malloc(sizeof(char*)*(15));
		}
		
	borrarEspacios(piso1,uno);
	mostrarPantalla(uno);
	

	char ** piso2 = (char **)malloc(sizeof(char*)*(15));
		for (int k = 0; k < 29; ++k){
			piso2[k]= (char *)malloc(sizeof(char*)*(29));
		}
	leer("piso2.in", piso2);

	
	char ** piso3 = (char **)malloc(sizeof(char*)*(15));
		for (int k = 0; k < 29; ++k){
			piso3[k]= (char *)malloc(sizeof(char*)*(29));
		}
	leer("piso3.in", piso3);

	
	moverPersonaje(15, 9, piso1);


	return 0;
}
