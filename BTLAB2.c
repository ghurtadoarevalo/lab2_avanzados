#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

result_s *result;
//Función encargada de leer todas las lineas del archivo con el nombre que contenga la variable fp_source_name_1
//Entradas: nombre del archivo a leer
//Salidas: Arreglo de arreglos de strings con los datos leídos del archivo
char** readData(char* fp_source_name_1)
{
  	FILE *fp = NULL;
  	int size = 0;
  	int count = 0;
  	int linesNumber = 0;
  	int lineLen = 1;
  	char* dataFileChar = NULL;
  	char* temp = NULL;
  	char* token = NULL;
  	char** lines = NULL;


  	fp = fopen (fp_source_name_1, "r" );

      if (fp==NULL)
      {
          printf("No existe archivo con nombre: %s, asegurese de que se encuentre en el directorio correcto o exista el archivo.\n", fp_source_name_1);
          exit (1);
      }

  	fseek(fp,0,SEEK_END);
  	size = ftell(fp);
  	rewind(fp);

  	dataFileChar = malloc(sizeof(char)*(size+1));
  	fread(dataFileChar,sizeof(char), size, fp);
  	fclose(fp);

    dataFileChar[size] = '\0';
  	//Se recorre el char* para encontrar la cantidad de palabras
  	for (int i = 0; i < size ; ++i)
  	{
  		  if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
  		  {
  			     linesNumber++;
  		  }
  	}

  	//Se asigna memoria para cada linea dentro del arreglo
  	lines = malloc(sizeof(char*)*(linesNumber+1));

  	//Se asigna memoria para cada linea dentro del arreglo
  	linesNumber = 0;
  	for (int i = 0; i <= size; ++i)
  	 {
    	 	if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
    		{
      			lines[linesNumber] = malloc(sizeof(char)*(lineLen));
      			linesNumber++;
      			lineLen = 1;
    		}

    		else if(dataFileChar[i] != '\n')
    		{
    		    lineLen++;;
    		}
  	}

  	//Se separan las palabras por \n
  	temp = malloc(sizeof(char)*(size+1));
  	strcpy(temp,dataFileChar);

	lines[0] = malloc(sizeof(char)*(size));

  	token = strtok(temp, "\n");
  	while(token != NULL)
  	{
        lines[count+1] = malloc(sizeof(char)*(size));
  		lines[count+1] = token;
        token = strtok(NULL, "\n");
  		count++;
  	}
  	sprintf(lines[0],"%d",count);

    free(dataFileChar);
    return lines;
}
  
//Función encargada de cambiar de lugar la posición de dos ciudades
//Entrada: Lista de ciudades, contador l y contador i, que sirven para identificar qué ciudades se deben intercambiar en la lista.
//Salida: Lista de ciudades con dos ciudades intercambiadas.
void swap(int* a, int l, int i) 
{ 
    int temp = 	a[l]; 
    a[l] = a[i]; 
    a[i] = temp; 
} 
  
//Función encargada de imprimir en pantalla cuando se activa el modo debug, las combinaciones de los caminos entre ciudades que
//se van generando.
//Entrada: Lista de ciudades.
//Salida: Impresión por pantalla al estar en modo debug de las combinaciones de caminos entre ciudades.
void printCurrent(int *road, int r)
{
	#ifdef DEBUG
	printf("\n enter para continuar…\n");
	while(getchar() != '\n');

	for (int i = 0; i < r; ++i)
	{
		if (i + 1 == r)
		{
			printf("%d",road[i] );
		}
		else
		{
			printf(" %d -> ",road[i] );
		}
	}
	printf("\n");

	#endif
}

//Función encargada de escribir la mejor solución en el archivo Salida.out
//Entrada: Combinación de la mejor inversión.
//Salida: Archivo Salida.out con la solución del problema.
void getOutput(result_s *result)
{
    FILE *fp;
    fp=fopen("Salida.out", "w");

    if(fp == NULL)
    {
        printf("Error al crear el archivo %s\n","Salida.out");
        exit(1);
    }

    for (int i = 0; i < result->optionsQuantity; ++i)
	{
		if (i+1 == result->optionsQuantity)
		{
			fprintf(fp,"%d",result->bestOption[i]);
		}

		else
		{
			fprintf(fp,"%d-",result->bestOption[i]);
		}
	}
	fprintf(fp,"\n");

	fprintf(fp,"%d",result->cost);

    fclose(fp);

    free(result->bestOption);
    free(result);
}

//Función encargada de realizar la permutación con backtraking del orden en que se visitarán las ciudades.
//Entrada: Lista de ciudades, contador l y contador i que sirven para identificar qué ciudades se deben intercambiar,
//         además ingresa la matriz de costos.
//Salida: Nada.
void permute(int *road, int l, int r, cities *citiesMatrix) 
{ 
   	int i; 
   	if (l == r)
   	{ 
   		printCurrent(road,r);
   		int temptCost = 0;

   		for (int i = 0; i < r ; ++i)
   	 	{
   	 		if (i+1 < r)
   	 		{
   	 			if (temptCost <= result->cost) 
	   	 		{
	   	 			temptCost += citiesMatrix->cost[road[i]][road[i+1]]; 
	   	 		}

	   	 		else
	   	 		{
	   	 			break;
	   	 		}
   	 		}
   		}
   		temptCost += 2;
   		if (result->cost > temptCost) 
 	    {
 	    	for (int i = 0; i < r; ++i)
 	    	{
 	    		result->bestOption[i] = road[i];
 	    	}
 	    	result->optionsQuantity = r;
 	    	result->cost = temptCost;
 	    }
   		
   	}
   	else
   	{ 
       for (i = l; i < r; i++) 
       { 
        	swap(road,l,i); 
          	permute(road, l+1, r, citiesMatrix); 
          	swap(road,l,i); //backtrack 
       } 
   	} 
} 
//Función encargada de generar el camino con menor costo posible, haciendo uso de la función permutation.
//Entrada: Matriz de costos.
//Salida: entrega una estructura con el mejor camino encontrado y el costo que tiene el realizar este camino.
result_s * backTraking(cities *citiesMatrix)
{
	int* cities = malloc(sizeof(int)*(citiesMatrix->citiesQuantity+1));

	for (int i = 1; i < citiesMatrix->citiesQuantity+1; ++i)
	{
		cities[i-1] = i;
	}		
 
    int n = citiesMatrix->citiesQuantity;

	result = malloc(sizeof(result_s));
   	result->bestOption = malloc(sizeof(int)*citiesMatrix->citiesQuantity);
    result->cost = 99999;
    permute(cities, 0, n, citiesMatrix);

    for (int i = 0; i < citiesMatrix->citiesQuantity+1; ++i)
    {
    	free(citiesMatrix->cost[i]);
    }

    free(citiesMatrix->cost);
    free(citiesMatrix);

    return result; 
}

//Función encargada de generar la matriz de costos entre ciudades.
//Entrada: cantidad de ciudades, cantidad de conexiones entre ciudades y la información leída de entrada.in
//Salida: estructura que contiene la matriz de costos, la cantidad de ciudades y la cantidad de conexiones.
cities* createMatrix(int citiesQuantity,int citiesConnections, char** data)
{

	cities* citiesMatrix = malloc(sizeof(cities));
	citiesMatrix->cost = malloc(sizeof(int*)*citiesQuantity+1);
	citiesMatrix->citiesQuantity = citiesQuantity;
	citiesMatrix->citiesConnections = citiesConnections;

    for (int i = 0; i < citiesMatrix->citiesQuantity+1; ++i)
    {
    	 citiesMatrix->cost[i] = malloc(sizeof(int)*citiesQuantity+1);
    	 for (int j = 0; j < citiesQuantity; ++j)
    	 {
			citiesMatrix->cost[i][j] = 0;
    	 }
    }


    for (int i = 2; i < citiesMatrix->citiesConnections +1 ; ++i)
    {
    	char* token = NULL;
    	int dataInt[] = {0,0,0};
    	char* temp = malloc(sizeof(char)*20);
    	strcpy(temp,data[i]);
   		int count = 0;	
    	token = strtok(temp," ");
	  	while(token != NULL)
	  	{
	  		dataInt[count] = atoi(token);
	  		token = strtok(NULL, " ");
	  		count++;
	  	}
 	   	citiesMatrix->cost[dataInt[0]][dataInt[1]] = dataInt[2];
 	   	citiesMatrix->cost[dataInt[1]][dataInt[0]] = dataInt[2];
    }

    return citiesMatrix;
}

int main(int argc, char const *argv[])
{
	char* fp_source_name;
    char** data;
	fp_source_name = "Entrada.in";

	printf("\n\n <<%s>> \n\n","Bienvenido al laboratorio de backtracking: Vendedor Viajero" );

    printf("\n %s \n","0) Leyendo informacion de Entrada.in");
    data = readData(fp_source_name);

    printf("\n %s \n","1) Generando matriz de costos");
    int citiesConnections = atoi(data[0]);
    int citiesQuantity = atoi(data[1]);
	cities *citiesMatrix = createMatrix(citiesQuantity,citiesConnections, data);

	printf("\n %s \n","2) Generando backtraking para obtener el mejor camino");

	result = backTraking(citiesMatrix);

	printf("\n %s \n","3) Guardando la mejor opcion en Salida.out");
    getOutput(result);
	return 0;
}