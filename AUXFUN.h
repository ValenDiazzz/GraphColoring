#ifndef AUXFUN_H
#define AUXFUN_H

#include "GRAPHSTRUCT.h"
#include "GRAPHFUN.h"
#include "stack.h"
#include <stdlib.h>

//Funciones auxiliares para Greedy
int max1(u32 a, u32 b);
int min(u32 a, u32 b);
int comparar_enteros(const void *a, const void *b);
bool biyeccion(u32 n,u32* Orden);

//Funciones auxiliares para GulDukat y ElimGarak
u32 agregar_vertices_gul(int cota, u32 **grado, stack *list_vert, u32 *orden, u32 cont);
u32 agregar_vertices_EG(int cota, u32 **grado, stack *list_vert, u32 *orden, u32 cont);
void inicializar(int cota, u32 **lista);
void inicializar_stack(int cota, stack *s);
void liberar(int cota, u32** lista);
void liberar_stack(int cota, stack *s);
int cant_colores(Grafo G);

#endif