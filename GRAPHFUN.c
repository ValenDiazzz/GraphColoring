#include "GRAPHFUN.h"
#include "GRAPHSTRUCT.h"

#define UINT32_MAX 4294967295U; //2^32 - 1

int max(u32 a, u32 b) {
    return a > b ? a : b;
}

Grafo ConstruirGrafo(){
    Grafo G=malloc(sizeof(struct GrafoSt));
    u32 nn,mm;
    
    //Salteamos las lineas con comentarios y espacios en blanco
    char com;
    while((com=fgetc(stdin)) == 'c' || com == '\n'){
        while((com=fgetc(stdin))  != '\n' && com != EOF){
        };
    }
    ungetc(com, stdin);
    
    int res=scanf("p edge %u %u \n", &nn, &mm); 
    if(res != 2){ //Error de lectura 
        free(G);
        G=NULL;
        return G;
    }

    G->n=nn;
    G->m=mm;
    G->grados=calloc(nn , sizeof(u32));
    G->colores=calloc(nn, sizeof(color));
    G->vert=malloc(nn * sizeof(u32*));
    
    //Creamos estructuras auxiliares
    u32 *sizes=calloc(nn , sizeof(u32));
    u32 **edges;
    edges=malloc(mm * sizeof(u32 *));
    for (u32 i = 0; i < mm; i++) {
        edges[i] = malloc(2 * sizeof(u32));
    }
    
    //almacenamos lados
    u32 v1,v2;
    for(u32 i=0;i<mm-1;i++){
        int res=scanf("e %u %u \n", &v1, &v2);
        
        if(res != 2){ //Error de lectura 
            free(G->grados);
            free(G->colores);
            free(G->vert);
            free(G);
            G=NULL;
            return G;
        }
        
        edges[i][0]=v1;
        edges[i][1]=v2;
        G->grados[v1]++;
        G->grados[v2]++;
    }

    //El for anterior debe tener la condición i<mm, pero usamos i<mm - 1 porque
    //realizo la última iteración sin \n en el scanf para que termine en mm iteracciones
    
    res=scanf("e %u %u", &v1, &v2);
    
    if(res != 2){ //Error de lectura 
        free(G->grados);
        free(G->colores);
        free(G->vert);
        free(G);
        G=NULL;
        return G;
    }
    edges[mm-1][0]=v1;
    edges[mm-1][1]=v2;
    G->grados[v1]++;
    G->grados[v2]++;
    
    //Seguimos con allocs de G y calculamos Delta
    u32 Delta=0;
    for(u32 j=0;j<nn;j++){
        G->vert[j]=malloc(G->grados[j] * sizeof(u32));
        sizes[j]=G->grados[j];
        Delta=max(max(Delta, sizes[j]),j+1<nn?sizes[j+1]:0);
    }
    G->delta = Delta;
    
    //Guardamos los vecinos de cada vertice
    u32 e1,e2;
    for(u32 j=0;j<mm;j++){
        e1=edges[j][0];
        e2=edges[j][1];
        G->vert[e1][sizes[e1]-1]=e2;
        G->vert[e2][sizes[e2]-1]=e1;
        sizes[e1]--;
        sizes[e2]--;
    }
    
    //Eliminamos los estructuras auxiliares
    for (u32 i=0;i<mm;i++) {
        free(edges[i]);
    }
    free(edges);
    free(sizes);
    return G;
}

bool invrep(Grafo G){
    return G!=NULL || G->delta<=G->n;
}


void DestruirGrafo(Grafo G){
    //Si G = NULL no hacemos nada, pero en cc destruimos
    if(G != NULL){
        assert(invrep(G));
        free(G->grados);
        free(G->colores);
        for(u32 i=0;i<G->n;i++){
            free(G->vert[i]);
        }
        free(G->vert);
        free(G);
        G=NULL;}
}


u32 NumeroDeVertices(Grafo G){
    assert(invrep(G));
    return G->n;
}

u32 NumeroDeLados(Grafo G){
    assert(invrep(G));
    return G->m;
}

u32 Delta(Grafo G){
    assert(invrep(G));
    return G->delta;
}

u32 Grado(u32 i, Grafo G){
    assert(invrep(G));
    u32 num_vertices = NumeroDeVertices(G);
    u32 res;
    if (i < num_vertices){res = G->grados[i];}
    else{res = 0;}
    return res;
}

color Color(u32 i, Grafo G){
    assert(invrep(G));
    u32 num_vertices = NumeroDeVertices(G);
    color res;
    if (i < num_vertices){res = G->colores[i];}
    else{res = UINT32_MAX;}
    return res;
}

u32 Vecino(u32 j, u32 i, Grafo G){
    //Asumimos que j>=0
    assert(invrep(G));
    u32 num_vertices = NumeroDeVertices(G);
    u32 grado_i = Grado(i, G);
    u32 res;
    if ((i >= num_vertices) || (j >= grado_i)){res = UINT32_MAX;}
    else{res = G->vert[i][j];}
    return res;
}

void AsignarColor(color x, u32 i, Grafo G){
    assert(invrep(G));
    u32 num_vertices = NumeroDeVertices(G);
    if(i < num_vertices){G->colores[i] = x;}
}

void ExtraerColores(Grafo G, color* Color){
    assert(invrep(G));
    u32 n = G->n;
    for(u32 i=0;i<n;i++){
        Color[i] = G->colores[i];
    }
}

void ImportarColores(color* Color, Grafo G){
    assert(invrep(G));
    u32 n = G->n;
    for(u32 i=0;i<n;i++){
        G->colores[i] = Color[i];
    }
}

