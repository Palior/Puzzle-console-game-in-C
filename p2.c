#include <stdio.h>
#include <stdlib.h>

//funciones que se utilizan a lo largo del programa
typedef struct personajes jugador;

struct personajes{
	int fil;
	int col;
	int idEstado;
	int estadoAnterior;
	char * nombre;
	char * transicion;
};
//Declaración funciones
jugador crearEstado(int fil, int col, int anterior, char * t, char * nombre); 
jugador * agregarEstado(jugador * lista, int * elementos, jugador actual); 
jugador * sacarElemento(jugador * lista, int * elementos); 
int verificarBajar(jugador actual, char** matriz); 
int verificarSubir(jugador actual, char** matriz); 
int verificarIzq(jugador actual, char** matriz); 
int verificarDer(jugador actual, char** matriz); 
jugador bajar(jugador actual, char** matriz); 
jugador subir(jugador actual, char** matriz);
jugador izq(jugador actual, char** matriz);
jugador der(jugador actual, char** matriz);
int esFinal(char** matrizOrd, char** matrizDes, int cant);
int estaEstado(jugador * lista, int elementos, jugador actual);

//Var globales
int correlativo;
int FILAS = 15;
int COLUMNAS = 30;

jugador crearEstado(int fil, int col, int anterior, char * t, char * nombre){
	jugador nuevoEstado;
	nuevoEstado.fil = fil;
	nuevoEstado.col = col;
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.nombre = nombre;
	nuevoEstado.transicion = t;
	correlativo++;
	return nuevoEstado;
}

jugador * agregarEstado(jugador * lista, int * elementos, jugador estado){
	jugador * nuevaLista = (jugador *)malloc(sizeof(jugador)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}
jugador * sacarElemento(jugador * lista, int * elementos){
	jugador * nuevaLista = (jugador *)malloc(sizeof(jugador)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}
/*
Función que verifica si es posible bajar una posición a la pieza que se desea mover
Entrada: El conjunto del estado actual de la pieza
Salida: Un numero entero el cual será 1 si es posible realizar la acción y un 0 si es que no se puede
*/
int verificarBajar(jugador estado, char** matriz){
	if(estado.fil==14)
		return 0;
	if(matriz[estado.fil+1][estado.col]=='X')
		return 0;
	return 1;
}
/*
Función que verifica si es posible subir una posición a la pieza que se desea mover
Entrada: El conjunto del estado actual de la pieza
Salida: Un numero entero el cual será 1 si es posible realizar la acción y un 0 si es que no se puede
*/
int verificarSubir(jugador estado, char** matriz){
	if(estado.fil==0)
		return 0;
	if(matriz[estado.fil-1][estado.col]=='X')
		return 0;
	return 1;
}
/*
Función que verifica si es posible mover hacia la izquierda a la pieza que se desea mover
Entrada: El conjunto del estado actual de la pieza
Salida: Un numero entero el cual será 1 si es posible realizar la acción y un 0 si es que no se puede
*/
int verificarIzq(jugador estado, char** matriz){
	if(estado.col==0)
		return 0;
	if(matriz[estado.fil][estado.col-1]=='X')
		return 0;
	return 1;
}
/*
Función que verifica si es posible mover hacia la derecha a la pieza que se desea mover
Entrada: El conjunto del estado actual de la pieza
Salida: Un numero entero el cual será 1 si es posible realizar la acción y un 0 si es que no se puede
*/
int verificarDer(jugador estado, char** matriz){
	if(estado.col==14)
		return 0;
	if(matriz[estado.fil][estado.col+1]=='X')
		return 0;
	return 1;
}
jugador bajar(jugador actual, char** matriz){
	char x = 'J';
	int i = 0;
	if(matriz[actual.fil][actual.col] == 'I'){
		matriz[actual.fil+1][actual.col] = x;
		i = 1;
	}
	if(matriz[actual.fil+1][actual.col] == 'O' || matriz[actual.fil+1][actual.col] == 'I'){
		matriz[actual.fil][actual.col] = '_';
		i = 1;
	}else if(i==0){
		matriz[actual.fil][actual.col] = matriz[actual.fil+1][actual.col];
		matriz[actual.fil+1][actual.col] = x;
	}
	return crearEstado(actual.fil+1, actual.col,actual.idEstado, "Abajo", actual.nombre);
}
jugador subir(jugador actual, char** matriz){
	char x = 'J';
	int i = 0;
	if(matriz[actual.fil][actual.col] == 'I'){
		matriz[actual.fil-1][actual.col] = x;
		i = 1;
	}
	if(matriz[actual.fil-1][actual.col] == 'O' || matriz[actual.fil-1][actual.col] == 'I'){
		matriz[actual.fil][actual.col] = '_';
		i = 1;
	}else if(i==0){
		matriz[actual.fil][actual.col] = matriz[actual.fil-1][actual.col];
		matriz[actual.fil-1][actual.col] = x;
	}
	return crearEstado(actual.fil-1, actual.col,actual.idEstado, "Arriba", actual.nombre);
}
jugador izq(jugador actual, char** matriz){
	char x = 'J';
	int i = 0;
	if(matriz[actual.fil][actual.col] == 'I'){
		matriz[actual.fil][actual.col-1] = x;
		i = 1;
	}
	if(matriz[actual.fil][actual.col-1] == 'O' || matriz[actual.fil][actual.col-1] == 'I'){
		matriz[actual.fil][actual.col] = '_';
		i = 1;
	}else if(i==0){
		matriz[actual.fil][actual.col] = matriz[actual.fil][actual.col-1];
		matriz[actual.fil][actual.col-1] = x;
	}
	return crearEstado(actual.fil, actual.col-1,actual.idEstado, "Izquierda", actual.nombre);
}
jugador der(jugador actual, char** matriz){
	char x = 'J';
	int i = 0;
	if(matriz[actual.fil][actual.col] == 'I'){
		printf("1\n");
		matriz[actual.fil][actual.col+1] = x;
		i = 1;
	}
	if(matriz[actual.fil][actual.col+1] == 'O' || matriz[actual.fil][actual.col+1] == 'I'){
		printf("%d %d\n", actual.fil, actual.col);
		matriz[actual.fil][actual.col] = '_';
		printf("\n%c\n", matriz[actual.fil][actual.col]);
		i = 1;
	}else if(i==0){
		printf("3\n");
		matriz[actual.fil][actual.col] = matriz[actual.fil][actual.col+1];
		matriz[actual.fil][actual.col+1] = x;
	}
	return crearEstado(actual.fil, actual.col+1,actual.idEstado, "Derecha", actual.nombre);
}

char** crearTablero(FILE* file){
    char** matriz = (char**) malloc(sizeof(char*)*FILAS);
    for(int i=0; i<FILAS; i++){
        matriz[i] = (char*) malloc(sizeof(char)*COLUMNAS);
    }
    char buffer;
    for(int i=0; i<FILAS; i++){
        for(int j=0;j<COLUMNAS;j++){
            //fscanf(file,"%c", &buffer);
            buffer = fgetc(file);
            //if (buffer != '\n')
            matriz[i][j]= buffer;
        }
    }
    fclose(file);
    return matriz;
}
void posInicial(char** matriz, int* x, int* y){
	//int pos_x,pos_y;
    for(int i=0; i<15; i++){
        for(int j=0;j<15;j++){
            if(matriz[i][j]=='I'){
            	*x = i;
            	*y = j;
            }
        }
    }
}
void posFinal(char** matriz, int* x, int* y){
	//int pos_x,pos_y;
    for(int i=0; i<15; i++){
        for(int j=0;j<15;j++){
            if(matriz[i][j]=='O'||matriz[i][j]=='0'){
            	*x = i;
            	*y = j;
            }
        }
    }
}
void imprimirTablero(char** matriz){
	printf("\n");
	for(int i=0; i<15; i++){
        for(int j=0;j<15;j++){
            printf("%c", matriz[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n\n");
}

int llegada(jugador actual, char ** matriz, int x, int y){
	if (actual.fil==x && actual.col==y)
		return 1;
	return 0;
}
int estaEstado(jugador * arreglo, int elementos, jugador estado){
	for (int i = 0; i < elementos; ++i){
		if((arreglo[i].fil == estado.fil) && (arreglo[i].col == estado.col))
			return 1;
	}return 0;
}

char** borrarEspacios(char ** imagen){
	char** nuevaImagen = (char**) malloc(sizeof(char*)*15);
    for(int i=0; i<15; i++){
        nuevaImagen[i] = (char*) malloc(sizeof(char)*15);
    }
	int fila=0;
	for (int i=0; i<15; i++){
		int columna=0;
		for(int j=0; j<29; j++){
			if(imagen[i][j]!=' '){
				nuevaImagen[fila][columna]=imagen[i][j];
				columna++;
			}
		}
		fila++;
	}
	return nuevaImagen;
}

int main(){
	system("clear");
	int posInicialX,posInicialY;
	int posFinalX, posFinalY;
	int canAbiertos = 0,canCerrados = 0;
	int m = 0, op;
	correlativo = 0;
	jugador pActual, pSiguiente;
	while(m==0){
		printf("1. Jugar\n");
		printf("2. Salir\n");
		scanf("%d", &op);
    	while(getchar()!='\n');
    	if(op==1){
    		FILE* laberinto = fopen("piso1.in","r");
    		printf("ASJKDJKASDKJAS");
    		char** espacios_laberinto = crearTablero(laberinto);
    		char** m_laberinto = borrarEspacios(espacios_laberinto);
    		printf("El laberinto es el siguiente:\n");
    		imprimirTablero(m_laberinto);
    		posInicial(m_laberinto, &posInicialX, &posInicialY);
    		posFinal(m_laberinto, &posFinalX, &posFinalY);
    		jugador inicial = crearEstado(posInicialX, posInicialY, correlativo, "", "J1");
    		pActual = inicial;
    		pSiguiente = inicial;
    		int t = 0;
    		char ch;
    		while(t==0){

   					pActual = pSiguiente;
   					imprimirTablero(m_laberinto);
   					printf("\nSeleccione un movimiento: \n");
    				if (verificarSubir(pActual, m_laberinto)==1)
    					printf(" -Subir (S)\n");
    				if (verificarBajar(pActual, m_laberinto)==1)
    					printf(" -Bajar (B)\n");
    				if (verificarIzq(pActual, m_laberinto)==1)
    					printf(" -Izquierda (I)\n");
    				if (verificarDer(pActual, m_laberinto)==1)
    					printf(" -Derecha (D)\n");
    				printf(" -Terminar (T)\n");
    				scanf("%c",&ch);
    				while(getchar()!='\n');
    				int i = 0;
    				while(i==0){
    					if(ch == 'S' || ch == 's'){
    						if (verificarSubir(pActual, m_laberinto)==1)
    							pSiguiente = subir(pActual, m_laberinto);
    					}
   						if(ch == 'B' || ch == 'b'){
   							if (verificarBajar(pActual, m_laberinto)==1)
   								pSiguiente = bajar(pActual, m_laberinto);
   						}
   						if(ch == 'I' || ch == 'i'){
   							if (verificarIzq(pActual, m_laberinto)==1)
   								pSiguiente = izq(pActual, m_laberinto);
   						}
   						if(ch == 'D' || ch == 'd'){
   							if (verificarDer(pActual, m_laberinto)==1)
   								pSiguiente = der(pActual, m_laberinto);
   						}
   						if(ch == 'T' || ch == 't'){
   							printf("\nVolviendo al menú inicial..\n");
   							t = 1;
   						}
   						if(ch!='S' && ch!='B' && ch!='I' && ch!='D' && ch!='T' && ch!='V'){
   							if((ch!='s' && ch!='b' && ch!='i' && ch!='d' && ch!='t' && ch!='v'))
   								printf("\nOpción inválida, vuelva a intentar..\n");
   						}
   						i = 1;
    				}
    			printf("\n\n%d   %d\n\n", posFinalX, posFinalY);
    			printf("\n\n%d   %d\n\n", pActual.fil, pActual.col);
   				if (llegada(pActual, m_laberinto, posFinalX, posFinalY)== 1){
    				imprimirTablero(m_laberinto);
   					printf("\nHa completado el laberinto.\n");
   					t = 1;
   				}
    		}
    	}
    	if(op==2){
    		printf("\nEl programa ha finalizado..\n");
	    	m = 1;
    	}
	}

	return 0;
}
