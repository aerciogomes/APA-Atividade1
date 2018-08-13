#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX 6

void Merge(int ar[MAX],int first, int mid,int last){
	int n1 = mid + 1 - first;
	int n2 = last - mid;

	int left[n1], right[n2];
	int i,j,k;

	for(i=0;i<n1;i++){
		left[i] = ar[i + first];
	}
	for(j=0;j<n2;j++){
		right[j] = ar[mid + j + 1];
	}
	i=0;
	j=0;
	k=first;

	while(i<n1 && j<n2){
		if(left[i] <= right[j]){
			ar[k] = left[i];
			i++;
		}else{
			ar[k] = right[j];
			j++;
		}

		k++;
	}

	while(i < n1){
		ar[k] = left[i];
		i++;
		k++;
	}

	while(j < n2){
		ar[k] = right[j];
		j++;
		k++;
	}

}

void MergeSort(int ar[MAX],int first, int last){

	if(first < last){
		int m = first + ((last - first)/2);

		MergeSort(ar,first,m);
		MergeSort(ar,m+1,last);

		Merge(ar,first,m,last);
	}

}

int main(){

	int ar[MAX] = {7,11,27,0,1,2};

	MergeSort(ar,0,MAX-1);

	printf("Array ordenador: \n");

	int i;

	for(i=0;i<MAX;i++){
		printf("%d\t",ar[i]);
	}
	puts("");

	return 0;
}