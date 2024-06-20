#ifndef GREEDY_H
#define GREEDY_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "GRAPHFUN.h"

u32 Greedy(Grafo G, u32* Orden);
char GulDukat(Grafo G,u32* Orden);
char ElimGarak(Grafo G,u32* Orden);
#endif
