#include <stdio.h>
#include "operaciones.h"
#include "sqlite3.h"

void crearTablas(sqlite3 *db) {

	char * mensajeError = 0;

	const char * sql =
			"CREATE TABLE IF NOT EXISTS proveedor( "
			"id_Proveedor INT(5) PRIMARY KEY, "
			"nombre VARCHAR(30), "
			"codigo_Postal INT(10), "
			"contrasena VARCHAR(30)); "

			"CREATE TABLE IF NOT EXISTS seccion( "
			"cod_seccion INT(5) PRIMARY KEY, "
			"nombre VARCHAR(30)); "

			"CREATE TABLE IF NOT EXISTS producto("
			"id_Producto INT(5) PRIMARY KEY, "
			"nombre VARCHAR(30), "
			"precio REAL, "
			"id_Proveedor INT(5), "
			"FOREIGN KEY(id_Proveedor) REFERENCES proveedor(id_Proveedor));"

			"CREATE TABLE IF NOT EXISTS departamento("
			"id_Departamento INT(5) PRIMARY KEY, "
			"nombre VARCHAR(50)); "

			"CREATE TABLE IF NOT EXISTS empleado("
			"NSS_Empleado INT(11) PRIMARY KEY, "
			"nombre VARCHAR(30), "
			"contrasena VARCHAR(30), "
			"id_Departamento INT(5), "
			"id_Seccion INT(5), "
			"FOREIGN KEY(id_Departamento) REFERENCES departamento(id_Departamento), "
			"FOREIGN KEY(id_Seccion) REFERENCES seccion(cod_seccion));";


	int ejecutar = sqlite3_exec(db, sql, 0, 0, &mensajeError);

	if(ejecutar != SQLITE_OK) {
		printf("Error al crear las tablas: %s\n", mensajeError);
		sqlite3_free(mensajeError);
	}
	else {
		printf("Tablas creadas correctamente");
	}

}



