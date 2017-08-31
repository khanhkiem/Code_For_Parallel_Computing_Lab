import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    plt.figure(figsize=(12, 7))

    # results from serial version of pi calculation
    pi_serial = [0.032057, 0.109386, 1.12105,
                 2.17339, 3.29431, 4.46514, 6.05376]

    # results from openmp on host version of pi calculation: 8 threads
    pi_omp_8threads = []

    # results from openmp on host version of pi calculation: 16 threads
    pi_omp_16threads = []

    # results from openmp on host version of pi calculation: 32 threads
    pi_omp_32threads = []

    # results from openmp on host version of pi calculation: 48 threads
    pi_omp_48threads = []

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

    plt.show()
