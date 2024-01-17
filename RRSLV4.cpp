#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void prvi_zad(int num_threads) {
	omp_set_num_threads(num_threads);
	int i, y = 0;
	int x[8000];
	for (i = 0; i < 8000; i++)
		x[i] = i;
	#pragma omp parallel for reduction(+:y)
	
		for (i = 3; i < 8000; i++)
			y = x[i - 3] + y;
	
	printf("%d\n", y);
}

void drugi_zad(int num_threads) {
	printf("Dodijeljeno niti: %d\n", num_threads);
	omp_set_num_threads(num_threads);
	double startTime = omp_get_wtime();
	int i, j = 0;
	int v[2];
	int m[2][2];
	int rj[2];
	int x[8000];
	v[0] = 5;
	v[1] = 2;
	for (i = 0; i < 2; i++) 
		for (j = 0; j < 2; j++)
			m[i][j] = i+j*j+i;

	printf("v = [ ");
	for (i = 0; i < 2; i++) {
		printf("%d ", v[i]);
		rj[i] = 0;
	}
	printf("]\n");

	printf("m = [ \n");
	for (i = 0; i < 2; i++) { printf("[ ");
		for (j = 0; j < 2; j++) printf("%d ", m[i][j]);
		printf("]\n");
	}
	printf("]\n");

#pragma omp parallel for private(j)
	for (i = 0; i < 2; i++) 
		for (j = 0; j < 2; j++) {
			rj[i] += v[j] * m[j][i];
			printf("tred br %d : v[%d] i m[%d][%d]\n", omp_get_thread_num(), j, j, i);
		}

	printf("rj = [ ");
	for (i = 0; i < 2; i++) {
		printf("%d ", rj[i]);
	}
	printf("]\n");

	double endTime = omp_get_wtime();
	printf("time took: %f ms\n", (endTime - startTime)*100);
	
}

int main(int argc, char* argv[]) {
	//prvi_zad(2);
	drugi_zad(2);
	return 0;
}
