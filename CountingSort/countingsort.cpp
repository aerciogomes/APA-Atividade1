#include <iostream>

using namespace std;

void countingSort(int arr[],int n,int max){
    int count[max]={0};
    int i;
    int saida[n];


    for(i=0; i<n; i++)
    	++count[arr[i]];

    for(i=1; i<max; i++)
    	count[i]+=count[i-1];

    for(i=n-1; i>=0; i--){
        saida[count[arr[i]]-1]=arr[i]; //varrendo o array desordenado da direita pra esquerda e conferindo o índice de cada elemento no array count
        --count[arr[i]];
    }

    for(i=0; i<n; i++)
    	arr[i]=saida[i];
}

int main() {

	int vetor[] = {1, 4, 1, 2, 7, 12, 2};

	int tam = sizeof(vetor)/sizeof(vetor[0]);

    int i;
    int maior = vetor[0];
    for(i=1;i<tam;i++){
        if(vetor[i] > maior){
            maior = vetor[i];
        }
    }
	countingSort(vetor, tam, maior + 1);

	cout << "\nArray ordenado: " << endl;
    for(int x = 0; x < 7; x++){
        cout << vetor[x] << endl;
    }
	return 0;
}
