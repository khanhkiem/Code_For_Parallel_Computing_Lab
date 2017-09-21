import sys
import numpy as np
import matplotlib.pyplot as plt


def main():
    plt.figure(figsize=(12, 7))

    packet_size = ['128', '256', '512', '1024']

    # results from serial version of pi calculation
    bandwidth_blocking = [67.685074, 91.365950, 82.583303, 93.144882]

    # results from openmp on host version of pi calculation: 8 threads
    bandwidth_non_blocking = [69.816843, 77.085006, 74.817210,
                              92.014332]

    x_pos = np.arange(len(bandwidth_blocking))

    plt.plot(bandwidth_blocking, label='Blocking', color='black', marker='*')

    plt.plot(bandwidth_non_blocking, label='Non-blocking')

    plt.xlabel('Packet size (KB)')
    plt.xticks(x_pos, packet_size)
    plt.ylabel('Bandwidth (MBps)')
    plt.title('Bandwidth between 2 node')
    plt.grid(True)
    plt.legend()

    plt.savefig(sys.path[0] + "/speedup.jpeg")
    plt.show()


if __name__ == "__main__":
    main()
