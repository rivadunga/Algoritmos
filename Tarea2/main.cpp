#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<time.h>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

#define NUMELTS 200
void writeRandom(string,int);
void readRandom(string,int[],int);
void printData(int[],int);
void siftDown( int*, int, int);
void bubble(int[],int);
void coctail(int[],int);
void insertion(int[],int);
void bucket(int[],int);
void counting(int[],int);
void selection(int[],int);
void heapsort(int[],int);
void quick(int[],int,int);
void binaryTree(int[],int);
void radixsort(int[],int);
void shellsort(int[],int);
void merge_sort(int[],int,int);


void readRandom(string fileName,int data[],int N){
    ifstream read(fileName);
    int n,i;
    for(int i = 0; i < N; i++)
        read >> data[i];
}

int main(){
    int num = 10;
    for (int i = 1; i <= 6; i++)
    {
        if (i == 6) num = 500000;
        int data[num];
        stringstream ss;
        ss << num;
        string name = ss.str() + "random.txt";
        readRandom(name,data,num);
        float start = clock();
        coctail(data,num); //ALGORITMO
        cout << "TIEMPO TOTAL (" << ss.str() << "): " <<(clock() - start)/CLOCKS_PER_SEC << "s" << endl;
        num *= 10;
    }
}
void writeRandom(string fileName, int N){
    ofstream file;
    file.open (fileName);
    for (int i = 0; i < N; i++)
        file << rand()%1000 << " ";
        file.close();
}
void printData(int data[], int N){
     for (int i = 0; i < N; i++)
        cout << data[i] << " ";
}
void bubble(int data[], int N){
    for (int j = 0; j < N; j++)
        for (int i = j; i < N; i++)
            if (data[i] < data[j])
            {
                int aux = data[i];
                data[i] = data[j];
                data[j] = aux;
            }
}
void coctail(int data[],int N){
    bool notSorted = true;
	while(notSorted)
	{
	    notSorted = false;
	    for(int i = 0; i < N; i++)
            if( data[i] > data[i+1] )
            {
                int aux = data[i];
                data[i] = data[i+1];
                data[i+1] = aux;
                notSorted = true;
            }
	    if( !notSorted ) break;
	    notSorted = false;
	    for(int i = N - 1; i > 0; i--)
            if(data[i-1] > data[i] )
            {
                int aux = data[i];
                data[i] = data[i-1];
                data[i-1] = aux;
                notSorted = true;
            }
	}
}
void insertion(int data[],int N){
    //Recorre todos y va insertando cada nodo en su lugar
    // 4 2 1 6 3
    // primera 4 2 1 6 3, no se mueve
    // segunda 2 4 1 6 3  mueve el segundo al final
    // tercera  1 2 4 6 3  mueve el 1 al final sin mover los que van antes
    int key,i,j;
    for (int i = 0; i < N; i++)
    {
        j = i;
        while (j > 0 && data[j-1] > data[j])
        {
            int aux = data[j];
            data[j] = data[j-1];
            data[j-1] = aux;
            j = j-1;
        }
    }
}
void bucket(int arr[],int n){
    int m = 1001;

    int buckets[m];

    for (int i = 0; i < m; ++i)
        buckets[i] = 0;

    for (int i = 0; i < n; ++i)
        ++buckets[arr[i]];

    for (int i = 0, j = 0; j < m; ++j)
        for (int k = buckets[j]; k > 0; --k)
            arr[i++] = j;
}
void counting(int data[],int N){
  int min = *min_element(data, data+N);
  int max = *max_element(data, data+N);

  int repeticiones[max - min +1];
  for(int i = 0; i < (max-min +1); ++i){
    repeticiones[i]=0;
  }

  for (int i = 0; i < N; ++i){
    repeticiones[data[i]-min] += 1;
  }

  int puntero = 0;
  for(int j = 0; j < (max-min+1); ++j){
    for (int x = 0; x < repeticiones[j]; ++x){
      data[puntero] = j + min;
      puntero++;
    }
  }
}
void swap(int *m, int *n){
	int tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}
void heapsort( int a[], int N){
	/* heapify */
	for (int k = N/2; k >= 0; k--) {
		siftDown( a, k, N);
	}

	while (N-1 > 0) {
		/* swap the root(maximum value) of the heap
		with the last element of the heap */
		swap(a[N-1], a[0]);
		/* put the heap back in max-heap order */
		siftDown(a, 0, N-1);
		/* N-- : decrease the size of the heap by one
		so that the previous max value will
        	stay in its proper placement */
		N--;
	}
}
void siftDown( int *a, int k, int N){
	while ( k*2 + 1 < N ) {
		/* For zero-based arrays, the children are 2*i+1 and 2*i+2 */
 		int child = 2*k + 1;

		/* get bigger child if there are two children */
		if ((child + 1 < N) && (a[child] < a[child+1])) child++;

		if (a[k] < a[child]) {   /* out of max-heap order */
			swap( a[child], a[k] );
			/* repeat to continue sifting down the child now */
			k = child;
		}
		else
			return;
	}
}
void selection(int data[], int N){
    int pos_min,temp;
	for (int i=0; i < N-1; i++)
	{
	    pos_min = i;//set pos_min to the current index of array
		for (int j=i+1; j < N; j++)
		{
		if (data[j] < data[pos_min])
                   pos_min=j;
	//pos_min will keep track of the index that min is in, this is needed when a swap happens
		}
	//if pos_min no longer equals i than a smaller value must have been found, so a swap must occur
            if (pos_min != i)
            {
                 temp = data[i];
                 data[i] = data[pos_min];
                 data[pos_min] = temp;
            }
	}
}
int divideQuick(int data[], int start, int end) {
    int left;
    int right;
    int pivot;
    int temp;
    pivot = data[start];
    left = start;
    right = end;
    while (left < right) {
        while (data[right] > pivot) {
            right--;
        }
        while ((left < right) && (data[left] <= pivot)) {
            left++;
        }
        if (left < right) {
            temp = data[left];
            data[left] = data[right];
            data[right] = temp;
        }
    }
    // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
    temp = data[right];
    data[right] = data[start];
    data[start] = temp;
    // La nueva posición del pivot
    return right;
}
void quick(int data[], int start, int end){
    int pivot;
    if (start < end) {
        pivot = divideQuick(data, start, end);
        quick(data, start, pivot - 1);
        quick(data, pivot + 1, end);
    }
}
struct nodo{
     int nro;
     struct nodo *izq, *der;
};
typedef struct nodo *ABB;
/* es un puntero de tipo nodo que hemos llamado ABB, que ulitizaremos
   para mayor facilidad de creacion de variables */
ABB crearNodo(int x){
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
void insertar(ABB &arbol, int x){
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
     }
     else if(x <= arbol->nro)
          insertar(arbol->izq, x);
     else if(x > arbol->nro)
          insertar(arbol->der, x);
}
void enOrden(ABB arbol){
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          //cout << arbol->nro << " ";
          enOrden(arbol->der);
     }
}
void binaryTree(int data[], int N){
    ABB arbol = NULL;
    for(int i=0; i<N; i++)
    {
        insertar( arbol, data[i]);
    }
    enOrden(arbol);
}

void countSort(int arr[], int n, int exp){
    int output[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
/*
 * sorts arr[] of size n using Radix Sort
 */
void radixsort(int arr[], int n){
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void shellsort(int v[], int n){

    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}

void merge(int a[], const int low, const int mid, const int high){
	int *temp = new int[high-low+1];

	int left = low;
	int right = mid+1;
	int current = 0;

	while(left <= mid && right <= high) {
		if(a[left] <= a[right]) {
			temp[current] = a[left];
			left++;
		}else {
			temp[current] = a[right];
			right++;
		}
		current++;
	}
	if(left > mid) {
		for(int i=right; i <= high;i++) {
			temp[current] = a[i];
			current++;
		}
	}else{
		for(int i=left; i <= mid; i++) {
			temp[current] = a[i];
			current++;
		}
	}

	for(int i=0; i<=high-low;i++) {
                a[i+low] = temp[i];
	}
	delete[] temp;
}

void merge_sort(int a[], const int low, const int high)
{
	if(low >= high) return;
	int mid = (low+high)/2;
	merge_sort(a, low, mid);
	merge_sort(a, mid+1, high);
	merge(a, low, mid, high);
}
