/*
Programa que buscará por medio del método Binario o Dicotómico
	gcc -o BusquedaBinaria BusquedaBinaria.c
	./BusquedaBinaria n k < NumerosOrdenados.txt >> Birario.txt
	donde:
		n es el tamaño de la búsqueda
		k es el valor a buscar
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "time.h"
#include "imprimeTiempos.h"

//VARIABLES GLOBALES
bool encontrar = false;
int* Dato;
int tama = 0, clave = 0;


void BusquedaBinaria();


int main(int argc, char const *argv[])
{
	if (argc < 3) exit(0);	// Verificación sencilla
	
	tama = atoi(argv[1]);	// Identifica el número de datos sobre los que se va a trabajar
	clave = atoi(argv[2]);	// Asigna el número que se va a buscar

	double utime0, stime0, wtime0; 	// Tiempos de inicio
	double utime1, stime1, wtime1;	// Tiempos de finalización

	Dato = (int*)calloc(tama,sizeof(int));	

	for (int i = 0; i < tama; ++i){
		scanf("%d", Dato+i);			// Insertamos los números en el arreglo
	}

	uswtime(&utime0, &stime0, &wtime0);		// Iniciamos los contadores de tiempo

	BusquedaBinaria();	

	uswtime(&utime1, &stime1, &wtime1);	
	
	double RealTime = wtime1 - wtime0;	
	double UserTime = utime1 - utime0;	
	double SysTime  = stime1 - stime0;	
	imprimeTiempos(encontrar, clave, tama, RealTime, UserTime, SysTime); // Función que mostrará los resultados

	free(Dato);	// Liberamos el arreglo de números

	return 0;
}



void BusquedaBinaria(){

	int izquierda,derecha,nMid; 
	izquierda = 0;	// Indicamos el lado izquierdo de la sección a manejar
	derecha = tama-1;	// Indicamos el lado derecho de la sección a manejar

	while(derecha >= izquierda){	// Iteración que se detendrá cuando los límites se superen o se encuentre el número en los demás hilos

		nMid = (izquierda+derecha)/2;	// Buscamos la mitad de la sección

		if(Dato[nMid] == clave){	// En caso de encontrar el número en la mitad
			encontrar = true;	// Indicamos que ya se encontró
			return;	// Salimos de la función
		}

		if(Dato[nMid] < clave){	// Si el número del medio es menor al buscado
			izquierda = nMid+1;	// Continuamos la búsqueda del lado derecho de la partición
		}
		else{	// En caso contrario
			derecha = nMid-1;	// Continuamos la búsqueda del lado izquierdo de la partición
		}
	}
}
