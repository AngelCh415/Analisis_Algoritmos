#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct arbol {
    char letra;
    int repeticiones;
    struct arbol *izq;
    struct arbol *der;
    struct arbol *siguiente;
}nodo;

//Funciones
char cadena[100000];
int cub [256];
char frec [256];

nodo * crear_Cola(char letra, int repeticiones, nodo * izq, nodo *der){
        struct arbol *nuevo=(struct arbol*)malloc(sizeof(struct arbol));
        nuevo->letra=letra;
        nuevo->repeticiones=repeticiones;
        nuevo->siguiente=NULL;
        nuevo->izq=izq;
        nuevo->der=der;
        return nuevo;
}
void insertar_Cola(nodo **cabecera,char data, int prioridad, nodo *izq, nodo *der){
    if((*cabecera)==NULL){
        (*cabecera)=crear_Cola(data,prioridad,izq,der);
    }
    else{
        nodo * ini = (*cabecera);
        nodo * aux = crear_Cola(data, prioridad,izq,der);
        if((*cabecera)->repeticiones > prioridad){
            aux -> siguiente = (*cabecera);
            (*cabecera) = aux;
        }else{
            while(ini->siguiente != NULL && ini->siguiente->repeticiones < prioridad){
                ini = ini->siguiente;
            }
            aux->siguiente = ini->siguiente;
            ini->siguiente = aux;
    }
    }
}
//Saca el caracter
int peek(nodo** head)
{
    return (*head)->letra;
}
int isEmpty(nodo** head)
{
    return (*head) == NULL;
}
void pop(nodo** head)
{
    nodo* temp = *head;
    (*head) = (*head)->siguiente;
    free(temp);
}
//Saca el costo/prioridad
int peek2(nodo** head)
{
    return (*head)->repeticiones;
}
/*void guardarcodigos(nodo* head, char recorrido[]){
    if(head==NULL){
        return;
    }
    if(head->letra !='$'){
        frec[head->letra] = (char *)recorrido;
    } 
    guardarcodigos(head->izq, recorrido + '0');
    guardarcodigos(head->der, recorrido + '1');
}*/
void imprimirArbol(nodo* head){
    if(head==NULL){
        return;
    }
    if(head->letra !='$'){
        printf("%c: %d",head->letra, head->repeticiones);
    } 
    imprimirArbol(head->izq);
    imprimirArbol(head->der);
}
    
int main()
{
    nodo *cola=NULL, *arbolHuff;
    int i = 0,n,lc=0;
    scanf("%[^\n]",&cadena);
    n = strlen(cadena);
    for(i=0;i<strlen(cadena);i++)
    {
        cub[cadena[i]]=cub[cadena[i]]+1;
    }
    for (i=0;i<256;i++)
    {
        if(cub[i]!=0)
        {
            printf("%c: %d\n",i,cub[i]);
        }
    }
    for(i=0;i<256;i++)
    {
        if(cub[i]!=0)
        {
            insertar_Cola(&cola,i,cub[i],NULL,NULL);
            lc=lc+1;
        }
    }
    while(lc>1){
        nodo *a = cola;
        int auxa=peek2(&a);
        pop(&cola);
        lc --;
        nodo *b = cola;
        int auxb=peek2(&b);
        pop(&cola);
        lc--;
        int prio = 0;
        prio = auxa+auxb;
        insertar_Cola(&cola, '$',prio,a,b);
        lc++;
    }
    arbolHuff = cola;
    imprimirArbol(arbolHuff);
    return 0;
}
