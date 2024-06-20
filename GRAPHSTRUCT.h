#ifndef GRAPHSTRUCT
#define GRAPHSTRUCT

typedef unsigned int u32;
typedef unsigned int color;

typedef struct GrafoSt{
    u32 n; 
    u32 m;
    u32* grados;
    color* colores; 
    u32 delta;
    u32** vert;
}GrafoSt;

#endif