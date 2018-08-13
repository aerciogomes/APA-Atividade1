#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX 6

int Partition(int ar[MAX],int first,int last){
	int pivo = ar[last];
	int i = first- 1;
	int j,aux;

	for(j = first; j <= last-1;j++){
		if(ar[j] <= pivo){
			i = i+1;
			if(ar[i] > ar[j]){
				aux = ar[i];
				ar[i] = ar[j];
				ar[j] = aux;
			}
		}

	}

	i++;
	aux = ar[i];
	ar[i] = ar[j];
	ar[j] = aux;

	return i;

}

void QuickSort(int ar[MAX],int first, int last){
	int aux;
	if(first < last){
		aux = Partition(ar,first,last);
		QuickSort(ar,first,aux-1);
		QuickSort(ar,aux+1,last);
	}
}


int main(){

	int ar[MAX] = {9,11,27,48,0,1};

	QuickSort(ar,0,MAX-1);

	printf("Array ordenado:\n");
	int i;

	for(i=0;i<MAX;i++){
		printf("%d\t",ar[i]);
	}
	puts("");

	return 0;
}