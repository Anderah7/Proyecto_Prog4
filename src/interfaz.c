/*
 * interfaz.c
 *
 *  Created on: 31 mar 2025
 *      Author: a.azcorra
 */
#include <stdio.h>
#include "../includes/operaciones.h"
#include "../includes/initDatabase.h"
#include "../includes/GestorDB.h"
#include "../libs/sqlite3.h"
#include "../includes/interfaz.h"
#include "../includes/estructuras.h"
#include <stdlib.h>

void interfazAnadirProducto(sqlite3 *db){
	char nomProd[30];
	float precio;
	int codSec = 200;
	int codDep = 200;

	printf("Introduce el nombre del producto: ");
	fflush(stdout);
	scanf("%s", nomProd);

	printf("Introduce el precio del producto: ");
	fflush(stdout);
	scanf("%f", &precio);

	printf("Introduce la seccion del producto: ");
	fflush(stdout);
	scanf("%i", &codSec);

	while (codSec < 1 || codSec > 5) {
	printf("Esa seccion no existe\n");
	printf("Las secciones disponibles son:\n");
	printf("1: limpieza\n");
	printf("2: congelados\n");
	printf("3: carniceria\n");
	printf("4: pescaderia\n");
	printf("5: cereales\n");
	printf("6: electrodomesticos\n");
	printf("Introduce la seccion del producto:\n");
	fflush(stdout);
	scanf("%i", &codSec);
			    	    }
	printf("Departamento del producto: ");
	fflush(stdout);
	scanf("%i", &codDep);

		while (codDep < 1 || codDep > 3) {
			printf("Ese departamento no existe\n");
			printf("Los separtamentos disponibles son:\n");
			printf("1: limpieza\n");
			printf("2: comida\n");
			printf("3: Electrodomesticos\n");
			printf("Introduce el departamento del producto:\n");
			fflush(stdout);
			scanf("%i", &codDep);
	};

	anadirProducto(db, nomProd, precio, codSec, codDep);

}
