#include <malloc.h>
#include <cmath>
#include <omp.h>
#include <cstdio>

void SumColumns(const int m, const int n, long *M, long *s);

int main(){
	const int n = 100000000;	/* the number of columns (inner dimension) */
	const int m = 4;	/* the number of rows (outer dimension) */

	long *matrix = (long *)_mm_malloc(sizeof(long) * m * n, 64);
	long *sums = (long *)_mm_malloc(sizeof(long) * m, 64); /* sum of matrix rows */

	const double HztoPerf = 1e-9 * double(m * n) * sizeof(long);

	const int nTrials = 10;
	double rate = 0;
	double dRate = 0;

	printf("\n\033[1mComputing the sums of elements in each row of a wide, short matrix.\033[0m\n");
	printf("Problem size: %.3f GB, outer dimension: %d, threads: %d (%s)\n\n",
		(double)(sizeof(long)) * (double)(n) * (double)(m) / (double)(1<<30),
		m, omp_get_max_threads(), "CPU");

	/* Initializing data */
	#pragma omp parallel for
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				matrix[i*n + j] = (long)i;

	printf("\033[1m%5s %10s %10s\033[0m\n", "Trials", "Time, s", "Perf(GB/s)");

	const int skipTrials = 2;

	/* Benchmarking SumColumns(...) */
	for(int trial = 1; trial <= nTrials; trial++){
		const double tStart = omp_get_wtime();
		SumColumns(m, n, matrix, sums);
		const double tEnd = omp_get_wtime();

		if(trial > skipTrials){
			rate += HztoPerf / (tEnd - tStart);
			dRate += (HztoPerf * HztoPerf) / ((tEnd - tStart) * (tEnd - tStart));
		}

		printf("%5d %10.3e %10.2f %s\n",
			trial, (tEnd - tStart), HztoPerf/(tEnd - tStart), (trial <= skipTrials ? "*" : ""));
		fflush(stdout);

		/* Verifying that the result is correct */
		for(int i = 0; i < m; i++){
			if(sums[i] != i * n)
				printf("Results are incorrect!\n");
		}
	}

	rate /= (double)(nTrials - skipTrials);
	dRate = sqrt(dRate / (double)(nTrials - skipTrials) - rate * rate);

	printf("-------------------------------------------------\n");
	printf("\033[1m%s %4s \033[42m%10.2f +- %.2f GB/s\033[0m\n",
		"Average performance:", "", rate, dRate);
	printf("-------------------------------------------------\n");
	printf("* - warm-up, not include in average\n");

	/* Free memory */
	_mm_free(sums);
	_mm_free(matrix);

}