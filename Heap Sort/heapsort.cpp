#include <iostream>
using namespace std;

// criando um maxHeap
void heapify(int arr[], int n, int i)
{
    int maior = i;  // inicializando o maior como raiz
    int l = 2*i + 1;  // esquerdo = 2*i + 1
    int r = 2*i + 2;  // direito = 2*i + 2

    // se o filho da esquerda é maior que a raiz (troca)
    if (l < n && arr[l] > arr[maior])
        maior = l;

    // se o filho da direita é maior que a raiz
    if (r < n && arr[r] > arr[maior])
        maior = r;

    // quando o maior não estiver como a raiz
    if (maior != i)
    {
        swap(arr[i], arr[maior]);

        // recursão na sub-árvore afetada pela troca
        heapify(arr, n, maior);
    }
}

void heapSort(int arr[], int n)
{
    // reorganizando o array na árvore (build maxheap)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // deletando o último nó da árvore depois que houver a troca entre o primeiro e o último
    for (int i=n-1; i>=0; i--)
    {
        // trocando o primeiro com o último
        swap(arr[0], arr[i]);

        // chama heapify na árvore já reduzida
        heapify(arr, i, 0);
    }
}

int main()
{
    int vetor[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(vetor)/sizeof(vetor[0]);

    heapSort(vetor, n);

    cout << "\nArray ordenado: " << endl;
    for(int x = 0; x < n; x++){
        cout << vetor[x] << endl;
    }
   
}
