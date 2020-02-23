
/*
 ============================================================================
 Name        : Trapecio.c
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
#include <math.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int thread_count;
int n;
double a, b, h;
double integral=0;
pthread_mutex_t mutex;

void* Thread_trapecio(void* rank);
double Trap(double left_endpt, double right_endpt, int trap_count,
		double base_len);
double f(double x);

int main(int argc, char *argv[]) {

	long thread;
	pthread_t* thread_handles;
	a = 10;
	b = 40;
	n = 20;
	h = (b-a)/n;
	//Get_args(argc, argv);
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	pthread_mutex_init(&mutex, NULL);
	//integral = 0;
	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Thread_trapecio,
				(void*) thread);

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	printf("El resultado con %f y %f con %d trapecios es %f \n", a, b, n, integral);
	/* This creates a team of threads; each thread has own copy of variables  */

	pthread_mutex_destroy(&mutex);
	free(thread_handles);
	return 0;
}

void* Thread_trapecio(void* rank) {
	long my_rank = (long) rank;
	int local_a, local_b, local_n;
	double local_int;

	local_n = n / thread_count;

	local_a = a + my_rank * local_n * h;
	local_b = local_a + local_n * h;
	local_int = Trap(local_a, local_b, local_n, h);

	pthread_mutex_lock(&mutex);
	integral += local_int;
	pthread_mutex_unlock(&mutex);

	return NULL;
} /* Thread_sum */

double Trap(double left_endpt /* in */, double right_endpt /* in */,
		int trap_count /* in */, double base_len /* in */) {
	double estimate, x;
	int i;

	estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
	for (i = 1; i <= trap_count - 1; i++) {
		x = left_endpt + i * base_len;
		estimate += f(x);
	}
	estimate = estimate * base_len;

	return estimate;
} /*  Trap  */

double f(double x) {
	return x*x;
} /* f */
