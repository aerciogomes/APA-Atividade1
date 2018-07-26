#include <stdio.h>
#define SIZE 4

void insertionSort(int ar[]) //função insertionsort
{
   int i, atual, j;
   for (i = 1; i < SIZE; i++) //percorrer todo o array
   {
       atual = ar[i];
       j = i-1;
       while (j >= 0 && ar[j] > atual) /* Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position */
       {
           ar[j+1] = ar[j];
           j = j-1;
       }
       ar[j+1] = atual;
   }
}

main(){
	int ar[SIZE] = {4, 6, 1, 2}; //array a ser ordenado
	int i = 0;

    printf("Array a ser ordenado: ");
	for (i = 0; i < SIZE; i++) //printar o array antes de ordenar
	{
		printf("%d", *(ar + i));
	}
	puts("\n");

	insertionSort(ar); //ordenando o array

	printf("Array ordenado: ");
	for (i = 0; i < SIZE; i++) //printar o array ordenado
	{
		printf("%d", *(ar + i));
	}
}

