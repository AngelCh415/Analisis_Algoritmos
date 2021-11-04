#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

//Funciones
char cadena[1000];
unsigned char cara[100];
unsigned int cubeta[100];
int n,i,repeticiones,tamanoPob;
    unsigned char caracter;
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
void decode(struct hoja *arbol){
    printf("\n");
    FILE *fp = fopen("decode.dat", "rb");
    FILE *fp2 = fopen("decodificado.txt", "wb");
    nodo *temp = arbol;
    while(tamanoPob){ 
        unsigned char aux = fgetc(fp);
        for(i=7; i>=0;i--){
            if(CONSULTARBIT(aux,i))
            {
                temp = temp->der;
            }
            else if(!CONSULTARBIT(aux,i))
            {
                temp = temp->izq;
            }
            if(temp->izq ==NULL &&temp->der==NULL)
            {
                fwrite(&(temp->letra),1,sizeof(temp->letra),fp2);
                tamanoPob--;
                temp = arbol;
            }
        }
    }
}
void HuffmanCodes(nodo ** hojas, int tama)
{
	struct hoja* root= HuffmanTree(hojas, tama);
	int arr=0, top = 0;
	printCodes(root, arr, top);
    decode(root);
}
int cub [256];

int main()
{
    
    int capacidad = 100;
    //Leer archivo
    FILE *archivo;
    archivo = fopen("ejemplo.txt", "r");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }
    nodo ** nodos = (nodo **)malloc(sizeof(nodo) * 100);
    for (i = 0; i < capacidad; i++)
    {
        fscanf(archivo, "%d", &caracter);
        fscanf(archivo, "%d", &repeticiones);
        tamanoPob += repeticiones;
        nodos[i] = crearNodo(caracter, repeticiones);
        printf("%d - %d\n", caracter, repeticiones);
    }
    fclose(archivo);
    //Crear arbol
    HuffmanCodes(nodos, capacidad);
    return 0;
}
