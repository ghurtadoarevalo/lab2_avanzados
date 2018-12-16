#ifndef STRUCTS_H
#define STRUCTS_H

//Estructura que se utiliza para almacenar la matriz de costos
typedef struct {
	int** cost;
	int citiesQuantity;
	int citiesConnections;
} cities;

//Estructura que se utiliza para almacenar la mejor ruta.
typedef struct {
	int* bestOption;
	int optionsQuantity;
	int cost;
} result_s;

typedef enum { false, true } bool;

#endif
