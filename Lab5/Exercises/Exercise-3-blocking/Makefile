CXX = mpicc
CXXFLAG = -lm  # for debugging
OUTPUT = main
# ARG = specify when call any rule
SRC = main
NP = 2
NPN = 1

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

build_run: build run

run_2_node:
	mpirun -np $(NP) -npernode $(NPN) -hostfile ~/share/hostfile.txt ./$(OUTPUT) $(ARG)

buid_run_2_node: build run_2_node
