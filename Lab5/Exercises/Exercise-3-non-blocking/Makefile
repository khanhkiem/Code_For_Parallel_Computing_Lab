CXX = mpicc
CXXFLAG = -lm  # for debugging
OUTPUT = main
SRC = main
ARG = 128
NP = 2

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
	mpirun -np $(NP) ./$(OUTPUT) $(ARG)

build_and_run: build run

run_2_node:
	mpirun -np $(NP) -npernode 2 -hostfile ~/share/hostfile.txt ./$(OUTPUT) $(ARG)
