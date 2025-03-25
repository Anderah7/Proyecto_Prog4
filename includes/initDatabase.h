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

void insertarDepartamentos(sqlite3 * db, Departamento departamentos[]);
void insertarEmpleados(sqlite3 * db, Empleado empleados[]);
void insertarProductos(sqlite3 * db, Producto productos[]);
void insertarProveedores(sqlite3 * db, Proveedor proveedores[]);
void insertarSecciones(sqlite3 * db, Seccion secciones[]);

void leerFicheros (Departamento departamentos[], Empleado empleados[], Producto productos[], Proveedor proveedores[], Seccion secciones[]);

#endif /* INITDATABASE_H_ */
