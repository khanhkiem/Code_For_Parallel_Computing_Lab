CXX = mpicc
CXXFLAG = -lm  # for debugging
OUTPUT = exercise
SRC = exercise
ARG = 
NUM_PROCESS = 4
NUM_PROCESS_PER_NODE = 2

default: build

begin:
	@echo "Building Exercise for Lab 3"

main: $(SRC).o
	$(CXX) $(SRC).o -o $(OUTPUT) $(CXXFLAG) 

$(SRC).o: $(SRC).cpp
	$(CXX) -c $< $(CXXFLAG) 

clean:
	rm -f $(SRC).o $(OUTPUT) core*

end:
	@echo "Done"

build: begin main end

run:
	mpirun -np $(NUM_PROCESS) ./$(OUTPUT) $(ARG)

build_and_run: build run

run_2_node:
	mpirun -np $(NUM_PROCESS) -npernode $(NUM_PROCESS_PER_NODE) -hostfile ~/hostfile.txt ./$(OUTPUT)

