CXX = mpicc
CXXFLAG = -lm  # for debugging
OUTPUT = main
SRC = main
ARG = 100000

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
	mpirun -np 4 ./$(OUTPUT) $(ARG)

build_and_run: build run

run_2_node:
	mpirun -np 8 -npernode 4 -hostfile ~/share/hostfile.txt ./$(OUTPUT) $(ARG)
