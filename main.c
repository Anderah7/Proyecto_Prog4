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

	sqlite3_close(db);

}

