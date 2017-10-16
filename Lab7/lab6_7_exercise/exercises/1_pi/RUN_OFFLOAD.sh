#LOOP_SIZE=(1000000 10000000 100000000 200000000 300000000 400000000 500000000)
LOOP_SIZE=$1	# Get input size from keyboard
NUM_THREADS=$2	# Get # of OMP threads from keyboard

# Set num of thread for omp
export OMP_NUM_THREADS=$NUM_THREADS
export MIC_ENV_PREFIX=MIC
export MIC_OMP_NUM_THREADS=$NUM_THREADS

for i in "${LOOP_SIZE}"
do
    echo "Run with loop size = $i and $NUM_THREADS threads..."
    time ./pi_omp_mic_offload $i
    echo
done
