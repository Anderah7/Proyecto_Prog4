#ifndef OPERACIONES_H_
#define OPERACIONES_H_

#include "sqlite3.h"

typedef struct {
	int idProd;
	char * nombreProd;
	float precio;
	int codSeccion;
	int codProveedor;
}Producto;

typedef struct {
	int codProveedor;
	char * nombreProveedor;
	int codPostal;
	char * contrasena;
}Proveedor;

typedef struct {
	int codSeccion;
	char * nombreSeccion;
}Seccion;

typedef struct {
	int idDepartamento;
	char * nombreDepartamento;
	int NSSJefe;
}Departamento;

typedef struct {
	int NSS;
	char * nombreEmpleado;
	char * contrasena;
	int codSeccion;
	int idDepartamento;
}Empleado;

void crearTablas(sqlite3 *db);

#endif
