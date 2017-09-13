CXX = mpicc
CXXFLAG = -lm  # for debugging
OUTPUT = example
SRC = example
ARG = 

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
	mpirun -np 8 -npernode 4 -hostfile ./hostfile.txt ./example

