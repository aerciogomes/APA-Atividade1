#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX 50

int A[MAX][MAX]; //matriz com os pesos das arestas, sendo i e j os respectivos vertices
int numV; // Numero de vértices

typedef struct
{
	int key;
	int father;
	int v;

}vertice;

typedef struct
{
	
	vertice lista[MAX];
	int numFila;

} prioridade;

prioridade fila; //lista de prioridade

vertice vector[MAX]; //lista de vertices

prioridade solution; // solução final

void Removelista(){
	vertice aux;
	aux = fila.lista[0];
	fila.lista[0] = fila.lista[fila.numFila - 1];
	fila.lista[fila.numFila - 1] = aux;

	fila.numFila = fila.numFila - 1;
}

void AtualizaLista(){
	int i;


	for(i=0;i<fila.numFila;i++){
		fila.lista[i] = vector[fila.lista[i].v];
	}

	for(i=0;i<fila.numFila;i++){
	}
}

int OrdenaLista(){

	Removelista();

	AtualizaLista();

	vertice min1;

	int min2;
	int i,j;

	for(i=0;i<(fila.numFila-1);i++){
		min1 = fila.lista[i];
		min2 = i;
		for(j=i+1;j<fila.numFila;j++){
			if(fila.lista[j].key < fila.lista[min2].key){
				min2 = j;
			}
		}

		if(i != min2){
			fila.lista[i] = fila.lista[min2];
			fila.lista[min2] = min1;
		}

	}

	return fila.lista[0].v;
}

void Prim(){

	int i;
	int cont = 0;

	for(i=0;i<numV;i++){
		vector[i].v = i;
		vector[i].key = 9999;
		vector[i].father = -1;
	}

	for(i = 0;i<numV;i++){
		fila.lista[i] = vector[i];
	}

	fila.numFila = numV;
	solution.numFila = 0;

	vector[0].key = 0;
	fila.lista[0].key = 0;

	while(fila.numFila != 0){
		for(i = 0; i<numV;i++){
			if(A[cont][i] != 0 && A[cont][i] < vector[i].key){
				vector[i].key = A[cont][i];
				vector[i].father = cont;
			}
		}

		solution.lista[solution.numFila] = vector[cont];
		solution.numFila++;
		//vector[cont].pertence = true;
		//fila.lista[0].pertence = true;

		cont = OrdenaLista();
	}
}

int main()
{
	int i,j;

	int G[MAX][MAX] = {0};
	int nlinha = 0;
	int tam1,tamanho;
	char ch[999];
	char *chave;


	FILE *arquivo;

	arquivo = fopen("dij10.txt","r");

	if(arquivo == NULL){
		printf("erro");
		return 1;
	}else{
		fgets(ch,999,arquivo);

		numV = atoi(ch);

		for(i = nlinha;!(feof(arquivo));i++){

			int k = i;
			fgets(ch,999,arquivo);

			chave = strtok(ch,"\t");

			while(chave != NULL){
				G[i][++k] = atoi(chave);
				chave = strtok(NULL,"\t");
			}

		}
	}

	fclose(arquivo);

	printf("\nNumv: %d\n",numV);

	for(i=0;i<numV;i++){
		for(j=0;j<i;j++){
			G[i][j] = G[j][i];
		}
	}

	for(i=0;i<numV;i++){
		for (j = 0; j < numV; ++j)
		{
			printf("%d |\t",G[i][j]);
		}
		puts("");
	}



	for(i=0;i<numV;i++){
		for(j=0;j<numV;j++){
			A[i][j] = G[i][j];
		}
	}
	Prim();
	int custo = 0;

	for(i=1;i<solution.numFila;i++){

		printf("\n Aresta = %d , com vertice1 = %d e vertice2 = %d",A[solution.lista[i].father][solution.lista[i].v],solution.lista[i].father,solution.lista[i].v);

		custo += solution.lista[i].key;
	}	

	printf("\nCusto total = %d\n",custo);

	return 0;
}