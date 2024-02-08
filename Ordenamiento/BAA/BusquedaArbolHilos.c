/*
		t es el número de hilos
		k es el valor a buscar
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "time.h"
#include "imprimeTiempos.h"

typedef struct nodo									
{
	struct nodo *izquierda, *derecha;
	int numero;
}nodo;


typedef nodo* posicion;												
typedef posicion arbol_bin;	
bool encontrar = false;
int* Dato;
int Tama = 0, nHilos = 0, clave = 0;


arbol_bin mainTree;


void Iniziar(arbol_bin *ArbolBinario);
void Insertar(arbol_bin * ArbolBinario, int nuevo_numero);
void Auxiliar(posicion aux[], arbol_bin * ArbolBinario, int n);
void Destruir(arbol_bin *ArbolBinario);
void * BusquedaArbol(void *root);



int main(int argc, char const *argv[])
{
	if (argc < 4) exit(0);	// Verificación sencilla
	
	Tama = atoi(argv[1]);	// Identifica el número de datos sobre los que se va a trabajar
	nHilos = atoi(argv[2]);	// Toma el número de hilos a trabajar
	clave = atoi(argv[3]);	// Asigna el número que se va a buscar

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

	posicion aux[nHilos];	// Arreglo de posiciones a partir de las cuales se realizará la búsqueda
	for (int i = 0; i < nHilos; ++i)
	{
		aux[i] = NULL;
	}

	Auxiliar(aux, &mainTree, nHilos);



	// En caso de que el número se encuentre en la raíz o en sus dos hijos, no iniciamos las búsquedas
	if(!encontrar){	
		pthread_t *aThreads;	// Declaramos un arreglo de hilos
		aThreads = (pthread_t*) malloc(nHilos*sizeof(pthread_t));	// Inicialización del arreglo de hilos

		for (int i = 0; i < nHilos; ++i)
		{
			pthread_create(&aThreads[i], NULL, BusquedaArbol, (void*)aux[i]);// Crear los hilos con el comportamiento "segmentar"
		}

		for (int i = 0; i < nHilos; ++i)
		{
			pthread_join(aThreads[i], NULL);	// Se verifica la finalización de todos los hilos
		}

		free(aThreads);	// Liberamos el arreglo de hilos
	}

	uswtime(&utime1, &stime1, &wtime1);		// Finalizamos los contadores de tiempo
	
	double RealTime = wtime1 - wtime0;	
	double UserTime = utime1 - utime0;	
	double SysTime  = stime1 - stime0;	

	imprimeTiempos(encontrar, clave, Tama, RealTime, UserTime, SysTime); // Función que mostrará los resultados

	free(Dato);	// Liberamos el arreglo de números

	Destruir(&mainTree);	// Destruimos el ABB usado

	return 0;
}



void * BusquedaArbol(void *root){

	posicion aux = (posicion)root;	// Posición auxiliar que nos permitirá movernos en el ABB

	while(aux != NULL && !encontrar){ // Iteración que durará hasta que ya no haya elementos donde buscar o se haya encontrado el número en otro hilo

		if(aux->numero == clave){	// En caso de encontrar el número
			encontrar = true;	// Indicamos que fue encontrado
		}

		if(aux->numero > clave){	// En caso de que el número en el que estamos sea mayor que el buscado
			aux = aux->izquierda;	// Nos moveremos al subárbol izquierdo
		}
		else{	// En caso contrario
			aux = aux->derecha;	// Nos movemos al subárbol derecho
		}
	}
	pthread_exit(NULL);	// Salimos del hilo
}



void Iniziar(arbol_bin *ArbolBinario){
	*ArbolBinario = NULL;	// El apuntador enviado por el usuario se coloca en un valor NULL
	return;
}


void Insertar(arbol_bin * ArbolBinario, int nuevo_numero){
	arbol_bin * aux = ArbolBinario; 	// Declaramos un apuntador para recorrer el árbol
	while(*aux != NULL){// Recorremos el árbol hasta encontrar el espacio libre donde irá el nuevo elemento
		if (nuevo_numero > ((*aux)->numero))// En caso de que el valor sea mayor, iremos a la parte derecha del árbol
		{
			aux = &((*aux)->derecha);
		}
		else{				// Caso contrario, viajaremos a la parte izquierda del árbol
			aux = &((*aux)->izquierda);
		}
	}
	*aux = (nodo *)malloc(sizeof(nodo));	// Una vez ubicados en su lugar, le haremos espacio en memoria al nuevo nodo
	(*aux)->numero = nuevo_numero;// En el nodo colocaremos el número que desea introducir el usuario al árbol
	(*aux)->izquierda = NULL;// Nos aseguramos de que ambos hijos estén apuntando a un valor NULL para evitar errores
	(*aux)->derecha = NULL;
	return;
}

/*
Función que devolverá los subárboles necesarios para iniciar los hilos
*/

void Auxiliar(posicion aux[], arbol_bin * ArbolBinario, int n){

    if((*ArbolBinario)->numero == clave){
		encontrar = true;
		return;
	}
	if(n == 1){
		*aux = *ArbolBinario;
		return;
	}
	if((*ArbolBinario)->izquierda!=NULL){
		Auxiliar(aux,&((*ArbolBinario)->izquierda),n/2);
	}
	if((*ArbolBinario)->derecha!=NULL){
		Auxiliar(aux+n/2,&((*ArbolBinario)->derecha),(n-n/2));
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
