#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "struct.h"

//Función encargada de leer todas las lineas del archivo con el nombre que contenga la variable fp_source_name_1
//Entradas: nombre del archivo a leer
//Salidas: Arreglo de arreglos de strings con los datos leídos del archivo
char** readData(char* fp_source_name_1);

//Función encargada de cambiar de lugar la posición de dos ciudades
//Entrada: Lista de ciudades, contador l y contador i, que sirven para identificar qué ciudades se deben intercambiar en la lista.
//Salida: Lista de ciudades con dos ciudades intercambiadas.
void swap(int* a, int l, int i);

//Función encargada de imprimir en pantalla cuando se activa el modo debug, las combinaciones de los caminos entre ciudades que
//se van generando.
//Entrada: Lista de ciudades.
//Salida: Impresión por pantalla al estar en modo debug de las combinaciones de caminos entre ciudades.
void printCurrent(int *road, int r);

//Función encargada de escribir la mejor solución en el archivo Salida.out
//Entrada: Combinación de la mejor inversión.
//Salida: Archivo Salida.out con la solución del problema.
void getOutput(result_s *result);

//Función encargada de realizar la permutación con backtraking del orden en que se visitarán las ciudades.
//Entrada: Lista de ciudades, contador l y contador i que sirven para identificar qué ciudades se deben intercambiar,
//         además ingresa la matriz de costos.
//Salida: Nada.
void permute(int *road, int l, int r, cities *citiesMatrix);

//Función encargada de generar el camino con menor costo posible, haciendo uso de la función permutation.
//Entrada: Matriz de costos.
//Salida: entrega una estructura con el mejor camino encontrado y el costo que tiene el realizar este camino.
result_s * backTraking(cities *citiesMatrix);

//Función encargada de generar la matriz de costos entre ciudades.
//Entrada: cantidad de ciudades, cantidad de conexiones entre ciudades y la información leída de entrada.in
//Salida: estructura que contiene la matriz de costos, la cantidad de ciudades y la cantidad de conexiones.
cities* createMatrix(int citiesQuantity,int citiesConnections, char** data);


#endif
