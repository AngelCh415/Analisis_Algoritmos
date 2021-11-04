#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Funciones
char cadena[1000];
unsigned char cara[100];
unsigned int cubeta[100];
typedef struct hoja{
    char letra;
    int frec;
    struct hoja *izq;
    struct hoja *der;
}nodo;
typedef struct arbol{
    //tamaaño actual del arbol
    int tama;
    //Capacidad del arbol
    int cap;
    nodo ** hojas;
}arbol;

struct hoja* crearNodo(unsigned char letra, unsigned frec)
{
	struct hoja* temp = (struct hoja*)malloc(sizeof(struct hoja));
	temp->der = temp->izq = NULL;
	temp->letra = letra;
	temp->frec = frec;
	return temp;
}
unsigned char codigos[256][2];//[letra][0]->codigo de la letra, [letra][1]->codigo de la longitud (servira para binario)

// A utility function to create
// a min heap of given cap
struct arbol* createarbol(unsigned cap)
{

	struct arbol* arbol= (struct arbol*)malloc(sizeof(struct arbol));

	// current tama is 0
	arbol->tama = 0;

	arbol->cap = cap;

	arbol->hojas = (struct hoja**)malloc(arbol->cap * sizeof(struct hoja*));
	return arbol;
}

// The standard arbolify function.
void ordenar_arbol(struct arbol* arbol, int i)

{
	
	int smallest;
	struct hoja* temp;

	// if left child is smaller than root
	if (i*2 + 1 < arbol->tama && arbol->hojas[i*2 + 1]->frec < arbol->hojas[i]->frec)
		smallest = i*2 + 1;
	else
		smallest = i;

	// if right child is smaller than smallest so far
	if (i*2 + 2 < arbol->tama && arbol->hojas[i*2 + 2]->frec < arbol->hojas[smallest]->frec)
		smallest = i*2 + 2;

	// if smallest is not root
	if (smallest != i)
	{
		temp = arbol->hojas[smallest];
		arbol->hojas[smallest] = arbol->hojas[i];
		arbol->hojas[i] = temp;

		// recursively arbolify the smallest node
		ordenar_arbol(arbol, smallest);
	}
}



// A standard function to extract
// minimum value node from heap
struct hoja* pop(struct arbol* arbol)

{

	struct hoja* temp = arbol->hojas[0];
	arbol->hojas[0] = arbol->hojas[arbol->tama - 1];
	--arbol->tama;//arbol->tama--;
	ordenar_arbol(arbol, 0);
	return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertarbol(struct arbol* arbol,struct hoja* hoja)

{
	arbol->tama++;
	int i = arbol->tama - 1;
	while (i&& hoja->frec< arbol->hojas[(i - 1) / 2]->frec) {
		arbol->hojas[i] = arbol->hojas[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	arbol->hojas[i] = hoja;
}

// A standard function to build min heap
void buildarbol(struct arbol* arbol)

{
	int n = arbol->tama - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; i--){
		ordenar_arbol(arbol, i);
	}
}

// A utility function to print an hojas of tama n
void printArr(char arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);
	printf("\n");
}

struct arbol* createAndBuildarbol(struct hoja **hojas, int tama)
{

	struct arbol* arbol = createarbol(tama);
	arbol -> hojas = hojas;
	arbol->tama = tama;
	buildarbol(arbol);
	return arbol;
}


struct hoja* HuffmanTree(struct hoja ** hojas, int tama)
{
	struct hoja *der, *izq, *top;
	struct arbol* arbol= createAndBuildarbol(hojas, tama);
	while (arbol->tama != 1) {
		der = pop(arbol);
		izq = pop(arbol);
		top = crearNodo('\0', der->frec + izq->frec);
		top->der = der;
		top->izq = izq;
		insertarbol(arbol, top);
	}
	return pop(arbol);
}

void printCodes(struct hoja* root, int lon,int top)
{
	if (root->der) {
		printCodes(root->der, lon *2, top + 1);
	}
	if (root->izq) {
		printCodes(root->izq, lon *2+1, top + 1);
	}
	if (root->izq == NULL && root->der == NULL) {
		printf("%c:%d ", root->letra,lon);
		codigos[root->letra][0] = lon;
		codigos[root->letra][1] = top;
	}
}
//Reversa
char* reversestring(char *cadena,int tama)
{
	int i,j;
	char temp;
	for(i=0,j=tama-1;i<j;i++,j--)
	{
		temp=cadena[i];
		cadena[i]=cadena[j];
		cadena[j]=temp;
	}
	return cadena;
}
//Pasa de decimal a binario
char * decToBin(int num, int n)
{
	char *bin = (char *)malloc(sizeof(char) * n);
	int i = 0;
	while (num != 0) {
		bin[i++] = (num & 1) + '0';
		num = num >> 1;
	}
	while (i < n)
		bin[i++] = '0';
	return reversestring(bin, n);
}
void codificar(struct hoja* root,int tama)
{
	int aux = 10000000,recorrido = 8;//1<<7
	unsigned char ans = 0;
	char *arreB;
	printf("Codificando\n");
	for(int i = 0; i < tama; i++){
		arreB= decToBin(codigos[cara[i]][0], codigos[cara[i]][1]);
		int tamrepe = codigos[cara[i]][1];//r - 1 , o - 2
		printf("\n");
		printf("%c: Valor decimal %d, Codigo Binario ", cara[i],codigos[cara[i]][0]);
		for(int j = 0; j < tamrepe; j++){
			printf("%c",arreB[j]);
			if(arreB[j] == '1'){
				ans = ans | recorrido;
			}
			recorrido = recorrido >> 1;
			if(recorrido == 0){
				//se meteria a un archivo
				
				recorrido = 8;
				ans=0;
			}
		}
	}
	
}
void HuffmanCodes(nodo ** hojas, int tama)
{
	struct hoja* root= HuffmanTree(hojas, tama);
	int arr=0, top = 0;
	printCodes(root, arr, top);

	/*
	abc
	a: 1
	b: 10
	c: 11
	Posicion 0 es la a con longitud 1 con codificacion 1
	Posicion 1 es la b con longitud 2 con codificacion 10
	Posicion 2 es la c con longitud 2 con codificacion 11
	Recorrer la codificacion 
	Si encuentro un 1
		resultado va a hacer el corrimientio a la izquierda las veces que le toque, ejemplo
		si en la posicion 1 hay un 1 se recorre 7 veces a la izquierda, si en la posicion 2 hay un 1
		se recorre 6 veces a la izquierda, etc
	Cuando supere los8 bits es nueva linea
	*/
	codificar(root,tama);
}
int cub [256];
unsigned char cad [1000][2];//[0] = caracter, [1] = frecuencia
int main()
{
    int i = 0,n=0;

    scanf("%[^\n]",cadena);
    for(i=0;i<strlen(cadena);i++)
    {
        cad[cadena[i]][0]=cadena[i];
        cad[cadena[i]][1]= cad[cadena[i]][1]+1;
    }
	nodo **nodos;
	for (i = 0; i < 256; i++)
	{
		if(cad[i][1]>0)
		{
			cara[n] = cad[i][0];
			cubeta[n] = cad[i][1];
			n++;
		}
	}
	nodos = (nodo**)malloc(sizeof(nodo*)*n);
	i = 0;
	while (n>0)
	{ 
		nodos[i] = crearNodo(cara[i], cubeta[i]);
		n--;
		i++;
	}
    HuffmanCodes(nodos,i);
    return 0;
}
