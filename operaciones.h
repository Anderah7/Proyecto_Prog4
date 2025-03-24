#ifndef OPERACIONES_H_
#define OPERACIONES_H_

#include "sqlite3.h"

typedef struct {
	int idProd;
	char nombreProd[30];
	float precio;
	int codSeccion;
	int codProveedor;
}Producto;

typedef struct {
	int codProveedor;
	char nombreProveedor[30];
	int codPostal;
	char contrasena[30];
}Proveedor;

typedef struct {
	int codSeccion;
	char nombreSeccion[30];
}Seccion;

typedef struct {
	int idDepartamento;
	char nombreDepartamento[30];
	int NSSJefe;
}Departamento;

typedef struct {
	int NSS;
	char nombreEmpleado[30];
	char contrasena[30];
	int codSeccion;
	int idDepartamento;
}Empleado;

void crearTablas(sqlite3 *db);

void insertarProductos(sqlite3 * db);

int mostrarProductos(sqlite3 *db, Producto **productos);

int compararPorPrecio(const void *a, const void *b);

void ordenarEstante(Producto *productos, int num_productos, Producto ***productosEstante);

#endif
