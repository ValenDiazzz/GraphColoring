#include <stdio.h>
#include <stdlib.h>
#include "GREEDY.h"
#include "GRAPHFUN.h"
#include "AUXFUN.h"


void print_colores(Grafo G){
    for(u32 i=0;i<NumeroDeVertices(G);i++){
        printf("%u ",Color(i,G));
    }
    printf("\n");
}

int min_idx(u32 array[], int size){
    u32 min_= array[0];
    int idx= 0;

    for (int i=1; i<size; i++) {
        if (array[i]<min_) {
            min_= array[i];
            idx= i;
        }
    }
    return idx;
}


int main(void){

    Grafo G=ConstruirGrafo();
    u32 n= NumeroDeVertices(G);
    u32** Ordenes= malloc(5 * sizeof(u32*));
    u32* Orden;
    u32 n_coloreo[250];
    color** coloreo= malloc(250 * sizeof(color*));
    u32** grad_vert=malloc(n * sizeof(u32*));
    inicializar((int)n, grad_vert);
    
    for(unsigned int i=0;i<5;i++){
        Ordenes[i]=calloc(n, sizeof(u32));
    }
    for(unsigned int i=0;i<250;i++){
        coloreo[i]= calloc(n, sizeof(color));
    }

    
    //ordenes 1 y 2
    for(u32 j=0;j<n;j++){
        Ordenes[0][j]=j;
        Ordenes[1][j]=n-j-1;
    }
    
    //orden 3
    for(int j=((n+1)/2)-1;j>=0;j--){
        Ordenes[2][((n+1)/2)-1-j]=(u32) 2*j;
    }
    for(u32 j=0;j<((n+1)/2)-(n%2);j++){
        Ordenes[2][((n+1)/2) + j]=2*j + 1;
    }
    //orden 4
    for (u32 j=0;j<n;j++){
        grad_vert[j][0]= Grado(j,G);
        grad_vert[j][1]= j;
    }
    qsort(grad_vert,n,sizeof(u32*),comparar_enteros);
    
    for (u32 j= 0; j < n; j++){
        Ordenes[3][j]= grad_vert[j][1];
    }
    liberar(n,grad_vert);
    
    //orden 5: 2,....,n-1,0,1

    for (u32 j=2; j<n; j++){
        Ordenes[4][j-2]=j;
    }
    Ordenes[4][n-2]=0;
    Ordenes[4][n-1]=1;
    

    u32 col;
    char g;
    for(u32 i=0;i<5;i++){
        Orden= Ordenes[i];
        col=Greedy(G, Orden);
        print_colores(G);
        
        for(u32 j=0;j<50;j++){
            g= GulDukat(G, Orden);
            assert(g=='0');
            col= Greedy(G, Orden);
            printf("GulDukat: %u\n",col);
            
            g= ElimGarak(G, Orden);
            assert(g=='0');
            col= Greedy(G, Orden);
            printf("ElimGarak: %u\n", col);


            n_coloreo[j + 50*i]= col;
            ExtraerColores(G, coloreo[j + 50*i]);
        }
    }
    liberar(5,Ordenes);
    
    int min_pos= min_idx(n_coloreo,  250);
    
    color* min_coloreo= malloc(n * sizeof(color));
    for (u32 i=0; i<n; i++){
        min_coloreo[i]=coloreo[min_pos][i];
    }
    liberar(250,coloreo);
    ImportarColores(min_coloreo, G);
    free(min_coloreo);
    for(u32 j=0;j<500;j++){
        int random_number= rand();
        int eleccion= (random_number % 2 == 0)?1:0;

        if(eleccion){
            g= GulDukat(G, Orden);
            assert(g=='0');
            col= Greedy(G, Orden);
        }else{
            g= ElimGarak(G, Orden);
            assert(g=='0');
            col= Greedy(G, Orden);    
        }
        printf("%u - ",col);
    }
    printf("\n");
    
    
    DestruirGrafo(G);
    
    return EXIT_SUCCESS;
}