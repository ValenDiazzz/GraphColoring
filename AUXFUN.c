#include "AUXFUN.h"

int max1(u32 a, u32 b){
    return a > b ? a : b;
}

int min(u32 a, u32 b){
    if(a==0){// está inicializado con calloc y los grafos son conexos
        return b;
    }else{
        return a < b ? a : b;
    }
}


int comparar_enteros(const void *a, const void *b) {
    const u32 *elem1 = *(const u32 **)a;
    const u32 *elem2 = *(const u32 **)b;

    if ((elem1)[0] < (elem2)[0]) {
        return 1; // Indica que elem1 es mayor que elem2
    } else if ((elem1)[0] > (elem2)[0]) {
        return -1; // Indica que elem1 es menor que elem2
    } else {
        return 0; // Indica que son iguales
    }
}

bool biyeccion(u32 n,u32* Orden){
    int chequeo[n]; 
    for(unsigned int i = 0; i < n; i++){
        chequeo[i] = i;
    }

    int aux;
    for(unsigned int j = 0; j<n;j++){
        aux = Orden[j];
        if(chequeo[aux] == aux){
            chequeo[aux] = -1;
        }
    }

    unsigned int i = 0;
    while(i < n && chequeo[i] == -1){
        i++;
    }

    return i == n;
}


u32 agregar_vertices_gul(int cota, u32 **grado, stack *list_vert, u32 *orden, u32 cont){
    color col_vertice;
    u32 vertice;
    
    // Sabemos que es orden n, cota y len(list_vert) están relacionados linealmente
    for(int i=0; i <cota; i++){
        col_vertice= grado[i][1];
        
        //Si hay menos de cota colores, col_vertice es 0 y no hay que agregar nada más a Orden
        if(col_vertice== 0){
            break;
        }
        
        while(!stack_is_empty(list_vert[col_vertice-1])){
            vertice = (u32)stack_top(list_vert[col_vertice-1]);
            orden[cont] = vertice;
            list_vert[col_vertice-1]=stack_pop(list_vert[col_vertice-1]);
            cont++; 
        }
    }
    return cont;
}

u32 agregar_vertices_EG(int cota, u32 **grado, stack *list_vert, u32 *orden, u32 cont){
    color col_vertice;
    u32 vertice;
    u32 copia_cont = cont;

    // Sabemos que es orden n, cota y len(list_vert) están relacionados linealmente
    for(int i=0; i <cota; i++){
        col_vertice=grado[i][1];
    
        //Si hay menos de cota colores, col_vertice es 0 y no hay que agregar nada más a Orden
        if(col_vertice== 0){
            break;
        }
        
        while(!stack_is_empty(list_vert[col_vertice-1])){
            vertice = (u32)stack_top(list_vert[col_vertice-1]);
            
            //orden[0]...orden[cont-1] colores con menor vértice
            orden[cont - 1] = vertice;
            list_vert[col_vertice-1]=stack_pop(list_vert[col_vertice-1]);
            cont--; 
        }
    }
    
    for(int j = 1; j >= 0; j--){
        while(!stack_is_empty(list_vert[j])){
            vertice = (u32)stack_top(list_vert[j]);
            
            //orden[cont]...orden[n-1] primero los de color 2, luego los de color 1
            orden[copia_cont] = vertice;
            list_vert[j]=stack_pop(list_vert[j]);
            copia_cont++; 
        }
    }

    return copia_cont;
}


void inicializar(int cota, u32 **lista){
    for(int i=0; i<cota;i++){
        lista[i] = calloc(2, sizeof(u32));
    }
}

void inicializar_stack(int cota, stack *s){
    for(int i = 0; i < cota; i++){
        s[i]= stack_empty();
    }
}

void liberar(int cota, u32** lista){
    for(int i = 0; i < cota; i++){
        free(lista[i]);
    }
    free(lista);
}

void liberar_stack(int cota, stack *s){
    for(int i=0; i<cota; i++){
        stack_destroy(s[i]);
    }
    free(s);
}

int cant_colores(Grafo G){
    color cant=0;
    u32 n = NumeroDeVertices(G);
    color col_vert; 
    for(u32 i=0; i<n; i++){
        col_vert = Color(i,G);
        cant = cant > col_vert ? cant : col_vert;
    }
    return (int) cant;
}