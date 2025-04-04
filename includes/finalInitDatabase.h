/*
 * finalInitDatabase.h
 *
 *  Created on: 4 abr 2025
 *      Author: j.fernandezde
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../libs/sqlite3.h"

#ifndef INCLUDES_FINALINITDATABASE_H_
#define INCLUDES_FINALINITDATABASE_H_

void crearTablasInit(sqlite3 *db);
void cargarProveedoresInit(sqlite3 *db);
void cargarDepartamentosInit(sqlite3 *db);

#endif /* INCLUDES_FINALINITDATABASE_H_ */
