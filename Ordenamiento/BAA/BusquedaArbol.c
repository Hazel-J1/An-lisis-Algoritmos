#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "time.h"
#include "imprimeTiempos.h"


bool encontrar = false;
int* Dato;
int Tama = 0, clave = 0;


typedef struct nodo															// Nuestro nodo del árbol contendrá hijo izquierdo, derecho y un número entero
{
	struct nodo *izquierda, *derecha;
	int numero;
}nodo;

//DEFINICIONES DE SINÓNIMOS
typedef nodo* posicion;														// La posición será la dirección hacia un nodo específico
typedef posicion arbol_bin;	

arbol_bin mainTree;	
void Auxiliar(posicion aux[], arbol_bin * ArbolBinario, int n);
void Insertar(arbol_bin * ArbolBinario, int nuevo_numero);
void Iniziar(arbol_bin *ArbolBinario);
void Destruir(arbol_bin *ArbolBinario);
void BusquedaArbol();

int main(int argc,char **argv){
	if (argc < 3) exit(0);	// Verificación sencilla
	
	Tama = atoi(argv[1]);	// Identifica el número de datos sobre los que se va a trabajar
	clave = atoi(argv[2]);	// Asigna el número que se va a buscar

	double utime0, stime0, wtime0; 	// Tiempos de inicio
	double utime1, stime1, wtime1;	// Tiempos de finalización

	Dato = (int*)calloc(Tama,sizeof(int));	// Inicialización del arreglo para los números

	for (int i = 0; i < Tama; ++i){
		scanf("%d", Dato+i);			// Insertamos los números en el arreglo
	}

	Iniziar(&mainTree);	// Iniciamos nuestro ABB para usarlo

	for(int i = 0; i < Tama; ++i){
		Insertar(&mainTree, Dato[i]);	// Insertamos los datos en el ABB
	}

	uswtime(&utime0, &stime0, &wtime0);		// Iniciamos los contadores de tiempo

	BusquedaArbol();	// Función que realiza la búsqueda

	uswtime(&utime1, &stime1, &wtime1);		// Finalizamos los contadores de tiempo
	
	double RealTime = wtime1 - wtime0;	
	double UserTime = utime1 - utime0;	
	double SysTime  = stime1 - stime0;	
	imprimeTiempos(encontrar, clave, Tama, RealTime, UserTime, SysTime); 
	free(Dato);	

	Destruir(&mainTree);	
}


void BusquedaArbol(){

	posicion aux = mainTree;	// Posición auxiliar que nos permitirá movernos en el ABB

	while(aux != NULL){	// Iteración que durará hasta que ya no haya elementos donde buscar

		if(aux->numero == clave){	// En caso de encontrar el número
			encontrar = true;	// Indicamos que fue encontrado
			return;	// Terminamos la función
		}

		if(aux->numero > clave){	// En caso de que el número en el que estamos sea mayor que el buscado
			aux = aux->izquierda;	// Nos moveremos al subárbol izquierdo
		}
		else{	// En caso contrario
			aux = aux->derecha;	// Nos movemos al subárbol derecho
		}
	}
}

void Iniziar(arbol_bin *ArbolBinario){
	*ArbolBinario = NULL;														// El 
	return;
}

/*
arbol_bin * ArbolBinario (apuntador al ABB utilizado por el Usuario), 
*/

void Insertar(arbol_bin * ArbolBinario, int nuevo_numero){//a incluir
	arbol_bin * aux = ArbolBinario; 											 
	while(*aux != NULL){		// Recorremos el árbol hasta encontrar el espacio libre donde irá el nuevo elemento
		if (nuevo_numero > ((*aux)->numero))	// Si es mayor va a la derecha del arbol
		{
			aux = &((*aux)->derecha);
		}
		else{							
			aux = &((*aux)->izquierda);
		}
	}
	*aux = (nodo *)malloc(sizeof(nodo));	//  espacio en memoria al nuevo nodo
	(*aux)->numero = nuevo_numero;
	(*aux)->izquierda = NULL;		
	(*aux)->derecha = NULL;
	return;
}

/*
Función que devolverá los subárboles necesarios para iniciar los hilos
*/
void auxiliar(posicion aux[], arbol_bin * ArbolBinario, int n){

    if((*ArbolBinario)->numero == clave){
		encontrar = true;
		return;
	}
	if(n == 1){
		*aux = *ArbolBinario;
		return;
	}
	if((*ArbolBinario)->izquierda!=NULL){
		auxiliar(aux,&((*ArbolBinario)->izquierda),n/2);
	}
	if((*ArbolBinario)->derecha!=NULL){
		auxiliar(aux+n/2,&((*ArbolBinario)->derecha),(n-n/2));
	}
}

void Destruir(arbol_bin *ArbolBinario){
	if(*ArbolBinario == NULL)											
		return;
	else
	{
		if((*ArbolBinario)->izquierda != NULL)									
			Destruir(&((*ArbolBinario)->izquierda));		
		if((*ArbolBinario)->derecha != NULL)		
			Destruir(&((*ArbolBinario)->derecha));		
		free(*ArbolBinario);			
		return;
	}
}
