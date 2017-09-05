import sys
import numpy as np
import matplotlib.pyplot as plt


def main():
    plt.figure(figsize=(12, 7))

    # results from serial version of sgemm calculation
    sgemm_serial = [0.011164, 14.5412,  109.243, 1095.86,
                    3881.92, 6914.15, 9181.26]

    # results from openmp on host version of sgemm calculation: 8 threads
    sgemm_omp_8threads = [0.00177, 2.2704, 18.6356, 180.404,
                          242.411, 575.409, 1104.69]

    # results from openmp on host version of sgemm calculation: 16 threads
    sgemm_omp_16threads = [0.001207, 1.50885,  11.2423, 68.6579,
                           120.325, 291.365, 561.505]

    # results from openmp on host version of sgemm calculation: 32 threads
    sgemm_omp_32threads = [0.013416,  0.958614, 7.38648,  59.5107,
                           84.8492, 208.065, 399.984]

    # results from openmp on host version of sgemm calculation: 48 threads
    sgemm_omp_48threads = [0.020395,  0.786059, 5.32728,  60.4137,
                           70.0501, 171.1, 325.873]

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

    plt.savefig(sys.path[0] + "/speedup.jpeg")
    plt.show()


if __name__ == "__main__":
    main()
