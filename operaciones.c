#include <stdio.h>
#include "operaciones.h"
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

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
			"cod_Seccion INT(5), "
			"FOREIGN KEY(id_Proveedor) REFERENCES proveedor(id_Proveedor), "
			"FOREIGN KEY(cod_Seccion) REFERENCES seccion(cod_Seccion));"

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
		printf("Tablas creadas correctamente\n");
	}

}

void insertarProductos(sqlite3 * db) {
	char * mensajeError = 0;

	const char *sql =
	        "INSERT INTO producto (id_Producto, nombre, precio, id_Proveedor, cod_Seccion) VALUES "
	        "(1, 'Huevos', 2.99, 1, 1), "
	        "(2, 'Leche', 1.50, 2, 1), "
	        "(3, 'Queso', 4.55, 3, 1), "
	        "(4, 'Filete de ternera', 5.99, 1, 1), "
	        "(5, 'Pechugas de pollo', 4.75, 2, 1), "
	        "(6, 'Alitas de pollo', 8.99, 4, 2), "
	        "(7, 'Manzana', 0.70, 3, 2), "
	        "(8, 'Pera', 0.60, 5, 2), "
	        "(9, 'Arroz blanco', 1.15, 4, 2), "
	        "(10, 'Macarrones', 1.70, 1, 2);";

	int ejecutar = sqlite3_exec(db, sql, 0, 0, &mensajeError);

	if (ejecutar != SQLITE_OK) {
	    printf("Error al insertar productos/Productos ya insertados: %s\n", mensajeError);
	    sqlite3_free(mensajeError);
	}
	else {
		printf("Productos insertados correctamente.\n");
	}
}

int mostrarProductos(sqlite3 *db, Producto **productos) {

	sqlite3_stmt *stmt;

	char sql[] = "select id_Producto, nombre, precio, id_Proveedor, cod_Seccion from producto";
	int contador = 0;

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
	    contador++;
	}

	sqlite3_reset(stmt);

	*productos = (Producto *)malloc(contador * sizeof(Producto));

	int i = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
	    (*productos)[i].idProd = sqlite3_column_int(stmt, 0);
	    strncpy((*productos)[i].nombreProd, (const char *)sqlite3_column_text(stmt, 1), sizeof((*productos)[i].nombreProd) - 1);
	    (*productos)[i].nombreProd[sizeof((*productos)[i].nombreProd) - 1] = '\0';
	    (*productos)[i].precio = (float)sqlite3_column_double(stmt, 2);
	    (*productos)[i].codProveedor = sqlite3_column_int(stmt, 3);
	    (*productos)[i].codSeccion = sqlite3_column_int(stmt, 4);
	    i++;
	    }

	sqlite3_finalize(stmt);

	return contador;
}

int compararPorPrecio(const void *a, const void *b) {
	Producto *p1 = (Producto *)a;
	Producto *p2 = (Producto *)b;
<<<<<<< HEAD

	if (p1->precio < p2->precio) return 1;
	if (p1->precio > p2->precio) return -1;
	return 0;
}

void ordenarEstante(Producto *productos, int num_productos, Producto ***productosEstante) {

}



void leerFicheros (Departamento departamentos[], Empleado empleados[], Producto productos[], Proveedor proveedores[], Seccion secciones[]){
	FILE *ficheroDepartamentos = fopen("datosIniciales/departamento.csv", "r");
	FILE *ficheroEmpleados = fopen("datosIniciales/empleados.csv", "r");
	FILE *ficheroProductos = fopen("datosIniciales/productos.csv", "r");
	FILE *ficheroProveedores = fopen("datosIniciales/proveedores.csv", "r");
	FILE *ficheroSecciones = fopen("datosIniciales/secciones.csv", "r");


	if (ficheroDepartamentos == NULL || ficheroEmpleados == NULL || ficheroProductos == NULL || ficheroProveedores == NULL || ficheroSecciones == NULL) {
	        perror("Error al abrir el archivo");
	        return;
	    }

	char line[256];
	int i = 0;


	while (fgets(line, sizeof(line), ficheroDepartamentos)) {
		 char *token = strtok(line, ";");
		 departamentos[i].idDepartamento = atoi(token);

		 token = strtok(NULL, ";");
		 strcpy(departamentos[i].nombreDepartamento, token);

		 token = strtok(NULL, ";");
		 departamentos[i].NSSJefe = atoi(token);

		 i++;
	}

		fclose(ficheroDepartamentos);

		i = 0;

	while (fgets(line, sizeof(line), ficheroEmpleados)) {
		char *token = strtok(line, ";");
		empleados[i].NSS = atoi(token);

		token = strtok(NULL, ";");
		strcpy(empleados[i].nombreEmpleado, token);

		token = strtok(NULL, ";");
		strcpy(empleados[i].contrasena, token);

		token = strtok(NULL, ";");
		empleados[i].codSeccion = atoi(token);

		token = strtok(NULL, ";");
		empleados[i].idDepartamento = atoi(token);

		i++;
		}

		fclose(ficheroEmpleados);

		i = 0;

	while (fgets(line, sizeof(line), ficheroProductos)) {
		char *token = strtok(line, ";");
		productos[i].idProd = atoi(token);

		token = strtok(NULL, ";");
		strcpy(productos[i].nombreProd, token);

		token = strtok(NULL, ";");
		productos[i].precio = atof(token);

		token = strtok(NULL, ";");
		productos[i].codSeccion = atoi(token);

		token = strtok(NULL, ";");
		productos[i].codProveedor = atoi(token);

		i++;
		}

		fclose(ficheroProductos);

		i = 0;

	while (fgets(line, sizeof(line), ficheroProveedores)) {
		char *token = strtok(line, ";");
		proveedores[i].codProveedor = atoi(token);

		token = strtok(NULL, ";");
		strcpy(proveedores[i].nombreProveedor, token);

		token = strtok(NULL, ";");
		proveedores[i].codPostal = atoi(token);

		token = strtok(NULL, ";");
		strcpy(proveedores[i].contrasena, token);

		i++;
		}

		fclose(ficheroProveedores);

		i = 0;

	while (fgets(line, sizeof(line), ficheroSecciones)) {
		char *token = strtok(line, ";");
		secciones[i].codSeccion = atoi(token);

		token = strtok(NULL, ";");
		strcpy(secciones[i].nombreSeccion, token);

		i++;
		}

		fclose(ficheroSecciones);


}


=======
>>>>>>> branch 'main' of https://github.com/Anderah7/Proyecto_Prog4.git

	if (p1->precio < p2->precio) return 1;
	if (p1->precio > p2->precio) return -1;
	return 0;
}

void ordenarEstante(Producto *productos, int num_productos, Producto ***productosEstante) {

}

