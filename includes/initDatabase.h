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

void insertarDepartamentos(sqlite3 * db, Departamento departamentos[], int contDep);
void insertarEmpleados(sqlite3 * db, Empleado empleados[], int contEmp);
void insertarProductos(sqlite3 * db, Producto productos[], int contProd);
void insertarProveedores(sqlite3 * db, Proveedor proveedores[], int contProv);
void insertarSecciones(sqlite3 * db, Seccion secciones[], int contSec);

void leerFicheros (Departamento departamentos[], Empleado empleados[], Producto productos[], Proveedor proveedores[], Seccion secciones[], int *contDep, int *contEmp, int *contProd, int *contProv, int *contSec);

#endif /* INITDATABASE_H_ */
