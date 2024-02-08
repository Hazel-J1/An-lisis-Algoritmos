
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "time.h"
#include "imprimeTiempos.h"

//VARIABLES GLOBALES
bool encontrar = false;
int* Dato;
int tama = 0, nHilos = 0, clave = 0;




void* BusquedaLineal(void* id);

int main(int argc, char const *argv[])
{
	if (argc < 4) exit(0);	// Verificación sencilla
	
	tama = atoi(argv[1]);	// Identifica el número de datos sobre los que se va a trabajar
	nHilos = atoi(argv[2]);	// Toma el número de hilos a trabajar
	clave = atoi(argv[3]);	// Asigna el número que se va a buscar

	double utime0, stime0, wtime0; 	// Tiempos de inicio
	double utime1, stime1, wtime1;	// Tiempos de finalización

	Dato = (int*)calloc(tama,sizeof(int));	// Inicialización del arreglo para los números

	for (int i = 0; i < tama; ++i){
		scanf("%d", Dato+i);			// Insertamos los números en el arreglo
	}

	uswtime(&utime0, &stime0, &wtime0);		// Iniciamos los contadores de tiempo

	pthread_t *aHilos;
	aHilos = (pthread_t*) malloc(nHilos*sizeof(pthread_t));	// Inicialización del arreglo de hilos

	for (int i = 0; i < nHilos; ++i)
	{
		pthread_create(&aHilos[i], NULL, BusquedaLineal, (void*)i);	// Crear los hilos con el comportamiento "segmentar"
	}

	for (int i = 0; i < nHilos; ++i)
	{
		pthread_join(aHilos[i], NULL);	
	}

	uswtime(&utime1, &stime1, &wtime1);		
	double RealTime = wtime1 - wtime0;	
	double UserTime = utime1 - utime0;	
	double SysTime  = stime1 - stime0;	
	imprimeTiempos(encontrar, clave, tama, RealTime, UserTime, SysTime); // Función que mostrará los resultados

	free(Dato);	// Liberamos el arreglo de números
	free(aHilos);	// Liberamos el arreglo de hilos

	return 0;
}

void* BusquedaLineal(void* id){

	int inicio = (long)id*(tama / nHilos); // DOnde se debe de iniciar la búsqueda
	int fin = ((long)id+1)*(tama / nHilos);	// Indica la posición de la conclusion de bus

	int i = inicio;		
	while(i < fin && !encontrar){// Iteración que recorrerá toda la sección mientras no se haya encontrado el número en los demás hilos
		if (Dato[i] == clave)	// En caso de encontrarlo
		{
			encontrar = true;//se encontró el número a romper la iteración
		}
		i++;
	}
	pthread_exit(NULL);				// Salida del hilo
}


