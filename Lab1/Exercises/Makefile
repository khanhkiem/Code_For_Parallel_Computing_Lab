CC = g++
CFLAG = -pthread -g	# for debugging
OUTPUT = mul_mat_pthread_output
SRC = mat_mul_pthread
default: clean begin main end

begin:
	@echo "Building Exercise for Lab1&2-Introduction and Multithread"

main: $(SRC).cpp
	$(CC) $(CFLAG) $(SRC).cpp -o $(OUTPUT)

clean:
	rm -f $(SRC).o $(OUTPUT)

end:
	@echo "Done"