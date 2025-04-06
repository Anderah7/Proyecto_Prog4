#include <stdio.h>
#include "../includes/operaciones.h"
#include "../includes/finalInitDatabase.h"
#include "../includes/anadirDatosDB.h"
#include "../includes/GestorDB.h"
#include "../libs/sqlite3.h"
#include "../includes/interfaz.h"
#include "../includes/estructuras.h"
#include <stdlib.h>

int main (void){

//	Departamento departamentos[100];
//	Empleado empleados[100];
//	Producto productos[200];
//	Proveedor proveedores[100];
//	Seccion secciones[100];



	sqlite3 * db;
	int abrir = sqlite3_open("database/adate.db", &db);

	if (abrir) {
	    printf("Error al conectar a la bd: %s\n", sqlite3_errmsg(db));
	    return abrir;
	} else {
	    printf("Conectado a la bd\n");
	}



//	cargarFicheros(db);
	crearTablasInit(db);

	char opcion;
	    do {
	        printf("\n==== ADATE: menú principal ====\n");
	        printf("1. Gestión de Productos\n");
	        printf("2. Gestión de Empleados\n");
	        printf("3. Gestión de la BBDD\n");
	        printf("4. Introducir datos.\n");
	        printf("q. Salir del programa\n");
	        printf("Seleccione una opción: ");
	        fflush(stdout);
	        scanf(" %c", &opcion);

	        switch (opcion) {
	            case '1':
	            	gestionarProductos(db);
	                break;
	            case '2':
	                gestionarEmpleados(db);
	                break;
	            case '3':
	                gestionarBBDD(db);
	                break;
	            case '4':
	            	introducirDatosDesdeCSV(db);
	            	break;
	            case 'q':
	                printf("Saliendo del programa...\n");
	                break;
	            default:
	                printf("Opción no válida, intente de nuevo.\n");
	        }
	    } while (opcion != 'q');



	sqlite3_close(db);

}

