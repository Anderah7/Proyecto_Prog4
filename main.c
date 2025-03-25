#include <stdio.h>
#include "operaciones.h"
#include "sqlite3.h"
#include <stdlib.h>

int main (void){

	Departamento departamentos[100];
	Empleado empleados[100];
	Producto productos[100];
	Proveedor proveedores[100];
	Seccion secciones[100];


	leerFicheros(departamentos, empleados, productos, proveedores, secciones);

	sqlite3 * db;
	int abrir = sqlite3_open("adate.db", &db);

	if (abrir) {
	    printf("Error al conectar a la bd: %s\n", sqlite3_errmsg(db));
	    return abrir;
	} else {
	    printf("Conectado a la bd\n");
	}

	crearTablas(db);

	insertarDepartamentos(db, departamentos);
	insertarEmpleados(db, empleados);
	insertarProductos(db, productos);
	insertarProveedores(db, proveedores);
	insertarSecciones(db, secciones);

	//Array de productos
	//Producto *productos = NULL;
	int num_productos = mostrarProductos(db, &productos);

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
		    printf("Seleccione una opción: ");
		    fflush(stdout);
		    scanf(" %c", &opcion);

		    if(opcion == '1') {
		    	for (int i = 0; i < num_productos; ++i) {
		    		printf("ID: %d, Nombre: %s, Precio: %.2f, Proveedor: %d, Seccion: %d\n", productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);
		        }
		    }
		    else if(opcion == '2') {

		    }
		    else if(opcion == '3') {

		    }
		    else if(opcion == '4') {
		    	qsort(productos, num_productos, sizeof(Producto), compararPorPrecio);
		    }
		    else if(opcion == '5') {
		    	ordenarEstante(productos, num_productos, &productosEstante, &num_secciones, &seccionesEstante);
		    	mostrarProductosEstante(productosEstante, seccionesEstante, num_secciones);
		    	liberarMemoria(productosEstante, num_secciones);
		    	free(seccionesEstante);

		    }

		    } while (opcion != 'q');

	sqlite3_close(db);




}

