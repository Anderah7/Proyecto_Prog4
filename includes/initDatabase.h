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

void insertarDepartamentos(sqlite3 *db, Departamento departamento);
void insertarEmpleados(sqlite3 *db, Empleado empleado);
void insertarProductos(sqlite3 *db, Producto producto);
void insertarProveedores(sqlite3 *db, Proveedor proveedor);
void insertarSecciones(sqlite3 *db, Seccion seccion);

void cargarFicheros (sqlite3 *db);
#endif /* INITDATABASE_H_ */
