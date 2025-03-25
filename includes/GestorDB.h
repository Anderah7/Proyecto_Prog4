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

#endif /* SRC_DB_MANAGER_GESTORDB_H_ */
