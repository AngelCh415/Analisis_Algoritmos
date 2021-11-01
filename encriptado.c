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
nodo * crear_Cola(char letra, int repeticiones){
        struct arbol *nuevo=(struct arbol*)malloc(sizeof(struct arbol));
        nuevo->letra=letra;
        nuevo->repeticiones=repeticiones;
        nuevo->siguiente=NULL;
        nuevo->izq=NULL;
        nuevo->der=NULL;
        return nuevo;
}
void insertar_Cola(nodo **cabecera,char data, int prioridad){
    if((*cabecera)==NULL){
        (*cabecera)=crear_Cola(data,prioridad);
    }
    else{
        nodo * ini = (*cabecera);
        nodo * aux = crear_Cola(data, prioridad);
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
int peek2(nodo** head)
{
    return (*head)->repeticiones;
}
int main()
{
    nodo *cola=NULL;
    int i = 0,n;
    scanf("%[^\n]",&cadena);
    n = strlen(cadena);
    for(i=0;i<strlen(cadena);i++)
    {
        cub[cadena[i]]=cub[cadena[i]]+1;
    }
    for(i=0;i<256;i++)
    {
        if(cub[i]!=0)
        {
            insertar_Cola(&cola,i,cub[i]);
        }
    }
    while (!isEmpty(&cola)) {
        printf("%c: %d\n", peek(&cola), peek2(&cola));
        pop(&cola);
    }
    return 0;
}
/*
#include<bits/stdc++.h>
using namespace std;
int main() {
    priority_queue<arbol> pq;

    vector<arbol> v;

    for(arbol i: v){
        pq.push(i);
    }
    while (pq.size()>1) {
        arbol a = pq.top();
        pq.pop();
        arbol b = pq.top();
        pq.pop();
        pq.push(combina(a,b));
    }
    arbol final = pq.top();
    return 0;
}
*/