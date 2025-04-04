#include <stdio.h>
#include "../includes/operaciones.h"
#include "../includes/initDatabase.h"
#include "../includes/GestorDB.h"
#include "../libs/sqlite3.h"
#include "../includes/interfaz.h"
#include "../includes/estructuras.h"
#include <stdlib.h>

int main (void){

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
	cargarFicheros(db);


	char opcion;
	    do {
	        printf("\n==== MENÚ PRINCIPAL ====\n");
	        printf("1. Gestión de Productos\n");
	        printf("2. Gestion de Empleados\n");
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
	            case 'q':
	                printf("Saliendo del programa...\n");
	                break;
	            default:
	                printf("Opción no válida, intente de nuevo.\n");
	        }
	    } while (opcion != 'q');



	sqlite3_close(db);

}

