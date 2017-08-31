import numpy as np
import matplotlib.pyplot as plt


def main():
    plt.figure(figsize=(12, 7))

    # results from serial version of pi calculation
    sgemm_serial = [0.000929, 1.1194, 8.62048, 180.573, ]

    # results from openmp on host version of sgemm calculation: 8 threads
    sgemm_omp_8threads = []

    # results from openmp on host version of sgemm calculation: 16 threads
    sgemm_omp_16threads = []

    # results from openmp on host version of sgemm calculation: 32 threads
    sgemm_omp_32threads = []

    # results from openmp on host version of sgemm calculation: 48 threads
    sgemm_omp_48threads = []

    loops = ('100', '1000', '2000', '4000', '6000', '8000', '10000')
    x_pos = np.arange(len(sgemm_serial))

    plt.plot(sgemm_serial, label='sgemm_serial', color='black', marker='*')

    plt.plot(sgemm_omp_8threads, label='sgemm_omp_8threads')
    plt.plot(sgemm_omp_16threads, label='sgemm_omp_16threads',
             linestyle='--', marker='o')
    plt.plot(sgemm_omp_32threads, label='sgemm_omp_32threads',
             linestyle=':', marker='s')
    plt.plot(sgemm_omp_48threads, label='sgemm_omp_48threads')

    plt.xlabel('Matrix sizes (N)')
    plt.xticks(x_pos, loops)
    plt.ylabel('Execution time (s)')
    plt.title('SGEMM Calculation in Parallel Computing')
    plt.grid(True)
    plt.legend()

    plt.savefig("speedup.jpeg")
    plt.show()


if __name__ == "__main__":
    main()
