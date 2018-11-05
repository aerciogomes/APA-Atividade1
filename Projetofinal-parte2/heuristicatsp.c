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
#define MAX 99

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
struct lista{
    int custo;
    int numV;
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
void LerArquivoMatrizInferior(struct matriz* m, char *arquivo);

void imprimiVertice(struct vertice);

void ConstruirSwap(struct matriz , int* , int* );
void Movimento2(struct matriz, int* , int* );
void ImplementarVND(struct matriz, int *, int*);
void Construir2_opt(struct matriz m,int *solucao_inicial, int* solucao_final);

int SelecionarCaminho(float alfa,int *solucao_aux,int numero);
void ConstruirLCR(struct matriz m, int *solucao_inicial,float alfa);
void OrdenaCaminho(struct lista lista[],int numero, int *solucao_aux);

void CopiarCaminho(struct matriz,int*,int*);
void ImplementarGRASP(struct matriz m, int * solucao_inicial, int maxgrasp, int *solucao_final);

int main(){
    clock_t t;      
    t = clock();

	struct matriz m;

	struct vertice v;
	lerArquivoInstancias(&v, "instancias/rat99.txt"); // no arquivo deve ser retirado o EOF e o nome dos vertices;
	imprimiVertice(v);

	ConstruirMatriz(&m,v);

	//ler_arquivo_matriz(&m, "instancias/swiss42.txt");
    //LerArquivoMatrizInferior(&m, "instancias/gr48.txt");



    imprimir_matriz(m);

    int *solucao_inicial = malloc((m.numero_elementos + 1) * sizeof(int));
    int *melhorv = malloc((m.numero_elementos + 1) * sizeof(int));
    construir_caminho(m, solucao_inicial);
    printf("Solucao inicial: ");
    imprimir_caminho(m.numero_elementos+1, solucao_inicial);

    int custo_solucao_inicial = calcular_custo(m, solucao_inicial);
    printf("Custo solução inicial: %d\n", custo_solucao_inicial);

    //ConstruirSwap(m,solucao_inicial,melhorv);

    //Construir2_opt(m,solucao_inicial,melhorv);
    srand(time(NULL));
    /*ConstruirLCR(m,solucao_inicial,0.5);
    printf("Solucao LCR: ");
    imprimir_caminho(m.numero_elementos+1, solucao_inicial);*/


    //OrdenaSolucao(m,solucao_inicial);

    //ImplementarVND(m,solucao_inicial,melhorv);
    ImplementarGRASP(m,solucao_inicial,5,melhorv);
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("tempo: %f \n", time_taken);
    //free(solucao_inicial);
    //free(melhorv);

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

void LerArquivoMatrizInferior(struct matriz* m, char *arquivo){
    FILE* fp = fopen(arquivo, "r");

    fscanf(fp, "%d\n", &m->numero_elementos);

    m->elementos = malloc(m->numero_elementos * sizeof(int*));

    for(int i = 0; i < m->numero_elementos; i++) {
        m->elementos[i] = malloc(m->numero_elementos * sizeof(int));
        for(int j = 0; j <= i; j++) {
            fscanf(fp, "%d ", &m->elementos[i][j]);
        }
    }

    fclose(fp);

    for(int i = 0;i<m->numero_elementos;i++){
        for(int j = i+1;j<m->numero_elementos;j++){
            m->elementos[i][j] = m->elementos[j][i];
        }
    }

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
        if(i==n-1){
            printf("%d",caminho[0]);
            break;
        }
        printf("%d ", caminho[i]);
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
        for(int j = i + 1; j < m.numero_elementos; j++) {
        	CopiarCaminho(m, solucao_inicial, solucao_tmp);

            tmp = solucao_tmp[i];
            solucao_tmp[i] = solucao_tmp[j];
            solucao_tmp[j] = tmp;
            /*printf("\nTeste: ");
            custo_solucao_tmp = calcular_custo(m, solucao_tmp);
            imprimir_caminho(m.numero_elementos+1,solucao_tmp);
            printf("Custo: %d\n\n",custo_solucao_tmp);*/

            if(custo_solucao_tmp < custo_referencia) {
                custo_referencia = custo_solucao_tmp;
                CopiarCaminho(m, solucao_tmp, melhor_vizinho);
            }
        }
        //puts("");
    }
    printf("\nMelhor: ");
    imprimir_caminho(m.numero_elementos+1,melhor_vizinho);
    custo_solucao_tmp = calcular_custo(m, melhor_vizinho);
    printf("Custo: %d\n\n",custo_solucao_tmp);
    free(solucao_tmp);
}
void Construir2_opt(struct matriz m,int *solucao_inicial, int* solucao_final){
    int* solucao_tmp = malloc((m.numero_elementos)*sizeof(int));
    int custo_referencia = calcular_custo(m, solucao_inicial);
    int custo;
    int i,j,k;
    int inicio,fim;
    int aux;

    CopiarCaminho(m,solucao_inicial,solucao_final);
    //CopiarCaminho(m, solucao_inicial,solucao_tmp);
    //1-2-3-4-5-6

    for(i=0;i<m.numero_elementos-1;i++){
        for(j=i+1;j<m.numero_elementos;j++){//vai até o ultimo elemento - nesse caso estará trocando a mesma ligação?
            inicio = i;
            fim = j;
            CopiarCaminho(m, solucao_inicial,solucao_tmp);
            while(inicio < fim){//da varios swap até não poder mais
                aux = solucao_inicial[inicio];
                solucao_tmp[inicio] = solucao_inicial[fim];
                solucao_tmp[fim] = aux;

                inicio++;
                fim--;
            }

            /*printf("\nTeste: ");
            imprimir_caminho(m.numero_elementos+1,solucao_tmp);
            int custo_solucao_tmp = calcular_custo(m, solucao_tmp);
            printf("Custo: %d\n\n",custo_solucao_tmp);*/

            custo = calcular_custo(m,solucao_tmp);
            if(custo < custo_referencia){
                custo_referencia = custo;
                CopiarCaminho(m,solucao_tmp,solucao_final);
            }          

        }
    }
    printf("\nMelhor: ");
    imprimir_caminho(m.numero_elementos+1,solucao_final);
    int custo_solucao_tmp = calcular_custo(m, solucao_final);
    printf("Custo: %d\n\n",custo_solucao_tmp);
    free(solucao_tmp);
}

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
			printf("\n\n**fazer o 2opt**");
			linha();
			Construir2_opt(m,solucao,melhor_vizinho);

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
void OrdenaCaminho(struct lista lista[],int numero, int solucao_aux[]){
    int i,j;
    int custo;
    int vertice;

    for(i = 0;i<numero;i++){
        for(j = i+1;j<numero;j++){
            //printf("\nVerifica %d com %d",lista[i].numV,lista[j].numV);
            if(lista[j].custo < lista[i].custo){
                custo = lista[i].custo;
                vertice = lista[i].numV;
                lista[i].custo = lista[j].custo;
                lista[i].numV = lista[j].numV;
                lista[j].custo = custo;
                lista[j].numV = vertice;
            }
        }
        //printf("\nLista[%d] = %d",i,lista[i].numV);
    }
    for(i=0;i<numero;i++){
        solucao_aux[i] = lista[i].numV;
    }
    printf("\nCaminho Ordenado: ");
    imprimir_caminho(numero+1,solucao_aux);
}

int SelecionarCaminho(float alfa,int solucao_aux[],int numero){
    int referencia,j;

    if(numero > 1){
        referencia = (int)(alfa*numero);
    }else{
        referencia = 0;
    }

    if(referencia > 1){
        j = rand() % (referencia-1);
    }else{
        j = 0;
    }
    printf("\nValor de j = %d e vetor selecionado = %d\n",j,solucao_aux[j]);

    return solucao_aux[j];
}

void ConstruirLCR(struct matriz m, int *solucao_inicial,float alfa){
    int *solucao_tmp = malloc((m.numero_elementos) * sizeof(int));
    int inseridos[m.numero_elementos];
    struct lista lista[m.numero_elementos]; // lista com todos os caminhos do Vertice N para todos os outros vertices
    int numero = m.numero_elementos;

    for(int i = 0; i < m.numero_elementos; i++) {
        inseridos[i] = FALSE; //Define que nenhum vertice está solução
    }

    solucao_tmp[0] = solucao_inicial[0]; // solucao_tmp será a solucao que recebe os vertices
    inseridos[solucao_tmp[0]] = TRUE; //o primeiro vertice sempre começará a gerar o LCR
    numero--;
    int k;
    int vertice;
    printf("\nSolucao[0] = %d\n",solucao_tmp[0]);
    int solucao_aux[m.numero_elementos];

    //1=1-2-3-4-5
    //2=1-2-3-4-5
    for(int i = 0;i<m.numero_elementos-1;i++){
        k = 0;
        vertice = solucao_tmp[i];
        printf("\nInserindo - pelo vertice [%d]: ",vertice);
        for(int j = 0;j<m.numero_elementos;j++){
            
            if(!inseridos[j]){
                printf("%d - ",j);
                lista[k].numV = j;
                lista[k].custo = m.elementos[vertice][j];
                k++;
            }
        }
        OrdenaCaminho(lista,numero,solucao_aux);// Ordena possíveis caminhos
        solucao_tmp[i+1] = SelecionarCaminho(alfa,solucao_aux,numero);// seleciona o vertice para a solução e retorna ele
        inseridos[solucao_tmp[i+1]] = TRUE;
        printf("\nSolucao[%d] = %d\n",i+1,solucao_tmp[i+1]);
        numero--;

    }

    CopiarCaminho(m,solucao_tmp,solucao_inicial);
    //free(solucao_tmp);
    //free(inseridos);
    //free(solucao_aux);
}

void ImplementarGRASP(struct matriz m, int * solucao_inicial, int maxgrasp, int *solucao_final){
    int *solucao_tmp = malloc((m.numero_elementos) * sizeof(int));
    int valor_referencia = INT_MAX;
    int custo_referencia;

    srand(time(NULL));

    for(int i = 0;i<maxgrasp;i++){
        linha();

        ConstruirLCR(m,solucao_inicial,0.7);

        linha();
        printf("\nSolucao Grasp = ");
        imprimir_caminho(m.numero_elementos+1,solucao_inicial);
        custo_referencia = calcular_custo(m,solucao_inicial);
        printf("\n Custo = %d\n",custo_referencia);

        ImplementarVND(m,solucao_inicial,solucao_tmp);
        custo_referencia = calcular_custo(m,solucao_tmp);

        if(custo_referencia < valor_referencia){
            //puts("oi");
            valor_referencia = custo_referencia;
            CopiarCaminho(m,solucao_tmp,solucao_final);
        }
    }
    printf("\nMelhor Grasp = ");
    imprimir_caminho(m.numero_elementos+1,solucao_final);
    printf("\n Custo = %d\n",valor_referencia);
    //free(solucao_tmp);
}