#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct repeticion{
    char letra;
    int repeticiones;
};
struct arbol{
    struct repeticion *info;
    int costo;
    struct arbol *izq;
    struct arbol *der;
};
//Funciones
struct arbol *crear_arbol(struct repeticion *info, int costo, struct arbol *izq, struct arbol *der);
struct arbol *insertar_arbol(struct arbol *arbol, struct repeticion *info, int costo);
struct arbol *ordenar_arbol(struct arbol *arbol);
void imprimir_arbol(struct arbol *arbol);
void actualizar_costo(struct arbol *arbol);

struct repeticion rep[256];
    char cadena[100000];
    int cub [256];
int comparar(const void *a, const void *b){
    struct repeticion *x = (struct repeticion *)a;
    struct repeticion *y = (struct repeticion *)b;
    if(x->repeticiones < y->repeticiones)
        return -1;
    else if(x->repeticiones > y->repeticiones)
        return 1;
    else
        return 0;
}
int main()
{
    int i = 0;
    struct arbol *arbol=NULL;
    scanf("%[^\n]",&cadena);
    for(i=0;i<strlen(cadena);i++)
    {
        cub[cadena[i]]=cub[cadena[i]]+1;
    }
    for(i=0;i<256;i++)
    {
        if(cub[i]!=0)
        {  
            rep[i].letra=i;
            rep[i].repeticiones=cub[i];
        }
    }
    qsort(rep,256,sizeof(struct repeticion),comparar);
    for (i=0;i<256;i++)
    {
        if(rep[i].repeticiones!=0)
        {
            arbol=insertar_arbol(arbol,&rep[i],rep[i].repeticiones);
            arbol = ordenar_arbol(arbol);
        }
    }
    imprimir_arbol(arbol);
}
struct arbol *crear_arbol(struct repeticion *info, int costo, struct arbol *izq, struct arbol *der){
    struct arbol *nuevo=(struct arbol*)malloc(sizeof(struct arbol));
    nuevo->info=info;
    nuevo->costo=costo;
    nuevo->izq=izq;
    nuevo->der=der;
    return nuevo;
}
struct arbol *insertar_arbol(struct arbol *arbol, struct repeticion *info, int costo){
    if(arbol==NULL){
        return crear_arbol(info, costo, NULL, NULL);
    }
    if(costo<arbol->costo){
        arbol->izq=insertar_arbol(arbol->izq, info, costo);
    }else{
        arbol->der=insertar_arbol(arbol->der, info, costo);
    }
    return arbol;
}
//Actualizar costo sumando los costos actuales de los hijos
void actualizar_costo(struct arbol *arbol){
    if(arbol==NULL){
        return;
    }
    if(arbol->izq!=NULL){
        arbol->costo+=arbol->izq->costo;
    }
    if(arbol->der!=NULL){
        arbol->costo+=arbol->der->costo;
    }
    actualizar_costo(arbol->izq);
    actualizar_costo(arbol->der);
}

//ordenamiento por costo
struct arbol *ordenar_arbol(struct arbol *arbol){
    if(arbol==NULL){
        return NULL;
    }
    //actualizar_costo(arbol);
    if(arbol->izq!=NULL){
        arbol->izq=ordenar_arbol(arbol->izq);
    }
    if(arbol->der!=NULL){
        arbol->der=ordenar_arbol(arbol->der);
    }
    if(arbol->izq!=NULL && arbol->der!=NULL){
        if(arbol->izq->costo>arbol->der->costo){
            struct arbol *aux=arbol->izq;
            arbol->izq=arbol->der;
            arbol->der=aux;
        }
    }
    return arbol;
}
//imprimir arbol en inorden
void imprimir_arbol(struct arbol *arbol){
    if(arbol==NULL){
        return;
    }
    imprimir_arbol(arbol->izq);
    printf("%c %d\n",arbol->info->letra,arbol->costo);
    imprimir_arbol(arbol->der);
}
