#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// para obter a hora do computador no srand
#include <mpi.h>
#include <unistd.h>

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
    usleep(1000000);
}

//função que soma duas matriz
void somar_matrizes(int m1[][ordem], int m2[][ordem], int m_soma[][ordem], int p)
{
	int i, j, p_linha, p_coluna, u_linha, u_coluna;

	//selecionando parte da matriz as matrizes
	switch (p)
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

void rodar_mpi(){

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

    //inicialização do ambiente MPI
    MPI_Init(NULL, NULL);
    

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size != 4)        //necessário ser 4 processos, pois divide a matriz em 4 partes
    {
        fprintf(stderr, "World size must be two for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    printf("RANK %d\n", world_rank);
    

    /*if (world_rank != 0)
    {
        MPI_Recv(&c, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
    }
    
    MPI_Send(&c, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    printf("SEND: RANK %d WORD SIZE %d\n", world_rank, (world_rank + 1) % world_size);
    
    if (world_rank == 0) {
        MPI_Recv(&c, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
    }*/

    if(world_rank == 0)
    {
        printf("Entrou 0\n");
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    } 
    else if(world_rank == 1)
    {
        printf("Entrou 1\n");
        MPI_Recv(&c, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    } 
    else if(world_rank == 2)
    {
        printf("Entrou 2\n");
        MPI_Recv(&c, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    } 
    else if(world_rank == 3)
    {
        printf("Entrou 3\n");
        MPI_Recv(&c, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    }

    /*switch (world_rank)
    {
    case 0:
        printf("Entrou 0");
        MPI_Recv(&c, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        break;

    case 1:
        printf("Entrou 1");
        MPI_Recv(&c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        break;
    
    case 2:
        printf("Entrou 2");
        MPI_Recv(&c, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
        break;
    
    case 3:
        printf("Entrou 3");
        MPI_Recv(&c, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        somar_matrizes(a, b, c, world_rank);
        printf("***Matriz C***\n");
    	imprimir_matriz(c);
        MPI_Send(&c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        break;

    default:
        break;
    }*/

    MPI_Finalize();
	return 0;
}