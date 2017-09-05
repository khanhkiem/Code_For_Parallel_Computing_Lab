import sys
import numpy as np
import matplotlib.pyplot as plt


def main():
    plt.figure(figsize=(12, 7))

    # results from serial version of pi calculation
    pi_serial = [0.012824, 0.133761, 1.29437,
                 2.57328, 3.87773, 5.14784, 6.51215]

    # results from openmp on host version of pi calculation: 8 threads
    pi_omp_8threads = [0.002054, 0.027327, 0.21004,
                       0.439824, 0.682988, 0.900439, 1.13843]

    # results from openmp on host version of pi calculation: 16 threads
    pi_omp_16threads = [0.001329, 0.008906, 0.13436,
                        0.276739, 0.452838, 0.539636, 0.747614]

    # results from openmp on host version of pi calculation: 32 threads
    pi_omp_32threads = [0.001314,  0.00492, 0.085078,
                        0.171272,  0.259308, 0.346824,  0.444838]

    # results from openmp on host version of pi calculation: 48 threads
    pi_omp_48threads = [0.019095, 0.023401, 0.109637,
                        0.238241, 0.278681, 0.382913, 0.47578]

    loops = ('1000000', '10000000', '100M', '200M', '300M', '400M', '500M')
    x_pos = np.arange(len(pi_serial))

    plt.plot(pi_serial, label='pi_serial', color='black', marker='*')

    plt.plot(pi_omp_8threads, label='pi_omp_8threads')
    plt.plot(pi_omp_16threads, label='pi_omp_16threads',
             linestyle='--', marker='o')
    plt.plot(pi_omp_32threads, label='pi_omp_32threads',
             linestyle=':', marker='s')
    plt.plot(pi_omp_48threads, label='pi_omp_48threads')

    plt.xlabel('Loop sizes (N)')
    plt.xticks(x_pos, loops)
    plt.ylabel('Execution time (s)')
    plt.title('Pi Calculation in Parallel Computing by Riemann Integral method')
    plt.grid(True)
    plt.legend()

    plt.savefig(sys.path[0] + "/speedup.jpeg")
    plt.show()


if __name__ == "__main__":
    main()
