#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct repeticion{
    char letra;
    int repeticiones;
    struct repeticion *siguiente;
};
struct arbol{
    int costo;//Costo sera el total de la suma de las raices
    int izq;
    int der;
    int padre;
};
//Funciones
char cadena[100000];
int cub [256];
int comparar(const void *, const void *);
struct repeticion *insertar(struct repeticion *, char,int);
struct arbol *crearArbol(struct arbol *,struct repeticion *,int);
void Seleccion (struct arbol *,int,int*,int*);
int main()
{

    int i = 0,n;
    char c;
    struct arbol *arbol=NULL;
    struct repeticion *rep=NULL;
    scanf("%[^\n]",&cadena);
    //scanf("%*[^\n]%*c");
    n = strlen(cadena);
    rep = (struct repeticion *)malloc(sizeof(struct repeticion));
    for(i=0;i<strlen(cadena);i++)
    {
        cub[cadena[i]]=cub[cadena[i]]+1;
    }
    for(i=0;i<256;i++)
    {
        if(cub[i]!=0)
        {
            rep = insertar(rep,i,cub[i]);
        }
    }
    arbol = crearArbol(arbol,rep,n);
    //qsort(rep,256,sizeof(struct repeticion),comparar);//Ordena menor a mayor
/* for(i=0;i<256;i++)
    {
        if(rep[i].repeticiones>0)
        {
            printf("%c %d\n",rep[i].letra,rep[i].repeticiones);
        }
    }*/
    while (rep->siguiente->siguiente!=NULL)
    {
        printf("%c %d\n",rep->letra,rep->repeticiones);
        rep = rep->siguiente;
    }
    return 0;
}

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
struct repeticion *insertar(struct repeticion *rep, char letra,int repeticiones){
    struct repeticion *nuevo = (struct repeticion *)malloc(sizeof(struct repeticion));
    nuevo->letra = letra;
    nuevo->repeticiones = repeticiones;
    nuevo->siguiente = rep;
    return nuevo;
}
struct arbol *crearArbol(struct arbol *arbol,struct repeticion *rep,int n){
    if(n<=1) return NULL; //La oracion unicamente es de un caracter
    int m,aux,auux,*aux1 = &aux, *aux2 = &auux;
    m = 2*n-1; //Nodos del arbol
    arbol = (struct arbol *)malloc(sizeof(struct arbol)*(m+1));
    for(int i=0;i<m;i++)
    {
        arbol[i].izq = 0;
        arbol[i].der = 0;
        arbol->padre = 0;
    }
    for(int i = 0 ; i<n; i++)
    {
        arbol[i].costo =rep[i].repeticiones;
    }
    //For que vaya de la cabecera a la ultima hoja
    while(n>1)
    {
        for(int i=0;i<n-1;i++)
        {
            Seleccion(arbol,n,aux1,aux2);
            arbol[aux].padre = i;
            arbol[auux].padre = i;
            arbol[i].izq = aux;
            arbol[i].der = auux;
            arbol[i].costo = arbol[aux].costo + arbol[auux].costo;
            printf("Costo: %d\n",arbol[i].costo);
        }
        n--;
    }
    return arbol;
}
void Seleccion(struct arbol *arbol,int n,int *aux1,int *aux2)
{
    int i,maxi,mini;
    *aux1 = 0;
    *aux2 = 0;
    maxi = 0;
    for(i=0;i<n;i++)
    {
        if(arbol[*aux1].costo > arbol[i].costo && arbol[i].padre == 0)
        {
            *aux1 = i;
        }
        if(arbol[maxi].costo < arbol[i].costo && arbol[i].padre == 0)
        {
            maxi = i;
        }
    }
    mini = arbol[*aux1].costo;
    arbol[*aux1].costo = arbol[maxi].costo;
    for(int i=0;i<n;i++)
    {
        if(arbol[*aux2].costo > arbol[i].costo && arbol[i].padre == 0)
        {
            *aux2 = i;
        }
    }
    arbol[*aux1].costo = mini;
    printf("Costos minimos %d %d\n",arbol[*aux1].costo,arbol[*aux2].costo);
}