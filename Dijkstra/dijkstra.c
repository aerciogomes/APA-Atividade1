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

void Dijkstra(){

	int i;
	int cont = 0;

	for(i=0;i<numV;i++){
		vector[i].v = i;
		vector[i].key = 99999999;
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
			if(A[cont][i] != 0 && ((A[cont][i] + vector[cont].key) < vector[i].key)){
				vector[i].key = A[cont][i] + vector[cont].key;
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

	arquivo = fopen("dij40.txt","r");

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

	/*numV = 9;    //TESTE COM O GRAFO DO SLIDE

	puts("Digite a matriz");

	int AD[9][9] = { {0,4,0,0,0,0,0,8,0},
					  {4,0,8,0,0,0,0,2,0},
					  {0,8,0,7,0,4,0,0,2},
					  {0,0,7,0,9,14,0,0,0},
					  {0,0,0,9,0,10,0,0,0},
					  {0,0,4,14,10,0,3,0,0},
					  {0,0,0,0,0,3,0,1,6},
					  {8,2,0,0,0,0,1,0,7},
					  {0,0,2,0,0,0,6,7,0} };

	for(i=0;i<numV;i++){
		for(j=0;j<numV;j++){
			A[i][j] = AD[i][j];
		}
	}*/

	for(i=0;i<numV;i++){
		printf("\n{ ");
		for(j=0;j<numV;j++){
			printf("%d \t",A[i][j]);
		}
		printf("}");

	}



	Dijkstra();
	
	printf("\n\n ***** Vertice e seus respectivos custos:");

	for(i=0;i<solution.numFila;i++){
		printf("\nVertice [%d] | Custo = %d",solution.lista[i].v,solution.lista[i].key);
	}

	puts("");
	return 0;
}