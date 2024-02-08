
#include <stdlib.h>
#include "tiempo.h"
#include "imprimeTiempos.h"
#include <pthread.h>
#define false 0

void* BusquedaSecuencial(void* args);

int main(int argc,char **argv){
  int Hilo_actual=0, encontrado = 0,tama=0, Hilos=0,clave;
  int* Dato;
	tama=atoi(argv[1]);
 	Hilos=atoi(argv[2]);
	clave=atoi(argv[3]);
	Dato=(int*)calloc(tama,sizeof(int));//Crea el arreglo de numeros
	for(int i=0;i<tama;i++){
		scanf("%d",Dato+i);
	}
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	pthread_t *arregloH;//arreglo para la identificacion de los threads
	arregloH = (pthread_t*)malloc(Hilos*sizeof(pthread_t));//Crea el arreglo de threds
	for (int i = 0; i < Hilos; i++){
		pthread_create(&arregloH[i], NULL, BusquedaSecuencial, (void*)NULL); // se asigna una rutina a cada hilo
	}
	for (int i = 0; i < Hilos; i++) {
    pthread_join(arregloH[i], NULL); // se comenza la rutina
	}
	uswtime(&utime1, &stime1, &wtime1);
	if (encontrado==1) {
		printf("Valor encontrado\n");
	} else {
		printf("Valor NO encontrado\n");
	}
	//
	double RealTime = wtime1 - wtime0;	
	double UserTime = utime1 - utime0;	
	double SysTime  = stime1 - stime0;
	bool encontrar = false;
	//
	imprimeTiempos(encontrar, clave,  tama, RealTime, UserTime, SysTime);
	free(Dato);
}


void* BusquedaSecuencial(void* args){
  int Hilo_actual=0, encontrado = 0,tama=0, Hilos=0,key;
  int* Dato;

  int InicioSeccion=Hilo_actual*(tama / Hilos);
  Hilo_actual++;
  int FinSeccion=Hilo_actual*(tama / Hilos);

  for (int i = InicioSeccion;i <FinSeccion; i++){
      if (Dato[i] == key)
          encontrado = 1;
  }
}
