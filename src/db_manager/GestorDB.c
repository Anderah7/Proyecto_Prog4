/*
 * GestorDB.c
 *
 *  Created on: 25 mar 2025
 *      Author: j.fernandezde
 */
#include "../../includes/GestorDB.h"

#include <stdio.h>
#include "../../libs/sqlite3.h"
#include <stdlib.h>
#include <string.h>

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
        printf("Tablas eliminadas correctamente\n");
    }
}


void mostrarProductos(sqlite3 *db) {

	sqlite3_stmt *stmt;

	char sql[] = "select id_Producto, nombre, precio, id_Proveedor, cod_Seccion from producto";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando la consulta SELECT\n");
	    printf("%s\n", sqlite3_errmsg(db));
	    return;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int idProd = sqlite3_column_int(stmt, 0);
		const unsigned char *nombreProd = sqlite3_column_text(stmt, 1);
		double precio = sqlite3_column_double(stmt, 2);
	    int codProveedor = sqlite3_column_int(stmt, 3);
	    int codSeccion = sqlite3_column_int(stmt, 4);

	    if(!idProd == 0) {
	    	printf("Producto: %d, Nombre: %s, Precio: %.2f, Proveedor: %d, Sección: %d\n", idProd, nombreProd, precio, codProveedor, codSeccion);
	    }
	}


	sqlite3_finalize(stmt);

}


void eliminarProducto(sqlite3 * db, int idProd) {
	char * mensajeError = 0;
	char sql[256];
	int contador = obtenerIdUltimoProducto(db);
	contador -= 1;

	sprintf(sql, "DELETE FROM producto WHERE id_Producto = %i", idProd);

	if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		printf("Error al eliminar el producto: %s\n", mensajeError);
		sqlite3_free(mensajeError);
	} else {
		printf("Producto eliminado: %i\n", idProd);
	}
}

void modificarProducto(sqlite3 *db) {
	char * mensajeError = 0;
	char sql[256];
	int contador = obtenerIdUltimoProducto(db);
	int id;
	char nuevoNombre[50];
	float nuevoPrecio;

	printf("Ingrese el ID del producto a modificar: ");
	fflush(stdout);
	scanf("%d", &id);

	while(id < 1 || id > contador) {
		printf("ID incorrecto. Eliga id entre 1 y %i: ", contador);
		fflush(stdout);
		scanf("%d", &id);
	}

	printf("Ingrese el nuevo nombre: ");
	fflush(stdout);
	scanf("%s", &nuevoNombre);

	printf("Ingrese el nuevo precio: ");
	fflush(stdout);
	scanf("%f", &nuevoPrecio);

	sprintf(sql, "UPDATE producto SET nombre = '%s', precio = %.2f WHERE id_Producto = %d;", nuevoNombre, nuevoPrecio, id);

	if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
		printf("Error al eliminar el producto: %s\n", mensajeError);
		sqlite3_free(mensajeError);
	} else {
		printf("Producto modificado: %i , nombre: %s\n", id, nuevoNombre);
	}

}

void buscarProductos(sqlite3 *db) {
	int opcion;
	char nombreBuscador[50];

	printf("Elige el modo de busqueda: \n");
	printf("1: Buscar por nombre \n");
	printf("2: Buscar por seccion\n");
	fflush(stdout);
	scanf("%i", &opcion);
	getchar();
	fflush(stdout);

	if(opcion == 1) {
		char sql[256];

		printf("Elige el nombre del producto: \n");
		fflush(stdout);
		scanf("%s", &nombreBuscador);
		getchar();
		fflush(stdout);

		 snprintf(sql, sizeof(sql), "SELECT id_Producto, nombre, precio, id_Proveedor, cod_Seccion FROM producto WHERE nombre LIKE '%%%s%%';", nombreBuscador);

		 sqlite3_stmt *stmt;
		 if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			 printf("\nResultados de la búsqueda por nombre:\n");
			 while (sqlite3_step(stmt) == SQLITE_ROW) {
				 int id = sqlite3_column_int(stmt, 0);
				 const unsigned char *nombre = sqlite3_column_text(stmt, 1);
				 float precio = (float)sqlite3_column_double(stmt, 2);
				 int proveedor = sqlite3_column_int(stmt, 3);
				 int seccion = sqlite3_column_int(stmt, 4);

				 if(id != 0) {
					 printf("ID: %d | Nombre: %s | Precio: %.2f | Proveedor: %d | Sección: %d\n", id, nombre, precio, proveedor, seccion);
				 }
			 }
			 sqlite3_finalize(stmt);
		     }
		 else {
			 printf("Error en la consulta: %s\n", sqlite3_errmsg(db));
		 	 }

	}
	else if(opcion == 2) {
		char sql[256];

		printf("Elige la seccion del producto: \n");
		fflush(stdout);
		scanf("%s", &nombreBuscador);
		getchar();
		fflush(stdout);

		snprintf(sql, sizeof(sql), "SELECT id_Producto, nombre, precio, id_Proveedor FROM producto WHERE cod_Seccion = %s;", nombreBuscador);

		sqlite3_stmt *stmt;
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			printf("\nResultados de la búsqueda por categoría:\n");
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				int id = sqlite3_column_int(stmt, 0);
		        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
		        float precio = (float)sqlite3_column_double(stmt, 2);
		        int proveedor = sqlite3_column_int(stmt, 3);

		        if(id != 0) {
		        	printf("ID: %d | Nombre: %s | Precio: %.2f | Proveedor: %d\n", id, nombre, precio, proveedor);
		        }
				}
			sqlite3_finalize(stmt);
			}
		else {
			printf("Error en la consulta: %s\n", sqlite3_errmsg(db));
		}
	}
	else {
		printf("Opcion no valida \n");
	}
}

void mostrarProductosOrden(sqlite3 *db) {

	sqlite3_stmt *stmt;

	char sql[] = "select id_Producto, nombre, precio, id_Proveedor, cod_Seccion from producto order by precio DESC";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando la consulta SELECT\n");
		printf("%s\n", sqlite3_errmsg(db));
		return;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int idProd = sqlite3_column_int(stmt, 0);
		const unsigned char *nombreProd = sqlite3_column_text(stmt, 1);
		double precio = sqlite3_column_double(stmt, 2);
		int codProveedor = sqlite3_column_int(stmt, 3);
		int codSeccion = sqlite3_column_int(stmt, 4);

		if(!idProd == 0) {
			printf("Producto: %d, Nombre: %s, Precio: %.2f, Proveedor: %d, Sección: %d\n", idProd, nombreProd, precio, codProveedor, codSeccion);
		}
	}


	sqlite3_finalize(stmt);


}


int obtenerIdUltimoProducto(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT MAX(id_Producto) FROM producto;";
    int maximo = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            maximo = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Error al obtener la id del ultimo producto: %s\n", sqlite3_errmsg(db));
    }

    return maximo;
}

