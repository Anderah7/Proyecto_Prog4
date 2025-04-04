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

void gestionarProductos(sqlite3 *db) {
	char opcion;

			do {
				printf("Bienvenido al gestor de productos\n");
			    printf("1. Mostrar productos\n");
			    printf("2. Añadir productos\n");
			    printf("3. Eliminar producto\n");
			    printf("4. Modificar producto\n");
			    printf("5. Ordenar productos\n");
			    printf("6. Ver estanteria\n");
			    printf("7. Buscar productos\n");
			    printf("Pulsar 'q' para salir\n");
			    printf("Seleccione una opción:\n");
			    fflush(stdout);
			    scanf(" %c", &opcion);

			    if(opcion == '1') {
			    	mostrarProductos(db);

			    }
			    else if(opcion == '2') {
			    	interfazAnadirProducto(db);
			    }
			    else if(opcion == '3') {
			    	interfazEliminarProducto(db);

			    }
			    else if(opcion == '4') {
			    	modificarProducto(db);
			    }
			    else if(opcion == '5') {
			    	mostrarProductosOrden(db);

			    }
			    else if(opcion == '6') {
			    	int numProds = obtenerIdUltimoProducto(db);
			    	//ordenarEstante(productos, numProds, &productosEstante, &num_secciones, &seccionesEstante);
			    	//mostrarProductosEstante(productosEstante, seccionesEstante, num_secciones);
			    	//liberarMemoria(productosEstante, num_secciones);
			    	//free(seccionesEstante);
			    }

			    else if (opcion == '7') {
			        buscarProductos(db);
			    }

			    } while (opcion != 'q');

}


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

void interfazEliminarProducto(sqlite3 *db) {
	int idProd;

	int idMax = 0;
	idMax = obtenerIdUltimoProducto(db);

	printf("Introduce el id del producto a eliminar: \n");
	fflush(stdout);
	scanf("%i", &idProd);

	while(idProd < 1 || idProd > idMax) {
		printf("Este producto no existe\n");
		printf("Los productos disponibles van del 1 al %i\n", idMax);
		printf("Introduce el id del producto a eliminar: \n");
		fflush(stdout);
		scanf("%i", &idProd);
	}

		eliminarProducto(db, idProd);

}


void gestionarEmpleados(sqlite3 * db) {
	char opcion;

	do {
		printf("Bienvenido al gestor de empleados\n");
		printf("1. Mostrar empleados\n");
		printf("2. Añadir empleado\n");
		printf("3. Eliminar empleado\n");
		printf("4. Modificar empleado\n");
		printf("Pulsar 'q' para salir\n");
		printf("Seleccione una opción:\n");
		fflush(stdout);
		scanf(" %c", &opcion);

		if(opcion == '1') {
			printf("1\n");
			mostrarEmpleados(db);

		}
		else if(opcion == '2') {
			printf("2\n");

		}
		else if(opcion == '3') {
			printf("3\n");

		}
		else if(opcion == '4') {
			printf("4\n");

		}
	}
	while (opcion != 'q');


}

