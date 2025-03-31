#include <stdio.h>
#include "../includes/operaciones.h"
#include "../includes/initDatabase.h"
#include "../includes/GestorDB.h"
#include "../libs/sqlite3.h"
#include <stdlib.h>

int main (void){

	Departamento departamentos[100];
	Empleado empleados[100];
	Producto productos[200];
	Proveedor proveedores[100];
	Seccion secciones[100];

	//no usar estos contadores para mostrar datos de la base de datos, usar la funcion "obtenerIdUltimoProducto" para sacar el numero de productos
	int contDep = 0;
	int contEmp = 0;
	int contProd = 0;
	int contProv = 0;
	int contSec = 0;

	leerFicheros(departamentos, empleados, productos, proveedores, secciones, &contDep, &contEmp, &contProd, &contProv, &contSec);

	sqlite3 * db;
	int abrir = sqlite3_open("database/adate.db", &db);

	if (abrir) {
	    printf("Error al conectar a la bd: %s\n", sqlite3_errmsg(db));
	    return abrir;
	} else {
	    printf("Conectado a la bd\n");
	}

	dropTables(db);
	crearTablas(db);

	insertarDepartamentos(db, departamentos, contDep);
	insertarEmpleados(db, empleados, contEmp);
	insertarProductos(db, productos, contProd);
	insertarProveedores(db, proveedores, contProv);
	insertarSecciones(db, secciones, contSec);

	//Array de productos
	Producto *productosCarga = NULL;
	int num_productos = mostrarProductos(db, &productosCarga);

	//Para la funcion ordenar
	Producto **productosEstante;
	int num_secciones;
	int *seccionesEstante;


	char opcion;

		do {
			printf("Bienvenido al gestor de productos\n");
		    printf("1. Mostrar productos\n");
		    printf("2. Añadir productos\n");
		    printf("3. Eliminar producto\n");
		    printf("4. Ordenar productos\n");
		    printf("5. Ver estanteria\n");
		    printf("Pulsar 'q' para salir\n");
		    printf("Seleccione una opción:\n");
		    fflush(stdout);
		    scanf(" %c", &opcion);

		    if(opcion == '1') {
		    	int num_productos = mostrarProductos(db, &productosCarga);
		    	for (int i = 0; i < num_productos; ++i) {
		    		printf("ID: %d, Nombre: %s, Precio: %.2f, Proveedor: %d, Seccion: %d\n", productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);
		        }
		    }
		    else if(opcion == '2') {
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
		    else if(opcion == '3') {
		    	int idProd;
		    	int idMax = obtenerIdUltimoProducto(db);
		    	printf("%i", idMax);

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
		    	num_productos = mostrarProductos(db, &productosCarga);

		    }
		    else if(opcion == '4') {
		    	qsort(productos, num_productos, sizeof(Producto), compararPorPrecio);
		    }
		    else if(opcion == '5') {
		    	int numProds = obtenerIdUltimoProducto(db);
		    	ordenarEstante(productos, numProds, &productosEstante, &num_secciones, &seccionesEstante);
		    	mostrarProductosEstante(productosEstante, seccionesEstante, num_secciones);
		    	liberarMemoria(productosEstante, num_secciones);
		    	free(seccionesEstante);

		    }

		    } while (opcion != 'q');

	sqlite3_close(db);




}

