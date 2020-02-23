/*
 ============================================================================
 Name        : factorial.c
 Author      : Myrella Alejandra
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int thread_count;
int n;
long fact;

void* Thread_factorial(void* rank);
//void Get_args(int argc, char* argv[]);

int main(int argc, char *argv[]) {

	long thread;
	pthread_t* thread_handles;
	n = 10;
	//Get_args(argc, argv);
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	//printf("Escriba el numero del factorial: ");
	fact = 1;
	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Thread_factorial,
				(void*) thread);

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	printf("El factorial de %d es %d\n", n, fact);
	/* This creates a team of threads; each thread has own copy of variables  */
	free(thread_handles);
	return 0;
}

void* Thread_factorial(void* rank) {
	long my_rank = (long) rank;
	long my_fact=1;
	long long i;
	long long my_n = n / thread_count;
	long long my_first_i = my_n * my_rank + 1;
	long long my_last_i = my_first_i + (my_n - 1);

	for (i = my_first_i; i <= my_last_i; i++) {
		my_fact = my_fact * i;
	}
	fact = fact* my_fact;

	return NULL;
} /* Thread_sum */
