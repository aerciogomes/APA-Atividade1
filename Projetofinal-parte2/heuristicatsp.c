#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define MAX 50

struct matriz {
    int numero_elementos;
    int** elementos;
};

struct nodo {
    int indice;
    int valor;
};

struct vertice{
	int cord1[MAX];
	int cord2[MAX];
	int tamanho;
};

void construir_caminho(struct matriz, int*);
void ConstruirMatriz(struct matriz*,struct vertice);
void imprimir_caminho(int, int*);
int calcular_custo(struct matriz, int*);
int calculaTangente(int x1, int y1,int x2,int y2);
void imprimir_matriz(struct matriz);
void linha();
void lerArquivoInstancias(struct vertice*,char*);
void ler_arquivo_matriz(struct matriz* m, char* arquivo);

void imprimiVertice(struct vertice);

void ConstruirSwap(struct matriz , int* , int* );
void Movimento2(struct matriz, int* , int* );
void Construir2_opt(struct matriz m, int* solucao_inicial, int* melhor_vizinho);
void ImplementarVND(struct matriz, int *, int*);

void CopiarCaminho(struct matriz,int*,int*);
void ImplementarGRASP(struct matriz m, int * solucao_inicial, int maxgrasp, int *solucao_final);
void CronstrucaoLCR(struct matriz m, int * solucao, float alfa);
int RemoveElemento(int numero, int *caminho, int loc);
void OrdenaSolucao(struct matriz m, int* solucao_inicial);

int main(){

	struct matriz m;

	struct vertice v;

	//lerArquivoInstancias(&v, "inst48.txt"); // no arquivo deve ser retirado o EOF e o nome dos vertices;
	//imprimiVertice(v);

	//ConstruirMatriz(&m,v);

	ler_arquivo_matriz(&m, "bays29.txt");



    imprimir_matriz(m);

    int *solucao_inicial = malloc((m.numero_elementos + 1) * sizeof(int));
    construir_caminho(m, solucao_inicial);
    printf("Solucao inicial: ");
    imprimir_caminho(m.numero_elementos+1, solucao_inicial);

    int custo_solucao_inicial = calcular_custo(m, solucao_inicial);
    printf("Custo solução inicial: %d\n", custo_solucao_inicial);

    int *melhorv = malloc((m.numero_elementos + 1) * sizeof(int));

    //ImplementarVND(m,solucao_inicial,melhorv);
    ImplementarGRASP(m,solucao_inicial,3,melhorv);

}
void lerArquivoInstancias(struct vertice* v,char* arquivo){

	int linhas = 0;
	char lim[999];
	char *key;
	int i,j;
	v->tamanho = 0;

	FILE *fp;
    fp = fopen(arquivo, "r");

    if (arquivo == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }

    while(1){
        fgets(lim, 999, fp);
        if (feof(fp)){
            break;
        }
       

        key = strtok(lim, " ");

        i = 0;
        while(key!=NULL){
            if(!i){

    			v->cord1[linhas] = atoi(key);
    			v->tamanho++;
            }else{

    			v->cord2[linhas] = atoi(key);
            }
            key = strtok(NULL, " ");
            i++;
        }
        
        linhas++;
    }

    fclose(fp);

}
void ler_arquivo_matriz(struct matriz* m, char* arquivo){
    FILE* fp = fopen(arquivo, "r");

    fscanf(fp, "%d\n", &m->numero_elementos);

    m->elementos = malloc(m->numero_elementos * sizeof(int*));

    for(int i = 0; i < m->numero_elementos; i++) {
        m->elementos[i] = malloc(m->numero_elementos * sizeof(int));
        for(int j = 0; j < m->numero_elementos; j++) {
            fscanf(fp, "%d ", &m->elementos[i][j]);
        }
    }


    fclose(fp);
}

void construir_caminho(struct matriz m, int* caminho) {
    int *inseridos = malloc(m.numero_elementos * sizeof(int));

    for(int i = 0; i < m.numero_elementos; i++) {
        inseridos[i] = FALSE;
    }
    int k;

    caminho[0] = 0;
    inseridos[0] = TRUE;

    for(int i = 0; i < m.numero_elementos; i++) {
    	k = caminho[i];
        int valor_referencia = INT_MAX;
        int vizinho_selecionado = 0;

        for(int j = 0; j < m.numero_elementos; j++) {
            if(!inseridos[j] && valor_referencia > m.elementos[k][j]) {
                vizinho_selecionado = j;
                valor_referencia = m.elementos[k][j];
            }
        }

        caminho[i+1] = vizinho_selecionado;
        inseridos[vizinho_selecionado] = TRUE;
    }

    caminho[m.numero_elementos] = 0;

    free(inseridos);
}

void ConstruirMatriz(struct matriz* m, struct vertice v){
	int i;
	m->numero_elementos = v.tamanho;
	m->elementos = malloc(m->numero_elementos * sizeof(int*));

	 for(int i = 0; i < m->numero_elementos; i++) {
        m->elementos[i] = malloc(m->numero_elementos * sizeof(int));
        for(int j = 0; j < m->numero_elementos; j++) {
        	if(i == j){
        		m->elementos[i][j] = 0;
        	}else{
        		m->elementos[i][j] = calculaTangente(v.cord1[i],v.cord2[i],v.cord1[j],v.cord2[j]);
        	}
        }
    }
}

void imprimir_caminho(int n, int* caminho) {
    int i;

    for(i = 0; i < n; i++) {
        printf("%d ", caminho[i]+1);
    }

    printf("\n");
}
int calcular_custo(struct matriz m, int* caminho) {
    int custo = 0;

    for(int i = 0; i < m.numero_elementos; i++) {
    	if(i == (m.numero_elementos-1)){
    		custo += m.elementos[caminho[i]][caminho[0]];
    		break;
    	}
        custo = custo + m.elementos[caminho[i]][caminho[i + 1]];
    }

    return custo;
}
int calculaTangente(int x1, int y1,int x2,int y2){
	int tangente;

	int cord1 = abs(x1-x2);
	int cord2 = abs(y1-y2);

	cord1 = pow(cord1, 2);
	cord2 = pow(cord2, 2);

	tangente = (int) sqrt(cord1 + cord2);

	return tangente; 

}

void imprimir_matriz(struct matriz m) {
    linha();
    printf("Matriz\n\n");

    for(int i = 0; i < m.numero_elementos; i++) {
        for(int j = 0; j < m.numero_elementos; j++) {
            printf("%d \t", m.elementos[i][j]);
        }
        linha();

        printf("\n");
    }

    linha();
}
void linha() {
    int i;
    printf("\n");
    for(i = 0; i < 80; i++) printf("_");
    printf("\n");
}
void imprimiVertice(struct vertice v){

	int i;

	for(i=0;i<v.tamanho;i++){
		printf("\nVertice(%d) cord1(%d) cord2(%d) ",i+1,v.cord1[i],v.cord2[i]);
	}

	puts("");

}

void ConstruirSwap(struct matriz m, int* solucao_inicial, int* melhor_vizinho){
    int* solucao_tmp = malloc((m.numero_elementos + 1) * sizeof(int));
    int custo_referencia = calcular_custo(m, solucao_inicial);
    int tmp;
    int custo_solucao_tmp;

    CopiarCaminho(m, solucao_inicial, melhor_vizinho);

    for(int i = 0; i < m.numero_elementos; i++) {
        CopiarCaminho(m, solucao_inicial, solucao_tmp);
        if(i == 0){
        	for(int j=1;j<m.numero_elementos;j++){
        		CopiarCaminho(m, solucao_inicial, solucao_tmp);
        		tmp = solucao_tmp[i];
            	solucao_tmp[i] = solucao_tmp[j];
            	solucao_tmp[j] = tmp;

            	solucao_tmp[m.numero_elementos] = solucao_tmp[i];

            	printf("\nTeste: ");
            	imprimir_caminho(m.numero_elementos+1,solucao_tmp);

            	custo_solucao_tmp = calcular_custo(m, solucao_tmp);
            	printf("Custo: %d\n\n",custo_solucao_tmp);

	            if(custo_solucao_tmp < custo_referencia) {
	                custo_referencia = custo_solucao_tmp;
	                CopiarCaminho(m, solucao_tmp, melhor_vizinho);
           		}
           		//CopiarCaminho(m, solucao_inicial, solucao_tmp);
        	}

        	continue;
        }

        for(int j = i + 1; j < m.numero_elementos; j++) {
        	CopiarCaminho(m, solucao_inicial, solucao_tmp);

            tmp = solucao_tmp[i];
            solucao_tmp[i] = solucao_tmp[j];
            solucao_tmp[j] = tmp;
            printf("\nTeste: ");
            custo_solucao_tmp = calcular_custo(m, solucao_tmp);
            imprimir_caminho(m.numero_elementos+1,solucao_tmp);
            printf("Custo: %d\n\n",custo_solucao_tmp);

            if(custo_solucao_tmp < custo_referencia) {
                custo_referencia = custo_solucao_tmp;
                CopiarCaminho(m, solucao_tmp, melhor_vizinho);
            }
        }
        puts("");
    }
    printf("\nMelhor: ");
    imprimir_caminho(m.numero_elementos+1,melhor_vizinho);
    custo_solucao_tmp = calcular_custo(m, melhor_vizinho);
    printf("Custo: %d\n\n",custo_solucao_tmp);
}

void Movimento2(struct matriz m, int* solucao_inicial, int* melhor_vizinho){
	int* solucao_tmp = malloc((m.numero_elementos + 1) * sizeof(int));
    int custo_referencia = calcular_custo(m, solucao_inicial);
    int tmp;
    int custo_solucao_tmp;

    //caminho - sequencia de vertices
    //matrix - pesos das ligações dos vertices

    CopiarCaminho(m, solucao_inicial, melhor_vizinho);

    for(int i=0;i<m.numero_elementos-2;i++){
    	CopiarCaminho(m, solucao_inicial, solucao_tmp);
    	tmp = solucao_tmp[i+2];
    	solucao_tmp[i+2] = solucao_tmp[i];
    	solucao_tmp[i] = tmp;

    	solucao_tmp[m.numero_elementos] = solucao_tmp[0];

    	custo_solucao_tmp = calcular_custo(m, solucao_tmp);

    	printf("\nTeste: ");
    	imprimir_caminho(m.numero_elementos+1,solucao_tmp);
    	custo_solucao_tmp = calcular_custo(m, solucao_tmp);
        printf("Custo: %d\n\n",custo_solucao_tmp);

    	if(custo_solucao_tmp < custo_referencia){
    		custo_referencia = custo_solucao_tmp;
            CopiarCaminho(m, solucao_tmp, melhor_vizinho);
    	}

    }
    printf("\nMelhor: ");
    imprimir_caminho(m.numero_elementos+1,melhor_vizinho);
    custo_solucao_tmp = calcular_custo(m, melhor_vizinho);
    printf("Custo: %d\n\n",custo_solucao_tmp);

}
/*void Construir2_opt(struct matriz m, int* solucao_inicial, int* melhor_vizinho){
	int* solucao_tmp = malloc((m.numero_elementos + 1) * sizeof(int));
    int* solucao_aux = malloc((m.numero_elementos + 1) * sizeof(int));
    int custo_referencia = calcular_custo(m, solucao_inicial);
    int tmp;
    int custo_solucao_tmp;

    //caminho - sequencia de vertices
    //matrix - pesos das ligações dos vertices
    CopiarCaminho(m, solucao_inicial, melhor_vizinho);
    
    for(int i =0;i<m.numero_elementos-2;i++){
    	CopiarCaminho(m, solucao_inicial, solucao_tmp);
    	for(int j = i+2;j<m.numero_elementos;j++){
    		CopiarCaminho(m, solucao_inicial, solucao_tmp);
            CopiarCaminho(m, solucao_tmp, solucao_aux);
            for(int k = j, int f = i;k>i;k--,f++){

                tmp = solucao_aux[k];
                solucao_aux[k] = solucao_aux[f];
                solucao_aux[f] = tmp;

            }   		

    	}
    }

    printf("\nMelhor: ");
    imprimir_caminho(m.numero_elementos+1,melhor_vizinho);
    custo_solucao_tmp = calcular_custo(m, melhor_vizinho);
    printf("Custo: %d\n\n",custo_solucao_tmp);

}*/

void ImplementarVND(struct matriz m, int *solucao, int*melhor_vizinho){
	int r = 2; // sendo as estruturas - movimento2 e swap
	int i = 1;
	int custo_referencia = calcular_custo(m, solucao);
	int custo_solucao_tmp;

	while(i<=r){
		if(i == 1){
			printf("\n\n**fazer o swap**");
			linha();
			ConstruirSwap(m,solucao,melhor_vizinho);

			custo_referencia = calcular_custo(m,solucao);
			custo_solucao_tmp = calcular_custo(m,melhor_vizinho);
		}else if(i == 2){
			printf("\n\n**fazer o movimento2**");
			linha();
			Movimento2(m,solucao,melhor_vizinho);

			custo_referencia = calcular_custo(m,solucao);
			custo_solucao_tmp = calcular_custo(m,melhor_vizinho);
		}
		if(custo_solucao_tmp < custo_referencia){
			CopiarCaminho(m, melhor_vizinho, solucao);
			i = 1; //condição para continuar no movimento até encontrar um mínimo local
		}else{
			i = i+1; //condição para pular o movimento após encontrar um mínimo local
		}
	}
}



void CopiarCaminho(struct matriz m,int*orig,int*dest){

	int i;

	for(i=0;i<=m.numero_elementos;i++){
		dest[i] = orig[i];
	}

}
int RemoveElemento(int numero, int *caminho, int loc){
    int i;
    int valor = caminho[loc];

    if(loc == numero-1){
        return valor;
    }

    for(i = loc;i<numero-1;i++){
        caminho[i] = caminho[i+1];
    }

    return valor;
}
/*void OrdenaSolucao(struct matriz m, int* solucao_inicial){
    int i,j;
    int menor;
    // 1 - 2 - 3 - 4
    int* solucao_tmp = malloc((m.numero_elementos + 1) * sizeof(int));
    CopiarCaminho(m,solucao_inicial, solucao_tmp);

    menor = m[solucao_inicial[0]][solucao_inicial[1]];
    int aux;
    int deslocamento = 0;

    for(i = 1;i<m.numero_elementos;i++){
        aux = ,
    }
}*/
void CronstrucaoLCR(struct matriz m, int * solucao, float alfa){
    int* solucao_tmp = malloc((m.numero_elementos + 1) * sizeof(int));
    int* solucao_final = malloc((m.numero_elementos + 1) * sizeof(int));
    int numero = m.numero_elementos;
    int vertice;
    int i;
    int aux;
    int j;
    CopiarCaminho(m,solucao, solucao_tmp);
    srand(time(NULL));
    for(i=0;i<m.numero_elementos;i++){
        if(numero > 1){
            aux = (int)(alfa*numero);
        }else{
            aux = 0;
        }
        printf("\naux = %d\n",aux);
        if(aux > 1){
            j = rand() % (aux-1);
        }else{
            j = 0;
        }
        printf("\n j = %d",j);

        printf("\nnumero = %d",numero);

        vertice = RemoveElemento(numero,solucao_tmp,j);
        if(numero > 0){
            numero--;
        }

        solucao_final[i] = vertice;
    }

    CopiarCaminho(m,solucao_final,solucao);
}

void ImplementarGRASP(struct matriz m, int * solucao_inicial, int maxgrasp, int *solucao_final){
    int valor_referencia = INT_MAX;
    int custo_referencia;

    for(int i = 0;i<maxgrasp;i++){
        CronstrucaoLCR(m,solucao_inicial,0.5);
        printf("\nSolucao Grasp = ");
        imprimir_caminho(m.numero_elementos+1,solucao_inicial);
        custo_referencia = calcular_custo(m,solucao_inicial);
        printf("\n Custo = %d\n",custo_referencia);
        ImplementarVND(m,solucao_inicial,solucao_final);
        custo_referencia = calcular_custo(m,solucao_final);

        if(custo_referencia < valor_referencia){
            valor_referencia = custo_referencia;
            solucao_final = solucao_final;
        }
    }
}