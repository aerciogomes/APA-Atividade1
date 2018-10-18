#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20000 // definir o valo do peso máximo aqui; problema com o linux pela memoria virtual;

typedef struct{
	int itens[MAX][2];
	int tamanho;
}item;

item tudo;

typedef struct{
	int memo[MAX][MAX];
	int pesomax;

}pesos;

pesos totalp;

int Knapsack(){
	int w = 0;
	int i;
	int aux;

	for(w=0;w<=totalp.pesomax;w++){
		for(i=0;i<=tudo.tamanho;i++){
			if(w==0|| i==0){
				totalp.memo[w][i] = 0;
			}else if(w < tudo.itens[i-1][0]){
				totalp.memo[w][i] = totalp.memo[w][i-1];
			}else{
				aux = totalp.memo[w - (tudo.itens[i-1][0])][i-1] + tudo.itens[i-1][1];

				if(aux >= totalp.memo[w][i-1]){
					totalp.memo[w][i] = aux;
				}else{
					totalp.memo[w][i] = totalp.memo[w][i-1];
				}
			}
		}
	}

	return totalp.memo[w-1][i-1];
}


int main(){

	int linhas = 0;
	char lim[999];
	char *key;
	int i,j;

	FILE *arquivo;
    arquivo = fopen("mochila01.txt", "r");

    if (arquivo == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }

    while(1){
        fgets(lim, 999, arquivo);
        if (feof(arquivo)){
            break;
        }
       

        key = strtok(lim, " ");

        i = 0;
        while(key!=NULL){
            if(linhas == 0){
                if(i == 0){
                    tudo.tamanho = atoi(key);
                }else{
                    totalp.pesomax = atoi(key);
                }
            }else if(!i){
            	//printf("\nLinha = %d e peso = %d",linhas,atoi(key));
    			tudo.itens[linhas-1][0] = atoi(key);
            }else{
            	//printf("\nLinha = %d e valor = %d",linhas,atoi(key));
    			tudo.itens[linhas-1][1] = atoi(key);
            }
            key = strtok(NULL, " ");
            i++;
        }
        
        linhas++;
    }

    //printf("\nLinha = %d",linhas);

 
    fclose(arquivo);

    printf("\n Total itens: %d e Peso maximo = %d\n",tudo.tamanho,totalp.pesomax);

    for(i=0;i<tudo.tamanho;i++){
    	printf("\nPeso = %d e Valor = %d",tudo.itens[i][0],tudo.itens[i][1]);
    }
    puts("");

	/*tudo.tamanho = 3; // teste do slide
	tudo.itens[0][0] = 1;
	tudo.itens[0][1] = 10;
	tudo.itens[1][0] = 1;
	tudo.itens[1][1] = 20;
	tudo.itens[2][0] = 2;
	tudo.itens[2][1] = 30;

	totalp.pesomax = 3;*/

	int valortotal = Knapsack();

	for(i=0;i<=totalp.pesomax;i++){
		for(j=0;j<=tudo.tamanho;j++){
			printf("|%d\t",totalp.memo[i][j]);
		}
		printf("|\n");
	}

	printf("\n Peso maximo = %d\n",valortotal);
}