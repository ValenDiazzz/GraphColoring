#include "GREEDY.h"
#include "AUXFUN.h"

#define UINT32_MAX 4294967295U; //2^32 - 1


u32 Greedy(Grafo G, u32* Orden){
    u32 n;
    color* colores;
    u32* pos_color;
    u32 v, c, grad, nb, delta;
    u32 res= 1;

    n= NumeroDeVertices(G);
    
    //Chequeo de que sea una biyección.
    if(!biyeccion(n, Orden)){
        return UINT32_MAX;
    }
    
    colores = calloc(n, sizeof(color));
    v= Orden[0];
    colores[v]=1;
    delta=Delta(G);
    for(unsigned int i=1;i<n;i++){
        v= Orden[i];
        pos_color= calloc((delta+1), sizeof(color));
        grad= Grado(v,G);

        //Se fija los colores de los vecinos
        for(u32 j=0;j<grad;j++){
            nb=Vecino(j,v,G);
            pos_color[colores[nb]]= 1;
        }
        
        //Busca el minimo color asignable
        c=1;
        while(c<delta+1 && pos_color[c]!=0){
            c++;
        }
        colores[v]=c;

        res= res>c?res:c;
        free(pos_color);
    }

    ImportarColores(colores, G);
    free(colores);
    return res;
}


char GulDukat(Grafo G,u32* Orden){
    u32 n = NumeroDeVertices(G);
    
    int cota = cant_colores(G);
    int cota1 = (int)(cota/4);
    int cota2 = (int)(cota/2) - cota1;
    int cota3 = cota - cota1 -cota2;

    
    u32 ** grado_div4 = calloc(cota1, sizeof(u32 *));
    u32 ** grado_pares = calloc(cota2, sizeof(u32 *));
    u32 ** grado_impares = calloc(cota3, sizeof(u32 *));
    u32 * grado_min_par = calloc(cota2, sizeof(u32 *));
    stack * vert_ord= malloc(cota * sizeof(u32 *));

    inicializar(cota1, grado_div4);
    inicializar(cota2, grado_pares);
    inicializar(cota3, grado_impares);
    inicializar_stack(cota, vert_ord);
    
    color col_vertice;
    u32 grad_vertice;

    for(u32 i = 0; i < n; i++){

        col_vertice = Color(i,G);

        if(col_vertice == 0){// Si col_vertice = 0, entonces no tengo un coloreo propio
            return '1'; 
        }

        grad_vertice = Grado(i,G);
        
        if(col_vertice % 4 == 0){
            grado_div4[col_vertice/4 - 1][0] = max1(grado_div4[col_vertice/4 - 1][0], grad_vertice);
            grado_div4[col_vertice/4 - 1][1] = col_vertice;
            vert_ord[col_vertice-1] = stack_push(vert_ord[col_vertice-1], i);
            
        } else if(col_vertice % 2 == 0){
            grado_pares[(int)(col_vertice/4)][0] = max1(grado_pares[(int)(col_vertice/4)][0], grad_vertice);
            grado_min_par[(int)(col_vertice/4)] = min(grado_min_par[(int)(col_vertice/4)], grad_vertice);
            grado_pares[(int)(col_vertice/4)][1] = col_vertice;
            vert_ord[col_vertice-1] = stack_push(vert_ord[col_vertice-1], i);

        } else {
            grado_impares[(col_vertice-1) / 2][0] = min(grado_impares[(col_vertice-1) / 2][0], grad_vertice);
            grado_impares[(col_vertice-1) / 2][1] = col_vertice;
            vert_ord[col_vertice-1] = stack_push(vert_ord[col_vertice-1], i);
        }
    }

    for(int i=0; i<cota2; i++){
        grado_pares[i][0] =  grado_pares[i][0] + grado_min_par[i];
    }


    qsort(grado_div4, cota1, sizeof(grado_div4[0]), comparar_enteros);
    qsort(grado_pares, cota2, sizeof(grado_pares[0]), comparar_enteros);
    qsort(grado_impares, cota3, sizeof(grado_impares[0]), comparar_enteros);
   
    u32 cont=0;
    cont = agregar_vertices_gul(cota1, grado_div4, vert_ord, Orden, cont);
    cont = agregar_vertices_gul(cota2, grado_pares, vert_ord, Orden, cont);
    cont = agregar_vertices_gul(cota3, grado_impares, vert_ord, Orden, cont);
    
    if(cont != n){ // No se agregaron todos los vértices a Orden
        return '1';
    }

    liberar_stack(cota, vert_ord);
    liberar(cota1, grado_div4);
    liberar(cota2, grado_pares);
    liberar(cota3, grado_impares);
    free(grado_min_par);
    
    return '0';
}  


char ElimGarak(Grafo G,u32* Orden){
    u32 n = NumeroDeVertices(G);
 
    int cota = cant_colores(G);

    u32 ** grado_color = calloc(cota, sizeof(u32 *));
    stack * vert_ord = malloc(cota * sizeof(u32 *));
    
    inicializar(cota, grado_color);
    inicializar_stack(cota, vert_ord);

    
    color col_vertice;

    for(u32 i = 0; i < n; i++){

        col_vertice = Color(i,G);

        if(col_vertice == 0){ // Si col_vertice = 0, entonces no es un coloreo propio
            return '1'; 
        }
        
        if(col_vertice != 1 && col_vertice != 2){
            grado_color[col_vertice - 3][0]++;
            grado_color[col_vertice - 3][1] = col_vertice;
        }
        
        vert_ord[col_vertice-1] = stack_push(vert_ord[col_vertice-1], i);
    }

    qsort(grado_color, cota - 2, sizeof(grado_color[0]), comparar_enteros);


    u32 cont = n - stack_size(vert_ord[0]) - stack_size(vert_ord[1]);
    cont = agregar_vertices_EG(cota - 2, grado_color, vert_ord, Orden, cont);

    if(cont != n){// No se agregaron todos los vértices a Orden
        return '1';
    }
    
    liberar_stack(cota, vert_ord);
    liberar(cota, grado_color);

    return '0';
}  
