#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Funciones
char cadena[1000];
unsigned char cara[100];
unsigned int cubeta[100];
unsigned char Huffman[1000][2];//[][1] -> Letra, [][2] -> Frecuencia
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
void printArr(int arr[], int n)
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

void printCodes(struct hoja* root, int arr[],int top)
{
	if (root->der) {
		arr[top] = 0;
		printCodes(root->der, arr, top + 1);
	}
	
	if (root->izq) {
		arr[top] = 1;
		printCodes(root->izq, arr, top + 1);
	}

	if (root->izq == NULL && root->der == NULL) {
		printf("%c: ", root->letra);
		printArr(arr, top);
	}
}

void HuffmanCodes(nodo ** hojas, int tama)

{
	struct hoja* root= HuffmanTree(hojas, tama);
	int arr[100], top = 0;
	printCodes(root, arr, top);
}
int cub [256];
unsigned int cad [1000][2];
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
