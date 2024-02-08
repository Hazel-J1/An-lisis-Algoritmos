
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "time.h"
#include "imprimeTiempos.h"

bool encontrar = false;
int* Dato;
int Tama = 0, nHilos = 0, clave = 0;

void * BusquedaBinaria(void *id);

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

	uswtime(&utime0, &stime0, &wtime0);		// Iniciamos los contadores de tiempo

	pthread_t *aHilos;	// Declaramos un arreglo de hilos
	aHilos = (pthread_t*) malloc(nHilos*sizeof(pthread_t));	// Inicialización del arreglo de hilos

	for (int i = 0; i < nHilos; ++i)
	{
		pthread_create(&aThreads[i], NULL, BusquedaBinaria, (void*)i);	// Crear los hilos con el comportamiento "segmentar"
	}

	for (int i = 0; i < nHilos; ++i)
	{
		pthread_join(aHilos[i], NULL);	// Se verifica la finalización de todos los hilos
	}

	uswtime(&utime1, &stime1, &wtime1);	
	
	double RealTime = wtime1 - wtime0;	
	double UserTime = utime1 - utime0;	
	double SysTime  = stime1 - stime0;	
	imprimeTiempos(encontrar, clave, Tama, RealTime, UserTime, SysTime); 
	free(Dato);	
	free(aHilos);	

	return 0;
}


void * BusquedaBinaria(void *id){

	int izquierda,derecha,nMid; // Tres variables que nos permitirán movernos por el arreglo

	izquierda = (long)id*(Tama / nHilos);	// Indicamos el lado izquierdo de la sección a manejar
	derecha = ((long)id+1)*(Tama / nHilos);	// Indicamos el lado derecho de la sección a manejar

	while(derecha>=izquierda && !encontrar){	
		nMid=(izquierda+derecha)/2;	// Buscamos la mitad de la sección
		if(Dato[nMid]==clave){	// En caso de encontrar el número en la mitad
			encontrar=true;	// Indicamos que ya se encontró
		}
		if(Dato[nMid]<clave){	// Si el número del medio es menor al buscado
			izquierda=nMid+1;	//búsqueda del lado derecho de la partición
		}
		else{	
			derecha=nMid-1;	//búsqueda del lado izquierdo de la partición
		}
	}
	pthread_exit(NULL);
}

