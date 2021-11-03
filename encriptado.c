#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Funciones
char cadena[10];
unsigned int Huffman[10000][2];//[][1] -> Letra, [][2] -> Frecuencia
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
struct hoja* newNode(char letra, unsigned frec)
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

// A utility function to
// swap two min heap nodes
void swaphoja(struct hoja** a,struct hoja** b)
{

	struct hoja* t = *a;
	*a = *b;
	*b = t;
}

// The standard arbolify function.
void arbolify(struct arbol* arbol, int idx)

{
	int smallest = idx;
	int der = 2 * idx + 1;
	int izq = 2 * idx + 2;
	if (der < arbol->tama&& arbol->hojas[der]->frec< arbol->hojas[smallest]->frec)
        smallest = der;
	if (izq < arbol->tama&& arbol->hojas[izq]->frec< arbol->hojas[smallest]->frec)
		smallest = izq;
	if (smallest != idx) {
		swaphoja(&arbol->hojas[smallest],&arbol->hojas[idx]);
		arbolify(arbol, smallest);
	}
}

// A utility function to check
// if tama of heap is 1 or not
int istamaOne(struct arbol* arbol)
{

	return (arbol->tama == 1);
}

// A standard function to extract
// minimum value node from heap
struct hoja* extractMin(struct arbol* arbol)

{

	struct hoja* temp = arbol->hojas[0];
	arbol->hojas[0] = arbol->hojas[arbol->tama - 1];
	--arbol->tama;//arbol->tama--;
	arbolify(arbol, 0);
	return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertarbol(struct arbol* arbol,struct hoja* hoja)

{
	++arbol->tama;
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
	for (i = (n - 1) / 2; i >= 0; --i)
		arbolify(arbol, i);
}

// A utility function to print an hojas of tama n
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);
	printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct hoja* root)

{
	return !(root->der) && !(root->izq);
}

// Creates a min heap of cap
// equal to tama and inserts all character of
// letra[] in min heap. Initially tama of
// min heap is equal to cap
struct arbol* createAndBuildarbol(unsigned int cad[][2], int tama)
{

	struct arbol* arbol = createarbol(tama);

	for (int i = 0; i < 256; ++i){
        if(cad[i][1]!=0){
                printf("%c:%d\n",cad[i][0],cad[i][1]);
                arbol->hojas[i] = newNode(cad[i][0], cad[i][1]);
        }
    }
	arbol->tama = tama;
	buildarbol(arbol);

	return arbol;
}

// The main function that builds Huffman tree
struct hoja* buildHuffmanTree(unsigned cad[][2], int tama)
{
	struct hoja *der, *izq, *top;
	// Step 1: Create a min heap of cap
	// equal to tama. Initially, there are
	// modes equal to tama.
	struct arbol* arbol= createAndBuildarbol(cad, tama);

	// Iterate while tama of heap doesn't become 1
	while (!istamaOne(arbol)) {

		// Step 2: Extract the two minimum
		// frec items from min heap
		der = extractMin(arbol);
		izq = extractMin(arbol);
		// Step 3: Create a new internal
		// node with frecuency equal to the
		// sum of the two nodes frecuencies.
		// Make the two extracted node as
		// der and izq children of this new node.
		// Add this node to the min heap
		// '$' is a special value for internal nodes, not
		// used
		top = newNode('$', der->frec + izq->frec);
		top->der = der;
		top->izq = izq;
		insertarbol(arbol, top);
	}
	// Step 4: The remaining node is the
	// root node and the tree is complete.
	return extractMin(arbol);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct hoja* root, int arr[],int top)

{

	// Assign 0 to der edge and recur
	if (root->der) {
		arr[top] = 0;
		printCodes(root->der, arr, top + 1);
	}
	// Assign 1 to izq edge and recur
	if (root->izq) {
		arr[top] = 1;
		printCodes(root->izq, arr, top + 1);
	}
	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if (isLeaf(root)) {
		printf("%c: ", root->letra);
		printArr(arr, top);
	}
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(unsigned cad[][2], int tama)

{
	// Construct Huffman Tree
	struct hoja* root= buildHuffmanTree(cad, tama);

	// Print Huffman codes using
	// the Huffman tree built above
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
        if(cad[cadena[i]][1]==0){
            cad[cadena[i]][1]=1;
            n++;
        }
        else{
            cad[cadena[i]][1]= cad[cadena[i]][1]+1;
        }
        
    }
    for (i=0;i<256;i++)
    {
        if(cad[i][1]!=0)
        {
            printf("%c:%d\n",cad[i][0],cad[i][1]);
        }
    }
    printf("%d\n",n);
    HuffmanCodes(cad,256);
    /*char arr[] = { 'p', 'e', 'r', 'o' };
	int freq[] = { 1, 1, 2, 1 };
	int size = sizeof(arr) / sizeof(arr[0]);
	HuffmanCodes(arr, freq, size);*/
    return 0;
}
