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
        printf("Tablas eliminadas correctamente.\n");
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

void anadirProducto (sqlite3 * db,  char nomProd[], float precio, int codSec, int codDep){
	char * mensajeError = 0;
	char sql[256];
	int contador = obtenerIdUltimoProducto(db);
	contador += 1;

	sprintf(sql, "INSERT INTO producto (id_Producto, nombre, precio, id_Proveedor, cod_Seccion) VALUES (%i, '%s', %f, %i, %i);",
				contador, nomProd, precio, codSec, codDep);

	if (sqlite3_exec(db, sql, 0, 0, &mensajeError) != SQLITE_OK) {
			            printf("Error al insertar el producto: %s\n", mensajeError);
			            sqlite3_free(mensajeError);
			        } else {
			            printf("Producto insertado: %i, %s, %f, %i, %i\n", contador, nomProd, precio, codSec, codDep);
			        }
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

