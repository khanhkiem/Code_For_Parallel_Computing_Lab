import numpy as np
import matplotlib.pyplot as plt

# results from serial version of matrix multiplication with size of matrices: 10, 100, 1000, 10000, 20000, 30000, 40000, 50000, ...
SERIAL_VERSION = [0.002, 0.006, 6.634, 13312.102]

# results from serial version of matrix multiplication with size of matrices: 10, 100, 1000, 10000, 20000, 30000, 40000, 50000, ...
PARALLEL_VERSION = [0.002, 0.002, 0.521, 967.12]

MATRIX_SIZES = ('10 - 2', '100 - 10', '1000 - 50', '10000 - 50')
X_POS = np.arange(len(SERIAL_VERSION))

plt.plot(SERIAL_VERSION, label='Serial Version')
plt.plot(PARALLEL_VERSION, label='Parallel Version')

plt.xlabel('Matrix sizes - Number of parallel threads')
plt.xticks(X_POS, MATRIX_SIZES)
plt.ylabel('Execution time (s)')
plt.title('Matrix Multiplication Serial vs Parallel')
plt.grid(True)
plt.legend()
plt.savefig('performance.png')
plt.show()
