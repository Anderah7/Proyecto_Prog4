#include <stdio.h>
#include "../includes/operaciones.h"
#include "../includes/initDatabase.h"
#include "../includes/GestorDB.h"
#include "../libs/sqlite3.h"
#include <stdlib.h>

int main (void){

	Departamento departamentos[100];
	Empleado empleados[100];
	Producto productos[100];
	Proveedor proveedores[100];
	Seccion secciones[100];

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
		    printf("Seleccione una opción:\n");
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

