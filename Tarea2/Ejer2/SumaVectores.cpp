#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define Master 0
#define Recv 1
#define Suma 2

void LlenarVector(int VECTOR[], int MAX);
void ImprimirVector(int VECTOR[], int MAX);

int main(int argc, char *argv[])
{
	int my_rank, size;
	int MAX = atoi(argv[1]);
	int VECTOR_A[MAX], VECTOR_B[MAX];

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_my_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == Master)
	{
		LlenarVector(VECTOR_A, MAX);
		LlenarVector(VECTOR_B, MAX);

		MPI_Send(VECTOR_A, MAX, MPI_INT, Recv, 2, MPI_COMM_WORLD);
		MPI_Send(VECTOR_B, MAX, MPI_INT, Recv, 3, MPI_COMM_WORLD);
	}
	else
	{
		if (my_rank == Recv)
		{
			MPI_Recv(VECTOR_A, MAX, MPI_INT, Master, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(VECTOR_B, MAX, MPI_INT, Master, 3, MPI_COMM_WORLD, &status);

			printf("Vector A :\n");ImprimirVector(VECTOR_A, MAX);
			printf("Vector B:\n");ImprimirVector(VECTOR_B, MAX);

			MPI_Send(VECTOR_A, MAX, MPI_INT, Suma, 2, MPI_COMM_WORLD);
			MPI_Send(VECTOR_B, MAX, MPI_INT, Suma, 3, MPI_COMM_WORLD);
		}
		else
		{
			if (my_rank == Suma)
			{
				MPI_Recv(VECTOR_A, MAX, MPI_INT, Recv, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(VECTOR_B, MAX, MPI_INT, Recv, 3, MPI_COMM_WORLD, &status);

				int VECTOR_RES[MAX];

				for(int i = 0; i < MAX; i++)
				{
					VECTOR_RES[i] = (VECTOR_A[i] + VECTOR_B[i]);
				}
				printf("Vector Sumaa : \n");
				ImprimirVector(VECTOR_RES, MAX);
			}
		}
	}

	MPI_Finalize();
	return EXIT_SUCCESS;
}

void LlenarVector(int VECTOR[], int MAX)
{
	for(int i = 0; i < MAX; i++)
	{
		VECTOR[i] = (rand()%120) + 1;
	}
}

void ImprimirVector(int VECTOR[], int MAX)
{
	for(int i = 0; i < MAX; i++)
	{
		printf("%d\n", VECTOR[i]);
	}
}
