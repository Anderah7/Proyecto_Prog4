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
			"FOREIGN KEY(id_Proveedor) REFERENCES proveedor(id_Proveedor) ON DELETE CASCADE, "
			"FOREIGN KEY(cod_Seccion) REFERENCES seccion(cod_Seccion) ON DELETE CASCADE);"

			"CREATE TABLE IF NOT EXISTS departamento("
			"id_Departamento INT(5) PRIMARY KEY, "
			"nombre VARCHAR(50), "
			"NSS_Jefe INT(11), "
			"FOREIGN KEY(NSS_Jefe) REFERENCES empleado(NSS_Empleado) ON DELETE CASCADE); "


			"CREATE TABLE IF NOT EXISTS empleado("
			"NSS_Empleado INT(11) PRIMARY KEY, "
			"nombre VARCHAR(30), "
			"contrasena VARCHAR(30), "
			"id_Departamento INT(5), "
			"id_Seccion INT(5), "
			"FOREIGN KEY(id_Departamento) REFERENCES departamento(id_Departamento) ON DELETE CASCADE, "
			"FOREIGN KEY(id_Seccion) REFERENCES seccion(cod_seccion) ON DELETE CASCADE);";


	int ejecutar = sqlite3_exec(db, sql, 0, 0, &mensajeError);

	if(ejecutar != SQLITE_OK) {
		printf("Error al crear las tablas: %s\n", mensajeError);
		sqlite3_free(mensajeError);
	}
	else {
		printf("Tablas creadas correctamente\n");
	}

}

void insertarDepartamento(sqlite3 * db, Departamento departamento) {
	char * mensajeError = 0;
	char sql[256];

		sprintf(sql, "INSERT INTO departamento (id_Departamento, nombre, NSS_Jefe) VALUES (%i, '%s', %i);",
			                departamento.idDepartamento, departamento.nombreDepartamento, departamento.NSSJefe);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el departamento: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Departamento insertado: %i, %s, %i\n", departamento.idDepartamento, departamento.nombreDepartamento, departamento.NSSJefe);
		        }
	printf("\n");
}

void insertarEmpleado(sqlite3 * db, Empleado empleado) {
	char * mensajeError = 0;
	char sql[256];

		sprintf(sql, "INSERT INTO empleado (NSS_Empleado, nombre, contrasena, id_Departamento, id_Seccion) VALUES (%i, '%s', '%s', %i, %i);",
			                empleado.NSS, empleado.nombreEmpleado, empleado.contrasena, empleado.idDepartamento, empleado.codSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el empleado: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Empleado insertado: %i, %s, %s, %i, %i\n", empleado.NSS, empleado.nombreEmpleado, empleado.contrasena, empleado.idDepartamento, empleado.codSeccion);
		        }
	printf("\n");
}


void insertarProducto(sqlite3 * db, Producto producto) {
	char * mensajeError = 0;
	char sql[256];

		sprintf(sql, "INSERT INTO producto (id_Producto, nombre, precio, id_Proveedor, cod_Seccion) VALUES (%i, '%s', %f, %i, %i);",
			                producto.idProd, producto.nombreProd, producto.precio, producto.codProveedor, producto.codSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el producto: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Producto insertado: %i, %s, %f, %i, %i\n", producto.idProd, producto.nombreProd, producto.precio, producto.codProveedor, producto.codSeccion);
		        }

	printf("\n");
}


void insertarProveedor(sqlite3 * db, Proveedor proveedor) {
	char * mensajeError = 0;
	char sql[256];

		sprintf(sql, "INSERT INTO proveedor (id_Proveedor, nombre, codigo_Postal, contrasena) VALUES (%i, '%s', %i, '%s');",
			                proveedor.codProveedor, proveedor.nombreProveedor, proveedor.codPostal, proveedor.contrasena);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar el proveedor: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Proveedor insertado: %i, %s, %i, %s", proveedor.codProveedor, proveedor.nombreProveedor, proveedor.codPostal, proveedor.contrasena);
		            										//al acabar en string no necesita el \n
		        }
	printf("\n\n");
}


void insertarSeccion(sqlite3 * db, Seccion seccione) {
	char * mensajeError = 0;
	char sql[256];

		sprintf(sql, "INSERT INTO producto (cod_seccion, nombre) VALUES (%i, '%s');",
			                seccione.codSeccion, seccione.nombreSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar la seccion: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Seccion insertado: %i, %s", seccione.codSeccion, seccione.nombreSeccion);
		            								//al acabar en string no necesita el \n
		        }
	printf("\n\n");
}

void cargarFicheros (sqlite3 * db){
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
		Departamento departamento;
		 char *token = strtok(line, ",");
		 departamento.idDepartamento = atoi(token);

		 token = strtok(NULL, ",");
		 strcpy(departamento.nombreDepartamento, token);

		 token = strtok(NULL, ",");
		 departamento.NSSJefe = atoi(token);

		 insertarDepartamento(db, departamento);
	}

		fclose(ficheroDepartamentos);


	while (fgets(line, sizeof(line), ficheroEmpleados)) {
		Empleado empleado;
		char *token = strtok(line, ",");
		empleado.NSS = atoi(token);

		token = strtok(NULL, ",");
		strcpy(empleado.nombreEmpleado, token);

		token = strtok(NULL, ",");
		strcpy(empleado.contrasena, token);

		token = strtok(NULL, ",");
		empleado.codSeccion = atoi(token);

		token = strtok(NULL, ",");
		empleado.idDepartamento = atoi(token);

		insertarEmpleado(db, empleado);
		}

		fclose(ficheroEmpleados);


	while (fgets(line, sizeof(line), ficheroProductos)) {
		Producto producto;
		char *token = strtok(line, ",");
		producto.idProd = atoi(token);

		token = strtok(NULL, ",");
		strcpy(producto.nombreProd, token);

		token = strtok(NULL, ",");
		producto.precio = atof(token);

		token = strtok(NULL, ",");
		producto.codSeccion = atoi(token);

		token = strtok(NULL, ",");
		producto.codProveedor = atoi(token);

		insertarProducto(db, producto);
		}


		fclose(ficheroProductos);


	while (fgets(line, sizeof(line), ficheroProveedores)) {
		Proveedor proveedor;
		char *token = strtok(line, ",");
		proveedor.codProveedor = atoi(token);

		token = strtok(NULL, ",");
		strcpy(proveedor.nombreProveedor, token);

		token = strtok(NULL, ",");
		proveedor.codPostal = atoi(token);

		token = strtok(NULL, ",");
		strcpy(proveedor.contrasena, token);

		insertarProveedor(db, proveedor);
		}

		fclose(ficheroProveedores);


	while (fgets(line, sizeof(line), ficheroSecciones)) {
		Seccion seccion;
		char *token = strtok(line, ",");
		seccion.codSeccion = atoi(token);

		token = strtok(NULL, ",");
		strcpy(seccion.nombreSeccion, token);

		insertarSeccion(db, seccion);
		}

		fclose(ficheroSecciones);
}

