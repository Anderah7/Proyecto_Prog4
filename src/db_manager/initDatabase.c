/*
 * initDatabase.c
 *
 *  Created on: 25 mar 2025
 *      Author: j.fernandezde
 */

#include <stdio.h>
#include "../../includes/initDatabase.h"
#include "../../libs/sqlite3.h"
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
			"nombre VARCHAR(50), "
			"NSS_Jefe INT(11), "
			"FOREIGN KEY(NSS_Jefe) REFERENCES empleado(NSS_Empleado)); "


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

void insertarDepartamentos(sqlite3 * db, Departamento departamentos[], int contDep) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contDep; i++) {
		sprintf(sql, "INSERT INTO departamento (id_Departamento, nombre, NSS_Jefe) VALUES (%i, '%s', %i);",
			                departamentos[i].idDepartamento, departamentos[i].nombreDepartamento, departamentos[i].NSSJefe); //aqui falta el NSS del jefe (que no esta en la base de datos)


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el departamento: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Departamento insertado: %i, %s, %i\n", departamentos[i].idDepartamento, departamentos[i].nombreDepartamento, departamentos[i].NSSJefe);
		        }
	}
}

void insertarEmpleados(sqlite3 * db, Empleado empleados[], int contEmp) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contEmp; i++) {
		sprintf(sql, "INSERT INTO empleado (NSS_Empleado, nombre, contrasena, id_Departamento, id_Seccion) VALUES (%i, '%s', '%s', %i, %i);",
			                empleados[i].NSS, empleados[i].nombreEmpleado, empleados[i].contrasena, empleados[i].idDepartamento, empleados[i].codSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el empleado: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Empleado insertado: %i, %s, %s, %i, %i\n", empleados[i].NSS, empleados[i].nombreEmpleado, empleados[i].contrasena, empleados[i].idDepartamento, empleados[i].codSeccion);
		        }
	}
}


void insertarProductos(sqlite3 * db, Producto productos[], int contPro) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contPro; i++) {
		sprintf(sql, "INSERT INTO producto (id_Producto, nombre, precio, id_Proveedor, cod_Seccion) VALUES (%i, '%s', %f, %i, %i);",
			                productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el producto: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Producto insertado: %i, %s, %f, %i, %i\n", productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);
		        }
	}
}


void insertarProveedores(sqlite3 * db, Proveedor proveedores[], int contPov) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contPov; i++) {
		sprintf(sql, "INSERT INTO proveedor (id_Proveedor, nombre, codigo_Postal, contrasena) VALUES (%i, '%s', %i, '%s');",
			                proveedores[i].codProveedor, proveedores[i].nombreProveedor, proveedores[i].codPostal, proveedores[i].contrasena);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el proveedor: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Proveedor insertado: %i, %s, %i, %s", proveedores[i].codProveedor, proveedores[i].nombreProveedor, proveedores[i].codPostal, proveedores[i].contrasena);
		            										//al acabar en string no necesita el \n
		        }
	}
}


void insertarSecciones(sqlite3 * db, Seccion secciones[], int contSec) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contSec; i++) {
		sprintf(sql, "INSERT INTO producto (cod_seccion, nombre) VALUES (%i, '%s');",
			                secciones[i].codSeccion, secciones[i].nombreSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar la seccion: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Seccion insertado: %i, %s", secciones[i].codSeccion, secciones[i].nombreSeccion);
		            								//al acabar en string no necesita el \n
		        }
	}
}

void leerFicheros (Departamento departamentos[], Empleado empleados[], Producto productos[], Proveedor proveedores[], Seccion secciones[], int *contDep, int *contEmp, int *contProd, int *contProv, int *contSec){
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


	while (fgets(line, sizeof(line), ficheroDepartamentos)) {
		 char *token = strtok(line, ",");
		 departamentos[*contDep].idDepartamento = atoi(token);

		 token = strtok(NULL, ",");
		 strcpy(departamentos[*contDep].nombreDepartamento, token);

		 token = strtok(NULL, ",");
		 departamentos[*contDep].NSSJefe = atoi(token);

		 (*contDep)++;
	}

		fclose(ficheroDepartamentos);


	while (fgets(line, sizeof(line), ficheroEmpleados)) {
		char *token = strtok(line, ",");
		empleados[*contEmp].NSS = atoi(token);

		token = strtok(NULL, ",");
		strcpy(empleados[*contEmp].nombreEmpleado, token);

		token = strtok(NULL, ",");
		strcpy(empleados[*contEmp].contrasena, token);

		token = strtok(NULL, ",");
		empleados[*contEmp].codSeccion = atoi(token);

		token = strtok(NULL, ",");
		empleados[*contEmp].idDepartamento = atoi(token);

		(*contEmp)++;
		}

		fclose(ficheroEmpleados);


	while (fgets(line, sizeof(line), ficheroProductos)) {
		char *token = strtok(line, ",");
		productos[*contProd].idProd = atoi(token);

		token = strtok(NULL, ",");
		strcpy(productos[*contProd].nombreProd, token);

		token = strtok(NULL, ",");
		productos[*contProd].precio = atof(token);

		token = strtok(NULL, ",");
		productos[*contProd].codSeccion = atoi(token);

		token = strtok(NULL, ",");
		productos[*contProd].codProveedor = atoi(token);

		(contProd)++;
		}


		fclose(ficheroProductos);


	while (fgets(line, sizeof(line), ficheroProveedores)) {
		char *token = strtok(line, ",");
		proveedores[*contProv].codProveedor = atoi(token);

		token = strtok(NULL, ",");
		strcpy(proveedores[*contProv].nombreProveedor, token);

		token = strtok(NULL, ",");
		proveedores[*contProv].codPostal = atoi(token);

		token = strtok(NULL, ",");
		strcpy(proveedores[*contProv].contrasena, token);

		(*contProv)++;
		}

		fclose(ficheroProveedores);


	while (fgets(line, sizeof(line), ficheroSecciones)) {
		char *token = strtok(line, ",");
		secciones[*contSec].codSeccion = atoi(token);

		token = strtok(NULL, ",");
		strcpy(secciones[*contSec].nombreSeccion, token);

		(*contSec)++;
		}

		fclose(ficheroSecciones);
}

