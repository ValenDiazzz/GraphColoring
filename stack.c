#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    struct _s_stack *next;
    unsigned int size;
};

stack stack_empty(){
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    stack p=NULL;
    p=malloc(sizeof(struct _s_stack));
    p->elem=e;
    p->next=s;
    if(s==NULL){
        p->size=1;
    }else{
        p->size=s->size +1;
    }

    return p;
}

stack stack_pop(stack s){
    if (s!=NULL){
        stack p;
        p=s;
        s=s->next;
        p->size--;
        free(p);
    }
    return s;
}

unsigned int stack_size(stack s){
    unsigned int len=0;
    if(s!=NULL){
        len=s->size;
    }
    return len;
}

stack_elem stack_top(stack s){
    if (s!=NULL){
        return s->elem;
    }else{
        printf("Error in stack_top: The list is empty.\n");
        exit(EXIT_FAILURE);
    }
}

bool stack_is_empty(stack s){
    return s==NULL;
}

stack_elem *stack_to_array(stack s){
    unsigned int size=stack_size(s);
    stack_elem *l=calloc(size,sizeof(stack_elem));
    stack p=s;
    for(unsigned int i=0;i<size;i++){
        l[size-1-i]=stack_top(p);
        p=p->next;
    }
    free(p);
    return l;
}

stack stack_destroy(stack s){
    if(s != NULL) {
        stack a, b;
        a = s;
        b = a->next;
        while(a != NULL) {
            free(a);
            a = b;
            if(a != NULL) {
                b = a->next;
            }
        }
        s = a;
    }
    return s;
}