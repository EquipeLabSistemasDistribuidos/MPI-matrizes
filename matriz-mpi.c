#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// para obter a hora do computador no srand
#include <mpi.h>		//mpi
#include <unistd.h>		//para pausar a execução do programa por um tempo

const int ordem = 40;	//variavel global

//função que preenche a matriz com valores aleatórios
void preencher_matriz(int m[][ordem])
{
	int i, j;
	srand(time(NULL));					//semente padrão para geração de numeros aleatórios, time(NULL) para receber a hora do computador que sempre será diferente, logo sempre gerará uma semente padrão dirente ao executar o programa
	
	for(i=0; i<ordem; i++)
	{
		for(j=0; j<ordem; j++)
		{
			m[i][j] = rand() % 10;		//numeros no maximo 99, pois utilizará sempre um valor que é resto de uma divisão por 100, que é no max 99
		}
	}	
}

void preencher_matriz_zeros(int m[][ordem])
{
	int i, j;
	
	for(i=0; i<ordem; i++)
	{
		for(j=0; j<ordem; j++)
		{
			m[i][j] = 0;
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
    usleep(1000000);
}

//função que soma duas matriz
void somar_matrizes(int m1[][ordem], int m2[][ordem], int m_soma[][ordem], int proc)
{
	int i, j, p_linha, p_coluna, u_linha, u_coluna;

	//selecionando parte da matriz
	switch (proc)
	{
	case 0:
		p_linha = 0;
		u_linha = ordem*50/100;
		p_coluna = 0;
		u_coluna = ordem*50/100;
		break;
	
	case 1:
		p_linha = 0;
		u_linha = ordem*50/100;
		p_coluna = (ordem*50/100);
		u_coluna = ordem;
		break;

	case 2:
		p_linha = (ordem*50/100);
		u_linha = ordem;
		p_coluna = 0;
		u_coluna = ordem*50/100;
		break;

	case 3:
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

int main(int argc, char** argv){
    
	
    int a[40][40], b[40][40], c[40][40], bytes = 40*40;
	preencher_matriz(a);
	usleep(1000000);	//sleep time para que a matriz a ser preenchida em B, não seja identica a matriz A. As matrizes são geradas aleatoriamente em função do tempo.
	preencher_matriz(b);
	preencher_matriz_zeros(c);
    
    MPI_Init(NULL, NULL);
    
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size != 4)        				//necessário ser 4 processos, pois divide a matriz em 4 partes, se for diferente retorna um erro
    {
        printf("Numero de processos precisa ser igual a 4!\n");
        MPI_Abort(MPI_COMM_WORLD, 1);			//aborta o MPI
    }
    
    if (world_rank != 0)
    {
        MPI_Recv(&c, bytes, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		//se o processo for diferente de 0, recebe a matriz somada do processo anterior
		printf("Processo atual: %d\nRecebido a matriz C do processo %d\n", world_rank, world_rank - 1);
        somar_matrizes(a, b, c, world_rank);													//e soma as matrizes c1,2 (world_rank = 1), c2,1 (world_rank = 2), c2,2 (world_rank = 3)
		printf("*************************************************************** Matriz C ***************************************************************\n");
    	imprimir_matriz(c);
    }
	else																						//se for o processo 0 (world_rank = 0), realiza a soma das matrizes parte c1,1
	{
		somar_matrizes(a, b, c, world_rank);
        printf("*************************************************************** Matriz C ***************************************************************\n");
    	imprimir_matriz(c);
	}
	
    MPI_Send(&c, bytes, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    
    if (world_rank == 0) {
        MPI_Recv(&c, bytes, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Processo atual: %d\nRecebido a matriz C do processo %d\n", world_rank, world_size-1);
		printf("*************************************************************** Matriz A ***************************************************************\n");
		imprimir_matriz(a);
		printf("*************************************************************** Matriz B ***************************************************************\n");
		imprimir_matriz(b);
        printf("*************************************************************** Matriz C FINAL ***************************************************************\n");
    	imprimir_matriz(c);
    }

    MPI_Finalize();
	return 0;
}