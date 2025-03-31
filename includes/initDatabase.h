/*
 * initDatabase.h
 *
 *  Created on: 25 mar 2025
 *      Author: j.fernandezde
 */

#ifndef INITDATABASE_H_
#define INITDATABASE_H_

#include "../libs/sqlite3.h"
#include "../includes/estructuras.h"

void crearTablas(sqlite3 *db);

void insertarDepartamento(sqlite3 *db, Departamento departamento);
void insertarEmpleado(sqlite3 *db, Empleado empleado);
void insertarProducto(sqlite3 *db, Producto producto);
void insertarProveedor(sqlite3 *db, Proveedor proveedor);
void insertarSeccion(sqlite3 *db, Seccion seccion);

void cargarFicheros (sqlite3 *db);
#endif /* INITDATABASE_H_ */
