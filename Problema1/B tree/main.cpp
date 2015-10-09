#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <io>
#include <fcntl.h>
//#include <sys\stat.h>
#include <ctime>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>
#include<string>
#include<sstream>

#define NIL (-1L)
#define SIZE 100000//DE CUANTOS NUMEROS DESEAS HACER EL ARBOL
#define MAXNUM 999999//RANGO DE LOS NUMEROS ALEATORIOS

static const int M = 4;
static const int MM = 16;

using namespace std;

typedef enum {
   INSERTNOTCOMPLETE, SUCCESS, DUPLICATEKEY,
   UNDERFLOW, NOTFOUND
} status;


//DECLACACION DE STRUCT NODO //ARREGLO DE DATOS
		typedef struct{
		  int cnt;
		  int key[MM];//ELEMENTOS MAXIMOS
		  long ptr[MM+1];//HIJOS MAXIMOS
		} node;

//DECLARACION DE VARIABLES
		node rootnode;//VERTICE RAIZ
		long start[2], root=NIL, freelist=NIL;//NUMEROTES
		FILE *fptree; //ARCHIVO

		void error(char *str);
		void readnode(long t, node *pnode);
		void writenode(long t, node *pnode);
		long getnode(void);
		void found(long t,  int i);
		void notfound(int x);
		int binsearch(int x, int *a, int n);
		status search(int x);
		status ins(int x, long t, int *y, long *u);
		status insert(int x);
		void freenode(long t);
		void rdstart(void);
		void wrstart(void);
		status del(int x, long t);
		status delnode(int x);
		void printtree(long t);
		void printOrdered(long t);
		void printOrderedAscending(long t);
		void readRandom(string,int[],int);
		int* data;
		int tam;


int main()
{
    /** EJEMPLO DE EJECUCION

	clock_t sC, fC, sC2, fC2, sC3, fC3;

	int x, code=0; //DATO DEL NODO Y AUX VAR
	char ch, treefilnam[51], inpfilnam[51]; //CHAR DE OPCIONES

	FILE *fpinp;
	 // FILE *fpinp;
	 srand(time(NULL));

	 printf("Ingrese el nombre con extencion, anterior o nuevo, del archivo para el Arbol b:  ");
	 scanf("%50s", treefilnam);

	 sC = clock();

///////GENERAR ARBOL/////////////////////////////////////////////////////////////////////////////////////
	 fptree = fopen(treefilnam, "r+b");
	 if (fptree == NULL) {
		fptree = fopen(treefilnam, "w+b");
		wrstart();
		printtree(root);
	 }
	 else{
		  rdstart();
		  printtree(root);
	 }
	 (void)getchar();
	 puts("");
	 if (code)
		printtree(root);
  	fC = clock();


//////REALIZAR 10 BUSQUEDAS ALEATORIAS///////////////////////////////////////////////////////////////////////

	//tomar tiempo inicio de busquedas
	sC2 = clock();

	for (int i =0; i < 10; i++)
	 {
		sC3 = clock();//tiempo inicial que demora una busqueda, se toma unicamente de la ultima busqueda
		int hipHipHurraNumRandom = rand() % MAXNUM;
		printf("Buscar: ");
		printf("%d", hipHipHurraNumRandom);
		printf("\n");
		 if (search(hipHipHurraNumRandom) == NOTFOUND)//BUSCA
								  puts("No se encontro\n");
		 fC3 = clock();//tiempo final que demora una busqueda, se toma unicamente de la ultima busqueda
	 }

	//tomar tiempo final de busquedas
	 fC2 = clock();


	 printf("\nTiempo que demora en realizar el arbol B: %d segundos\n\n", (fC-sC)/CLOCKS_PER_SEC);
	 printf("\nTiempo que demora en realizar las 10 busquedas: %f segundos\n\n", (fC2-sC2)/CLOCKS_PER_SEC);
	 printf("\nTiempo que demora en realizar las 1 busqueda: %Lf segundos\n\n", (fC3-sC3)/CLOCKS_PER_SEC);


/////SEGUNDA PREGUNTA//////////////////////////////////////////////////////////////////////////////////////////////////////////
	 printf("Desea leer datos de un archivo? (S/N): ");
	 scanf(" %c", &ch); //SEGUNDA CAPTURA
	 while (getchar() != '\n');   /// Rest of line skipped

/////LEER UN ARCHIVO    IF (ch==Y) //////////////////////////////////////////////////////////////////////////////////////////////////////////
	 if (toupper(ch) == 'S'){
		printf("Nombre del archivo: ");
		scanf("%50s", inpfilnam);
		if ((fpinp = fopen(inpfilnam, "r")) == NULL)
		  error("archivo no disponible");
		while (fscanf(fpinp, "%d", &x) == 1)
			 insert(x);
		fclose(fpinp);
		printtree(root);
	 }

//////ELSE  ->	if (ch == 'N') //////////////////////////////////////////////////////////////////////////////////////////////////

	 //////DRAW|UPDATE (se repite continuamente)//////

	for ( ; ; ) {
		//INSTRUCCIONES DE USO
		printf("\nIngrese un entero, seguido por la letra I, B, o S (I para insertar,"
			"B para Borrar y S para Buscar). Asimismo ingrese O para imprimir el arbol ordenado\ndescendentemente "
	  "o ingrese A para imprimir el arbol ascendentemente. Para salir presione Q. Porfavor realici su seleccion: ");
		code = scanf("%d", &x);//ENTRADA INTEGER
		scanf(" %c", &ch);//ENTRADA STRING
		ch = toupper(ch);//MAYUSCULAS <-> MINUSCULAS

		//SI HAY NUMERO, INSERTO, BORRO O BUSCO.
		if (code)
			switch (ch) {

				  case 'I': if (insert(x) == SUCCESS)//INSERTA
									printtree(root);//Imprime el arbol resultante despu�s de insertar
								break;//VUELVE AL UPDATE

				  case 'B': if (delnode(x) == SUCCESS)//BORRA
								  printtree(root);//Imprime el arbol resultante despu�s de borrar
								else
								 puts("Not found");
								break;

				  case 'S': if (search(x) == NOTFOUND)//BUSCA
								  puts("Not found");
								break;
			}

		//SI NO HAY NUMERO, IMPRIMO O CIERRO.
			else
			  if (ch == 'O')
			  {
				  printOrdered(root);//IMPRIME DESCENDENTE
				  printf("\n");
			  }
			  if (ch == 'A')
			  {
				  printOrderedAscending(root);//IMPRIME ACENDENTE
				  printf("\n");
			  }
			  if (ch == 'Q')
				 break;//ROMPE EL CICLO CONTINUO (DRAW|UPDATE) -> for
	}//for

  wrstart();
  fclose(fptree);
  */


  /** ANALIZAR BUSQUEDA **/


    int N = 100000;
    tam = N;
    data = new int[N];
    readRandom("data.txt",data,N);
    fptree = fopen("disc_tree", "w+b");
     wrstart();

    int M = 10;
    int data2[M];
    readRandom("search.txt",data2,M);


    for (int i = 0; i < M; i++){
        float start = clock();
        search(data2[i]);
        cout << "TIME " << i+1 << " (" << data2[i] << "): " <<(clock() - start)/CLOCKS_PER_SEC << "s" << endl;
    }




  return(0);//FIN
}


void readRandom(string fileName,int data[],int N)
{
    ifstream read(fileName.c_str());
    int n,i;
    for(int i = 0; i < N; i++)
        read >> data[i];
}



void error(char *str)
{
	printf("\nError: %s\n", str);
	exit(1);
}

void readnode(long t, node *pnode)
{
  if (t == root){
	 *pnode = rootnode;
	  return;
  }
  if (fseek(fptree, t, SEEK_SET))
	 error("fseek in readnode");
  if (fread(pnode, sizeof(node), 1, fptree) == 0)
	 error("fread in readnode");
}

void writenode(long t, node *pnode)
{
	if (t == root)
		rootnode = *pnode;
	if (fseek(fptree, t, SEEK_SET))
	  error("fseek in writenode");
	if (fwrite(pnode, sizeof(node), 1, fptree) == 0)
	  error("fwrite in writenode");
}

long getnode(void)
{
long t;
node nod;

  if (freelist == NIL) {
	 if (fseek(fptree, 0L, SEEK_END))
		 error("fseek in getnode");
  t = ftell(fptree);
  writenode(t, &nod);  }         /*  Allocate space on disk  */

  else{
	  t = freelist;
		readnode(t, &nod);             /*  To update freelist      */
		freelist = nod.ptr[0];
 }
 return(t);
}

void found(long t,  int i)
{
node nod;

	printf("Se enconto en la posicion %d del nodo que contiene:  ", i);
	readnode(t, &nod);
	for (i=0; i < nod.cnt; i++)
		printf("  %d", nod.key[i]);

	puts("");
	printf("\n");
}

void notfound(int x)
{
	printf("Item %ld not found\n\n", x);
}

int binsearch(int x, int *a, int n)
{
int i, left, right;

	if (x <= a[0])
		return 0;
	if (x > a[n-1])
		 return n;
	left = 0;
	right = n-1;
	while (right -  left > 1){
		  i = (right + left)/2;
		  if (x <= a[i])
			  right = i;
		  else
			 left = i;
	}
	return(right);
}

status search(int x)
{
int i, j,*k, n;
node nod;
long t = root;

	//puts("Camino por el que se busco:");
	while (t != NIL){
		  readnode(t, &nod);
		  k = nod.key;
		  n = nod.cnt;
		  for (j=0; j < n; j++)
			wrstart();
		  puts("");
		  i = binsearch(x, k, n);
		  if (i < n && x == k[i]){
			  found(t,i);
			  return(SUCCESS);
		  }
		  t = nod.ptr[i];
	}
	return(NOTFOUND);
}

/*
	Insert x in B-tree with root t.  If not completely successful, the
	 integer *y and the pointer *u remain to be inserted.
*/
status ins(int x, long t, int *y, long *u)
{
 long tnew, p_final, *p;
 int i, j, *n, k_final, *k, xnew;
 status code;
 node nod, newnod;

	/*  Examine whether t is a pointer member in a leaf  */
	if (t == NIL){
		*u = NIL;
		 *y = x;
		 return(INSERTNOTCOMPLETE);
	}
	readnode(t, &nod);
	n = & nod.cnt;
	k = nod.key;
	p = nod.ptr;
	/*  Select pointer p[i] and try to insert x in  the subtree of whichp[i]
	  is  the root:  */
	i = binsearch(x, k, *n);
	if (i < *n && x == k[i])
	  return(DUPLICATEKEY);
	code = ins(x, p[i], &xnew, &tnew);
	if (code != INSERTNOTCOMPLETE)
	  return code;
	/* Insertion in subtree did not completely succeed; try to insert xnew and
	tnew in the current node:  */
	if (*n < MM){
		i = binsearch(xnew, k, *n);
		for (j = *n; j > i; j--){
			k[j] = k[j-1];
			p[j+1] = p[j];
		}
	  k[i] = xnew;
	  p[i+1] = tnew;
	  ++*n;
	  writenode(t, &nod);
	  return(SUCCESS);
	}
	/*  The current node was already full, so split it.  Pass item k[M] in the
	 middle of the augmented sequence back through parameter y, so that it
	 can move upward in the tree.  Also, pass a pointer to the newly created
	 node back through u.  Return INSERTNOTCOMPLETE, to report that insertion
	 was not completed:    */
	if (i == MM){
	  k_final = xnew;
	  p_final = tnew;
	 }else{
		  k_final = k[MM-1];
		  p_final = p[MM];
		  for (j=MM-1; j>i; j--){
			  k[j] = k[j-1];
			  p[j+1] = p[j];
		  }
			k[i] = xnew;
			p[i+1] = tnew;
	}
	*y = k[M];
	*n = M;
	*u = getnode(); newnod.cnt = M;
	for (j=0; j< M-1; j++){
		newnod.key[j] = k[j+M+1];
		newnod.ptr[j] = p[j+M+1];
	}
	newnod.ptr[M-1] = p[MM];
	newnod.key[M-1] = k_final;
	newnod.ptr[M] = p_final;
	writenode(t, &nod);
	writenode(*u, &newnod);
	return(INSERTNOTCOMPLETE);
}

/*  Driver function for node insertion, called only in the main function.

	 Most of the work is delegated to 'ins'.
*/
status insert(int x)
{
long tnew, u;
int xnew;
status code = ins(x, root, &xnew, &tnew);

  if (code == DUPLICATEKEY){}
	 //printf("=> El elemento %d no se puede insertar porque el numero ya se habia insertado, seria redundante insertarlo\n\n", x);
  else
	 if (code == INSERTNOTCOMPLETE){
		u = getnode();
		rootnode.cnt = 1;
		rootnode.key[0] = xnew;
		rootnode.ptr[0] = root;
		rootnode.ptr[1] = tnew;
		root = u;
		writenode(u, &rootnode);
		code = SUCCESS;
	}
	return(code);     /*  return value: SUCCESS  of DUPLICATEKEY  */
}

void freenode(long t)
{
node nod;

  readnode(t, &nod);
  nod.ptr[0] = freelist;
  freelist = t;
  writenode(t, &nod);
}

void rdstart(void)
{

  if (fseek(fptree, 0L, SEEK_SET))
	 error("fseek in rdstart");
  if (fread(start, sizeof(long), 2, fptree) == 0)
	 error("fread in rdstart");
  readnode(start[0], &rootnode);
  root = start[0];
  freelist = start[1];
}

void wrstart(void)
{
  start[0] = root;
  start[1] = freelist;
  if (fseek(fptree, 0L, SEEK_SET))
	  error("fseek in wrstart");
  if (fwrite(start, sizeof(long), 2, fptree) == 0)
	  error("fwrite in wrstart");
  if (root != NIL)
	  writenode(root, &rootnode);

  	for (int i =0; i < tam; i++)
	 {
		insert(data[i]);
	 }
}


void wrstart2(int datos[], int tam )
{
  start[0] = root;
  start[1] = freelist;
  if (fseek(fptree, 0L, SEEK_SET))
	  error("fseek in wrstart");
  if (fwrite(start, sizeof(long), 2, fptree) == 0)
	  error("fwrite in wrstart");
  if (root != NIL)
	  writenode(root, &rootnode);

  	for (int i =0; i < tam; i++)
	 {
		insert(datos[i]);
	 }
}


/* Delete item x in B-tree with root t.

	Return value:

	  SUCCESS, NOTFOUND, OR UNDERFLOW
*/
status del(int x, long t)
{
int i, j, *k, *n,*item, *nleft, *nright, *lkey, *rkey, borrowleft=0, nq,
 *addr;
status code;
long *p, left, right, *lptr, *rptr, q, q1;
node nod, nod1, nod2, nodL, nodR;

 if (t == NIL)
	return(NOTFOUND);
 readnode(t, &nod);
 n = & nod.cnt;
 k = nod.key;
 p=nod.ptr;
 i=binsearch(x, k, *n);
 /* *t is a leaf */
 if (p[0] == NIL){
	if (i == *n || x < k[i])
		 return NOTFOUND;
	 /* x is now equal to k[i], located in a leaf:  */
	 for (j=i+1; j < *n; j++){
		 k[j-1] = k[j];
		 p[j] = p[j+1];
	 }
	 --*n;
	writenode(t, &nod);
	 return(*n >= (t==root ? 1 : M) ? SUCCESS : UNDERFLOW);
  }
  /*  t is an interior node (not a leaf): */
  item = k+i;
  left = p[i];
  readnode(left, &nod1);
  nleft = & nod1.cnt;
    /* x found in interior node.  Go to left child *p[i] and then follow a

	  path all the way to a leaf, using rightmost branches:  */
  if (i < *n && x == *item){
	  q = p[i];
	  readnode(q, &nod1);
	  nq = nod1.cnt;
	  while (q1 = nod1.ptr[nq], q1!= NIL){
			 q = q1;
			 readnode(q, &nod1);
			 nq = nod1.cnt;
	  }
	  /*  Exchange k[i] with the rightmost item in that leaf:   */
	  addr = nod1.key + nq -1;
	  *item = *addr;
	  *addr = x;
	  writenode(t, &nod);
	  writenode(q, &nod1);
  }

  /*  Delete x in subtree with root p[i]:  */
	code = del(x, left);
	if (code != UNDERFLOW)
		return code;
	/*  Underflow, borrow, and , if necessary, merge:  */
	if (i < *n)
		readnode(p[i+1], &nodR);
	if (i == *n || nodR.cnt == M){
	  if (i > 0){
		 readnode(p[i-1], &nodL);
		 if (i == *n || nodL.cnt > M)
			borrowleft = 1;
	  }
	}
	/* borrow from left sibling */
	if (borrowleft){
	  item = k+i-1;
		left = p[i-1];
		right = p[i];
		nod1 = nodL;
		readnode(right, &nod2);
		nleft = & nod1.cnt;
	}else{
		right = p[i+1];        /*  borrow from right sibling   */
		readnode(left, &nod1);
		nod2 = nodR;
	}
	nright = & nod2.cnt;
	lkey = nod1.key;
	rkey = nod2.key;
	lptr = nod1.ptr;
	rptr = nod2.ptr;
	if (borrowleft){
		rptr[*nright + 1] = rptr[*nright];
		for (j=*nright; j>0; j--){
			rkey[j] = rkey[j-1];
			rptr[j] = rptr[j-1];
		}
		++*nright;
		rkey[0] = *item;
		rptr[0] = lptr[*nleft];
		*item = lkey[*nleft - 1];
		if (--*nleft >= M){
		  writenode(t, &nod);
		  writenode(left, &nod1);
		  writenode(right, &nod2);
		  return SUCCESS;
		}
	}else
	/* borrow from right sibling */
	 if (*nright > M){
		 lkey[M-1] = *item;
		 lptr[M] = rptr[0];
		 *item = rkey[0];
		 ++*nleft;
		 --*nright;
		 for (j=0; j < *nright; j++){
			 rptr[j] = rptr[j+1];
			 rkey[j] = rkey[j+1];
		 }
		 rptr[*nright] = rptr[*nright + 1];
		 writenode(t, &nod);
		 writenode(left, &nod1);
		 writenode(right, &nod2);
		 return(SUCCESS);
	 }

/////ALGORITMO DE ORDENAMIENTO  (MERGE) //////////////////////////////////////////////////////////////
	 lkey[M-1] = *item;
	 lptr[M] = rptr[0];
	 for (j=0; j<M; j++){
		lkey[M+j] = rkey[j];
		lptr[M+j+1] = rptr[j+1];
	 }
	 *nleft = MM;
	 freenode(right);
	 for (j=i+1; j < *n; j++){
		 k[j-1] = k[j];
		 p[j] = p[j+1];
	 }
	 --*n;
	 writenode(t, &nod);
	 writenode(left, &nod1);
	 return( *n >= (t==root ? 1 : M) ? SUCCESS : UNDERFLOW);

}//DEL


status delnode(int x)
{
long newroot;
	status code = del(x, root);//LLAMA FUNCION DEL
	if (code == UNDERFLOW){
	  newroot = rootnode.ptr[0];
	  freenode(root);
	  if (newroot != NIL)
		 readnode(newroot, &rootnode);
	  root = newroot;
	  code = SUCCESS;
	}
	return(code);  /* Return value:  SUCCESS  or NOTFOUND   */
}

void printtree(long t)
{
static int position=0;
int i, *k, n;
node nod;

  if (t != NIL){
	 position += 6;
	 readnode(t, &nod);
	 k = nod.key;
	 n = nod.cnt;
	 printf("%*s", position, "");
	 for (i=0; i<n; i++)
		printf(" %d", k[i]);
	 puts("");
	 for (i=0; i<=n; i++)
		printtree(nod.ptr[i]);
	 position -= 6;
  }
}

void printOrderedAscending(long t)
{
static int position=0;
int i, *k, n;
node nod;

  if (t != NIL){
	 position += 6;
	 readnode(t, &nod);
	 k = nod.key;
	 n = nod.cnt;
	  for (i=0; i<=n; i++)
	  {
		  printOrderedAscending(nod.ptr[i]);
		  if (i!=n) printf(" %d", k[i]);
	  }
	 position -= 6;
  }
}

void printOrdered(long t)
{
static int position=0;
int i, *k, n;
node nod;

  if (t != NIL){
	 position += 6;
	 readnode(t, &nod);
	 k = nod.key;
	 n = nod.cnt;
	 //printf("%*s", position, "");
	  for (i=n; i>=0; i--)
	  {
		  if (i!=n) printf(" %d", k[i]);
		  printOrdered(nod.ptr[i]);
	  }
	 //puts("");
	 position -= 6;
  }
}
