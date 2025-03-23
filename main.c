#include <stdio.h>
#include "operaciones.h"
#include "sqlite3.h"
#include <stdlib.h>

int main (void){
	sqlite3 * db;
	int abrir = sqlite3_open("adate.db", &db);

	if (abrir) {
	    printf("Error al conectar a la bd: %s\n", sqlite3_errmsg(db));
	    return abrir;
	} else {
	    printf("Conectado a la bd\n");
	}

	crearTablas(db);

	insertarProductos(db);

	Producto *productos = NULL;
	//int num_productos = mostrarProductos(db, &productos);

	//for (int i = 0; i < num_productos; ++i) {
		//printf("ID: %d, Nombre: %s, Precio: %.2f, Proveedor: %d, Seccion: %d\n", productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);
	//}

	sqlite3_close(db);

}

