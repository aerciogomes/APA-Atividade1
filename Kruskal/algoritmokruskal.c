#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50

typedef struct{
	
	int v1;
	int v2;
	int peso;

}aresta; // define as arestas

int A[MAX][MAX]; //matriz com os pesos das arestas, sendo i e j os respectivos vertices
int numV; // Numero de vértices

typedef struct{

	aresta data[MAX];
	int n;

}listaresta;

listaresta lista; // lista de aresta


listaresta listaux; //lista final


void Ordena(){
	int i,j;

	aresta aux;

	for (i = 1; i < lista.n; i++){
		for(j=0;j<lista.n-1;j++){
			if(lista.data[j].peso > lista.data[j+1].peso){
				aux = lista.data[j];
				lista.data[j] = lista.data[j+1];
				lista.data[j+1] = aux;
			}
		}
	}
}

int Busca(int confere[], int vertice){
	return(confere[vertice]);
}
void Union(int confere[],int ver1,int ver2){
	int i;

	for(i=0;i<numV;i++){
		if(confere[i] == ver2){
			confere[i] = ver1;
		}
	}
}
void Kruskal(){
	int confere[MAX],i,j;
	lista.n = 0;

	// colocar as respectivas arestas de A na matriz lista.data[]

	for(i=1;i<numV;i++){
		for(j=0;j<i;j++){
			if (A[i][j] != 0){
				
				lista.data[lista.n].v1 = i;
				lista.data[lista.n].v2 = j;
				lista.data[lista.n].peso = A[i][j];
				lista.n++;

			}
		}
	}

	Ordena(); // ordenar a matriz lista.data[] de acordo com os pesos

	for (i = 0; i < numV; i++)
	{
		confere[i] = i; //armazena os vetores no confere
	}

	listaux.n = 0;

	int vertice1,vertice2;

	for(i=0;i<lista.n;i++){

		vertice1 = Busca(confere,lista.data[i].v1);
		vertice2 = Busca(confere,lista.data[i].v2);

		if(vertice1 != vertice2){
			listaux.data[listaux.n] = lista.data[i];
			listaux.n++;
			Union(confere,vertice1,vertice2);
		}

	}

}

int main(int argc, char const *argv[])
{
	int i,j;
	int total = 0;
	int G[MAX][MAX] = {0};
	int nlinha = 0;
	int tam1,tamanho;
	char ch[999];
	char *key;


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

			key = strtok(ch,"\t");

			while(key != NULL){
				G[i][++k] = atoi(key);
				key = strtok(NULL,"\t");
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

	for(i=0;i<tam1;i++){
		for (j = 0; j < tam1; ++j)
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


	Kruskal();

	for(i=0;i<listaux.n;i++)
    {
        printf("\nVertice1: %d \t Vertice2: %d \t Peso: %d",listaux.data[i].v1,listaux.data[i].v2,listaux.data[i].peso);
        total+=listaux.data[i].peso;

    }

    printf("\n\n\n Custo total eh de: %d\n",total);

	return 0;
}

