/*
 * GestorBD.h
 *
 *  Created on: 25 mar 2025
 *      Author: j.fernandezde
 */

#ifndef SRC_DB_MANAGER_GESTORDB_H_
#define SRC_DB_MANAGER_GESTORDB_H_

#include "../libs/sqlite3.h"
#include "../includes/estructuras.h"

void dropTables(sqlite3 *db);

int mostrarProductos(sqlite3 *db, Producto **productos);

void anadirProducto (sqlite3 * db,  char nomProd[], float precio, int codSec, int codDep);

int obtenerIdUltimoProducto(sqlite3 *db);

#endif /* SRC_DB_MANAGER_GESTORDB_H_ */
