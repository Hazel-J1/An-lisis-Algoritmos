#!/bin/bash   
#Script para la ejecución de las distintas búsquedas
#Arreglo de los diferentes tamaños del arreglo donde se efectuara la busqueda               
TAMANO=(100 1000 5000 10000 50000 100000 200000 400000 600000 800000 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000) 

#Arreglo de los diferentes números a buscar
NUMEROS=(322486 14700764 3128036 6337399 61396 10393545 2147445644 1295390003 450057883 187645041 1980098116 152503 5000 1493283650 214826 1843349527 1360839354 2109248666 2147470852 0)


gcc BusquedaArbol.c -o BusquedaArbol
gccBusquedaArbolHilos.c -o BusquedaArbollHilos -pthread

gcc BusquedaBinaria.c -o BusquedaBinaria
gcc BusquedaBinariaHilos.c -o BusquedaBinariaHilos -pthread

gcc BusquedaLinealHilos.c -o BusquedaExponencialHilos -pthread
gcc BusquedaLineal.c -o Busqueda Lineal

gcc BusquedaExponencialHilos.c -o BusquedaExponencialHilos -pthread		#Secuencial con hilos
gcc BusquedaExponencial.c -o BusquedaExponencial 
			
 
#####################################
echo -e "BUSQUEDA LINEAL SIN HILOS\n" >>BusquedaLineal.txt
for j in {0..19}
do
	for i in {0..19} 
	do 
		./BusquedaLineal "${TAMANO[i]}" "${NUMEROS[j]}" < NumerosOrdenados.txt >>BusquedaLineal.txt
	done
done

#BÚSQUEDA SECUENCIAL CON 2, 3 y 4 HILOS
for k in {2..4}
do
	echo -e "\nBUSQUEDA SECUENCIAL CON '$k' HILOS\n" >>BusquedaLineal.txt
	for j in {0..19}
	do
		for i in {0..19} 
		do 
			./BusquedaLinealHilos "${TAMANO[i]}" $k "${NUMEROS[j]}" < NumerosOrdenados.txt >>BusquedaLineal.txt
		done
	done
done

#BÚSQUEDA BINARIA SIN HILOS
echo -e "BUSQUEDA BINARIA SIN HILOS\n" >>BusquedaBinaria.txt
for j in {0..19}
do
	for i in {0..19} 
	do 
		./BusquedaBinaria "${TAMANO[i]}" "${NUMEROS[j]}" < NumerosOrdenados.txt >>BusquedaBinaria.txt
	done
done

#BÚSQUEDA BINARIA CON 2, 3 y 4 HILOS
for k in {2..4}
do
	echo -e "\nBUSQUEDA BINARIA CON '$k' HILOS\n" >>BusquedaBinaria.txt
	for j in {0..19}
	do
		for i in {0..19} 
		do 
			./BusquedaBinariaHilos "${TAMANO[i]}" $k "${NUMEROS[j]}" < NumerosOrdenados.txt >>BusquedaBinaria.txt
		done
	done
done

#BÚSQUEDA EN ABB SIN HILOS
echo -e "BUSQUEDA ARBOL BINARIO SIN HILOS\n" >>BusquedArbol.txt
for j in {0..19}
do
	for i in {0..19} 
	do 
		./BusquedaArbol "${TAMANO[i]}" "${NUMEROS[j]}" < NumerosDesordenados.txt >>BusquedaArbol.txt
	done
done

#BÚSQUEDA EN ABB CON 2, 3 Y 4 HILOS
for k in {2..4}
do
	echo -e "\nBUSQUEDA ARBOL BINARIO CON '$k' HILOS\n" >>BusquedaArbol.txt
	for j in {0..19}
	do
		for i in {0..19} 
		do 
			./BusquedaArbolHilos "${TAMANO[i]}" $k "${NUMEROS[j]}" < NumerosDesordenados.txt >>BusquedaArbol.txt
		done
	done
done
########################################33
#BÚSQUEDA EXPONENCIAL USANDO 2, 3 Y 4 HILOS
for k in {2..4}
do
	echo -e "\nBusqueda de arbol usando '$k' hilos\n" >>resultados/BusquedaExponencial.txt
	for j in {0..19}
	do
		for i in {0..19} 
		do 
			./BusquedaExponencialHilos "${TAMANO[i]}" $k "${NUMEROS[j]}" < NumerosOrdenados.txt >>resultados/BusquedaExponencial.txt
		done
	done
done




