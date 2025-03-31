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
	Producto producto;

	producto.idProd = obtenerIdUltimoProducto(db) + 1;

	printf("Introduce el nombre del producto: ");
	fflush(stdout);
	scanf("%s", producto.nombreProd);

	printf("Introduce el precio del producto: ");
	fflush(stdout);
	scanf("%f", &producto.precio);

	printf("Introduce la seccion del producto: ");
	fflush(stdout);
	scanf("%i", &producto.codSeccion);

	while (producto.codSeccion < 1 || producto.codSeccion > 6) {
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
		scanf("%i", &producto.codSeccion);
			   }
	printf("Proveedor del producto: ");
	fflush(stdout);
	scanf("%i", &producto.codProveedor);

	while (producto.codProveedor < 1 || producto.codProveedor > 6) {
		printf("Ese departamento no existe\n");
		printf("Los separtamentos disponibles son:\n");
		printf("1: Proveedor limpieza\n");
		printf("2: Proveedor congelados\n");
		printf("3: Proveedor carniceria\n");
		printf("4: Proveedor pescaderia\n");
		printf("5: Proveedor cereales\n");
		printf("6: Proveedor electrodomesticos\n");
		printf("Introduce el departamento del producto:\n");
		fflush(stdout);
		scanf("%i", &producto.codProveedor);
	};

	insertarProducto(db, producto);
	imprimirProducto(producto);

}
