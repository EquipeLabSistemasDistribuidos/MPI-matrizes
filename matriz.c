//https://sites.google.com/a/liesenberg.biz/cjogos/home/materiais-de-apoio/topicos-relativos-a-c/matrizes/soma-de-matrizes

#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// para obter a hora do computador no srand

const int ordem = 8;	//variavel global

//função que preenche a matriz com valores aleatórios
void preencher_matriz(int m[][ordem])
{
	int i, j;
	srand(time(NULL));		//semente padrão para geração de numeros aleatórios, time(NULL) para receber a hora do computador que sempre será diferente, logo sempre gerará uma semente padrão dirente ao executar o programa
	
	for(i=0; i<ordem; i++)
	{
		for(j=0; j<ordem; j++)
		{
			m[i][j] = rand() % 100;		//numeros no maximo 99, pois utilizará sempre um valor que é resto de uma divisão por 100, que é no max 99
		}
	}	
}

//função que imprime a matriz
void imprimir_matriz(int m[][ordem])
{
	int i, j;

	for(i=0; i<ordem; i++)
	{
		for(j=0; j<ordem; j++)
		{
			printf("%3d ", m[i][j]);
		}
		printf("\n");
	}
}

//função que soma duas matriz
void somar_matrizes(int m1[][ordem], int m2[][ordem], int m_soma[][ordem], int p)
{
	int i, j, p_linha, p_coluna, u_linha, u_coluna;

	//selecionando parte da matriz as matrizes
	switch (p)
	{
	case 1:
		p_linha = 0;
		u_linha = ordem*50/100;
		p_coluna = 0;
		u_coluna = ordem*50/100;
		break;
	
	case 2:
		p_linha = 0;
		u_linha = ordem*50/100;
		p_coluna = (ordem*50/100);
		u_coluna = ordem;
		break;

	case 3:
		p_linha = (ordem*50/100);
		u_linha = ordem;
		p_coluna = 0;
		u_coluna = ordem*50/100;
		break;

	case 4:
		p_linha = (ordem*50/100);
		u_linha = ordem;
		p_coluna = (ordem*50/100);
		u_coluna = ordem;
		break;

	default:
		printf("Error!");
		break;
	}
	for(i=p_linha; i<u_linha; i++)
	{
		for(j=p_coluna; j<u_coluna; j++)
		{
			m_soma[i][j] = m1[i][j] + m2[i][j];
		}
	}
}

void soma_2(int m1[][ordem], int m2[][ordem], int m_soma[][ordem])
{
	
}

void dividir_matriz(int m[][ordem], int p1[][ordem/2], int p2[][ordem/2], int p3[][ordem/2], int p4[][ordem/2])
{
	int i, j;
	printf("25 PORCENTO DA ORDEM %d \n", (ordem*25/100));
	printf("50 PORCENTO DA ORDEM %d \n", (ordem*50/100));
	printf("75 PORCENTO DA ORDEM %d \n", (ordem*75/100));
	printf("100 PORCENTO DA ORDEM %d \n", ordem);
	for(i=0; i<ordem; i++)
	{
		for(j=0; j<ordem; j++)
		{
			
		}
	}
}

int main(int argc, char** argv){
	int a[8][8] = 
	{
		{2, 3, 1, 4, 2, 3, 5, 4}, 
		{3, 1, 2, 5, 2, 3, 4, 4}, 
		{5, 6, 1, 6, 2, 3, 3, 4},
		{4, 1, 3, 7, 2, 3, 4, 4},
		{2, 3, 1, 4, 2, 3, 5, 4}, 
		{3, 1, 2, 5, 2, 3, 7, 4}, 
		{5, 6, 1, 6, 2, 3, 9, 4},
		{4, 1, 3, 7, 2, 3, 1, 4}
	};
	
	int b[8][8] = 
	{
		{4, 1, 1, 5, 2, 3, 1, 4},
		{7, 3, 1, 1, 2, 3, 1, 4},
		{5, 5, 6, 6, 2, 3, 1, 4},
		{3, 9 ,1, 5, 2, 3, 1, 4},
		{4, 1, 1, 5, 2, 3, 1, 4},
		{7, 3, 1, 1, 2, 3, 1, 4},
		{5, 5, 6, 6, 2, 3, 1, 4},
		{3, 9 ,1, 5, 2, 3, 1, 4}
	};
	
	int c[8][8] = 
	{
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};

	int i;

	
	printf("***Matriz A***\n");
	imprimir_matriz(a);
	printf("***Matriz B***\n");
	imprimir_matriz(b);
	for (i = 1; i <= 4; i++)	//apenas alterar para rank
	{
		somar_matrizes(a, b, c, i);
		printf("***Matriz C (SOMA %d)***\n", i);
		imprimir_matriz(c);
	}
	
	printf("***Matriz C (SOMA FINAL)***\n");
	imprimir_matriz(c);
		
	return 0;
}