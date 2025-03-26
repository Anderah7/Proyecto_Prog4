#ifndef OPERACIONES_H_
#define OPERACIONES_H_

#include "../libs/sqlite3.h"
#include "../includes/estructuras.h"


int compararPorPrecio(const void *a, const void *b);

void ordenarEstante(Producto *productos, int num_productos, Producto ***productosEstante, int * num_secciones, int ** seccionesEstante);

int contarSecciones(Producto *productos, int num_productos, int **seccionesEstante);

void mostrarProductosEstante(Producto **productosEstante, int *seccionesEstante, int num_secciones);

void anadirProducto(sqlite3 * db, int *contProd, char nomProd[], float precio, int codSec, int codDep);

void liberarMemoria(Producto **productosEstante, int num_secciones);

#endif
