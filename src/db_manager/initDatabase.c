/*
 * initDatabase.c
 *
 *  Created on: 25 mar 2025
 *      Author: j.fernandezde
 */

#include <stdio.h>
#include "initDatabase.h"
#include "../libs/sqlite3.h"
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

void insertarDepartamentos(sqlite3 * db, Departamento departamentos[]) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < 5; i++) {
		sprintf(sql, "INSERT INTO departamento (id_Departamento, nombre) VALUES (%i, '%s');",
			                departamentos[i].idDepartamento, departamentos[i].nombreDepartamento); //aqui falta el NSS del jefe (que no esta en la base de datos)


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar datos: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Registro insertado: %i, %s, %i\n", departamentos[i].idDepartamento, departamentos[i].nombreDepartamento, departamentos[i].NSSJefe);
		        }
	}
}

void insertarEmpleados(sqlite3 * db, Empleado empleados[]) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < 5; i++) {
		sprintf(sql, "INSERT INTO empleado (NSS_Empleado, nombre, contrasena, id_Departamento, id_Seccion) VALUES (%i, '%s', '%s', %i, %i);",
			                empleados[i].NSS, empleados[i].nombreEmpleado, empleados[i].contrasena, empleados[i].idDepartamento, empleados[i].codSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar datos: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Registro insertado: %i, %s, %s, %i, %i\n", empleados[i].NSS, empleados[i].nombreEmpleado, empleados[i].contrasena, empleados[i].idDepartamento, empleados[i].codSeccion);
		        }
	}
}


void insertarProductos(sqlite3 * db, Producto productos[]) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < 5; i++) {
		sprintf(sql, "INSERT INTO producto (id_Producto, nombre, precio, id_Proveedor, cod_Seccion) VALUES (%i, '%s', %f, %i, %i);",
			                productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar datos: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Registro insertado: %i, %s, %f, %i, %i\n", productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);
		        }
	}
}


void insertarProveedores(sqlite3 * db, Proveedor proveedores[]) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < 5; i++) {
		sprintf(sql, "INSERT INTO proveedor (id_Proveedor, nombre, codigo_Postal, contrasena) VALUES (%i, '%s', %i, '%s');",
			                proveedores[i].codProveedor, proveedores[i].nombreProveedor, proveedores[i].codPostal, proveedores[i].contrasena);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar datos: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Registro insertado: %i, %s, %i, %s\n", proveedores[i].codProveedor, proveedores[i].nombreProveedor, proveedores[i].codPostal, proveedores[i].contrasena);
		        }
	}
}


void insertarSecciones(sqlite3 * db, Seccion secciones[]) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < 5; i++) {
		sprintf(sql, "INSERT INTO producto (cod_seccion, nombre) VALUES (%i, '%s');",
			                secciones[i].codSeccion, secciones[i].nombreSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar datos: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Registro insertado: %i, %s\n", secciones[i].codSeccion, secciones[i].nombreSeccion);
		        }
	}
}

void leerFicheros (Departamento departamentos[], Empleado empleados[], Producto productos[], Proveedor proveedores[], Seccion secciones[]){
	FILE *ficheroDepartamentos = fopen("database/datosIniciales/departamentos.csv", "r");
	FILE *ficheroEmpleados = fopen("database/datosIniciales/empleados.csv", "r");
	FILE *ficheroProductos = fopen("database/datosIniciales/productos.csv", "r");
	FILE *ficheroProveedores = fopen("database/datosIniciales/proveedores.csv", "r");
	FILE *ficheroSecciones = fopen("database/datosIniciales/secciones.csv", "r");


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

