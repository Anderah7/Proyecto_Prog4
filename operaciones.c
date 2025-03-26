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

void insertarDepartamentos(sqlite3 * db, Departamento departamentos[], int contador) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contador; i++) {
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

void insertarEmpleados(sqlite3 * db, Empleado empleados[], int contador) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contador; i++) {
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


void insertarProductos(sqlite3 * db, Producto productos[], int contador) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contador; i++) {
		sprintf(sql, "INSERT INTO producto (id_Producto, nombre, precio, id_Proveedor, cod_Seccion) VALUES (%i, '%s', %f, %i, %i);",
			                productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);


	 if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		            printf("Error al insertar datos: %s\n", mensajeError);
		            sqlite3_free(mensajeError);
		        } else {
		            printf("Registro insertado: %i, %s, %.2f, %i, %i\n", productos[i].idProd, productos[i].nombreProd, productos[i].precio, productos[i].codProveedor, productos[i].codSeccion);
		        }
	}
}


void insertarProveedores(sqlite3 * db, Proveedor proveedores[], int contador) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contador; i++) {
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


void insertarSecciones(sqlite3 * db, Seccion secciones[], int contador) {
	char * mensajeError = 0;
	char sql[256];

	for (int i = 0; i < contador; i++) {
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


	if (p1->precio < p2->precio) return 1;
	if (p1->precio > p2->precio) return -1;
	return 0;
}

void ordenarEstante(Producto *productos, int num_productos, Producto ***productosEstante, int * num_secciones, int ** seccionesEstante) {

	*num_secciones = contarSecciones(productos, num_productos, seccionesEstante);

	*productosEstante = malloc((*num_secciones) * sizeof(Producto *));
	int *contadorSeccion = calloc((*num_secciones), sizeof(int));

	for (int i = 0; i < num_productos; i++) {
		for (int j = 0; j < *num_secciones; j++) {
			if (productos[i].codSeccion == (*seccionesEstante)[j]) {
				contadorSeccion[j]++;
	            break;
	        }
		}
	}

	for (int i = 0; i < *num_secciones; i++) {
		(*productosEstante)[i] = malloc(contadorSeccion[i] * sizeof(Producto));
		contadorSeccion[i] = 0;
	}

	for (int i = 0; i < num_productos; i++) {
		for (int j = 0; j < *num_secciones; j++) {
			if (productos[i].codSeccion == (*seccionesEstante)[j]) {
				(*productosEstante)[j][contadorSeccion[j]++] = productos[i];
				break;
			}
		}
	}

	free(contadorSeccion);
}

int contarSecciones(Producto *productos, int num_productos, int **seccionesEstante) {
	int *tempSecciones = malloc(num_productos * sizeof(int));
	int num_secciones = 0;

	for (int i = 0; i < num_productos; i++) {
		int existe = 0;
	    for (int j = 0; j < num_secciones; j++) {
	    	if (tempSecciones[j] == productos[i].codSeccion) {
	    		existe = 1;
	            break;
	        }
	    }
	    if (!existe) {
	        tempSecciones[num_secciones++] = productos[i].codSeccion;
	    }
	}

	*seccionesEstante = malloc(num_secciones * sizeof(int));
	memcpy(*seccionesEstante, tempSecciones, num_secciones * sizeof(int));
	free(tempSecciones);

	return num_secciones;
}

void mostrarProductosEstante(Producto **productosEstante, int *seccionesEstante, int num_secciones) {
	for(int i = 0; i < num_secciones; i++) {
		printf("Seccion: %d", seccionesEstante[i]);
		int j = 0;
		while (productosEstante[i][j].idProd != 0) {
			printf("  ID: %d, Nombre: %s, Precio: %.2f\n", productosEstante[i][j].idProd, productosEstante[i][j].nombreProd, productosEstante[i][j].precio);
			j++;
		}
	}
}

void liberarMemoria(Producto **productosEstante, int num_secciones) {
	for(int i = 0; i < num_secciones; i++) {
		free(productosEstante[i]);
	}
	free(productosEstante);
}

void leerFicheros (Departamento departamentos[], Empleado empleados[], Producto productos[], Proveedor proveedores[], Seccion secciones[], int *contDepar, int *contEmpl, int *contProd, int *contProv, int *contSec){
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
		 departamentos[*contDepar].idDepartamento = atoi(token);

		 token = strtok(NULL, ",");
		 strcpy(departamentos[*contDepar].nombreDepartamento, token);

		 token = strtok(NULL, ",");
		 departamentos[*contDepar].NSSJefe = atoi(token);

		 *contDepar += 1;
	}

		fclose(ficheroDepartamentos);


	while (fgets(line, sizeof(line), ficheroEmpleados)) {
		char *token = strtok(line, ",");
		empleados[*contEmpl].NSS = atoi(token);

		token = strtok(NULL, ",");
		strcpy(empleados[*contEmpl].nombreEmpleado, token);

		token = strtok(NULL, ",");
		strcpy(empleados[*contEmpl].contrasena, token);

		token = strtok(NULL, ",");
		empleados[*contEmpl].codSeccion = atoi(token);

		token = strtok(NULL, ",");
		empleados[*contEmpl].idDepartamento = atoi(token);

		*contEmpl += 1;
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

		*contProd += 1;
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

		*contProv += 1;
		}

		fclose(ficheroProveedores);


	while (fgets(line, sizeof(line), ficheroSecciones)) {
		char *token = strtok(line, ",");
		secciones[*contSec].codSeccion = atoi(token);

		token = strtok(NULL, ",");
		strcpy(secciones[*contSec].nombreSeccion, token);

		*contSec += 1;
		}

		fclose(ficheroSecciones);
}

void dropTables(sqlite3 * db) {
    char *errMsg = 0;
    char *sql = "DROP TABLE IF EXISTS producto; "
    			"DROP TABLE IF EXISTS departamento; "
                "DROP TABLE IF EXISTS proveedor; "
    			"DROP TABLE IF EXISTS empleado; "
                "DROP TABLE IF EXISTS seccion; ";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        printf("Error al borrar tablas: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Tablas eliminadas correctamente.\n");
    }
}










