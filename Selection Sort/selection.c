#include<stdio.h>
#include<stdlib.h>

#define MAX 10

void SelectionShort(int ar[MAX]){

	int min;
	int i,j,aux;


	for(i=0;i<MAX-1;i++){    //o primeiro  começa sendo o primero 
		min = i;

		for(j=i+1;j<MAX;j++){ // procura o minimo de fato
			if(ar[j] < ar[min]){
				min = j;
			}
		}
		if(i != min){ // encontrou o minimo menor que o atual
			aux = ar[i];
			ar[i] = ar[min];
			ar[min] = aux;
		}
	}

}



int main (){
	
int ar[MAX] = {1, 0, 9, 7, 3, 4, 8, 2, 0, 1};

SelectionShort(ar);

	for (int i = 0; i < MAX; i++){
		printf("%d", ar[i]);
	}

puts("\n");
	
}