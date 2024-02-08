#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "time.h"
#include "imprimeTiempos.h"

//VARIABLES GLOBALES
bool encontrar = false;
int* Dato;
int tama = 0, clave = 0;

void BusquedaLineal();

int main(int argc, char const *argv[])
{
	if (argc < 3) exit(0);	// Verificación sencilla
	
	tama = atoi(argv[1]);	// Identifica el número de datos sobre los que se va a trabajar
	clave = atoi(argv[2]);	// Asigna el número que se va a buscar

	double utime0, stime0, wtime0; 	// Tiempos de inicio
	double utime1, stime1, wtime1;	// Tiempos de finalización

	Dato = (int*)calloc(tama,sizeof(int));	// Inicialización del arreglo para los números

	for (int i = 0; i < tama; ++i){
		scanf("%d", Dato+i);			// Insertamos los números en el arreglo
	}

	uswtime(&utime0, &stime0, &wtime0);		// Iniciamos los contadores de tiempo

	BusquedaLineal(); // Función que realizará la búsqueda

	uswtime(&utime1, &stime1, &wtime1);		// Finalizamos los contadores de tiempo
	
	double RealTime = wtime1 - wtime0;	
	double UserTime = utime1 - utime0;	
	double SysTime  = stime1 - stime0;	
	imprimeTiempos(encontrar, clave, tama, RealTime, UserTime, SysTime); 
	free(Dato);	

	return 0;
}

void BusquedaLineal(){
	for (int i = 0; i < tama; ++i)
	{
		if (Dato[i] == clave)
		{
			encontrar = true;
			return;
		}
	}
}
