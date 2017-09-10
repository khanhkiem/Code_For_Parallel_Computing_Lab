CXX = mpicc
CXXFLAG = -lm  # for debugging
OUTPUT = exercise_3
SRC = exercise_3
default: build

begin:
	@echo "Building Exercise for Lab 3"

main: $(SRC).o
	$(CXX) $(SRC).o -o $(OUTPUT) $(CXXFLAG) 

$(SRC).o: $(SRC).cpp
	$(CXX) -c $< $(CXXFLAG) 

clean:
	rm -f $(SRC).o $(OUTPUT)

end:
	@echo "Done"

build: begin main end

run:
	mpirun -np 4 ./exercise_3 100000000

build_and_run: build run