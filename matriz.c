//https://sites.google.com/a/liesenberg.biz/cjogos/home/materiais-de-apoio/topicos-relativos-a-c/matrizes/soma-de-matrizes

#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// para obter a hora do computador no srand

int ordem = 3;	//variavel global

//função que preenche a matriz com valores aleatórios
void preencher_matriz(int m[][ordem]){
	int i, j;
	srand(time(NULL));		//semente padrão para geração de numeros aleatórios, time(NULL) para receber a hora do computador que sempre será diferente, logo sempre gerará uma semente padrão dirente ao executar o programa
	
	for(i=0; i<ordem; i++){
		for(j=0; j<ordem; j++){
			m[i][j] = rand() % 100;		//numeros no maximo 99, pois utilizará sempre um valor que é resto de uma divisão por 100, que é no max 99
		}
	}	
}

//função que imprime a matriz
void imprimir_matriz(int m[][ordem]){
	int i, j;

	for(i=0; i<ordem; i++){
		for(j=0; j<ordem; j++){
			printf("%3d ", m[i][j]);
		}
		printf("\n");
	}
}

//função que soma duas matriz
void somar_matrizes(int m1[][ordem], int m2[][ordem], int m_soma[][ordem]){
	int i, j;
	
	for(i=0; i<ordem; i++){
		for(j=0; j<ordem; j++){
			m_soma[i][j] = m1[i][j] + m2[i][j];
		}
	}
}

void soma_2(int m1[][ordem], int m2[][ordem], int m_soma[][ordem]){
	
}

int main(int argc, char** argv){
	int mat1[3][3] = {
		{2, 3, 1}, 
		{3, 1, 2}, 
		{5, 6, 1}
	};
	int mat2[3][3] = {
		{4, 1, 1},
		{7, 3, 1},
		{5, 5, 6}
	};
	int mat_soma[3][3];

	printf("***Matriz A***\n");
	imprimir_matriz(mat1);
	printf("***Matriz B***\n");
	imprimir_matriz(mat2);
	somar_matrizes(mat1, mat2, mat_soma);
	printf("***Matriz SOMA***\n");
	imprimir_matriz(mat_soma);
	return 0;
}