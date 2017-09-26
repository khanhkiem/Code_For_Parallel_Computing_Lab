# MODIFY THESE PARAMETERS TO OPTIMIZE THE CALCULATION:
KMP_AFFINITY=scatter
OMP_NUM_THREADS=1
# END OF PARAMETERS TO MODIFY

CXX = icpc
CXXFLAGS=-qopenmp -mkl
CPUFLAGS = $(CXXFLAGS) -xhost
OPTFLAGS = -qopt-report -qopt-report-file=$@.optrpt

CPUOBJECTS = dgemm.o

TARGET=app-CPU
CXX=icpc

.SUFFIXES: .o .cc

all: $(TARGET) instructions

%-CPU: $(CPUOBJECTS)
	$(info )
	$(info Linking the CPU executable:)
	$(CXX) $(CPUFLAGS) -o $@ $(CPUOBJECTS)

.cc.o:
	$(info )
	$(info Compiling a CPU object file:)
	$(CXX) -c $(CPUFLAGS) $(OPTFLAGS) -o "$@" "$<"

instructions: run-cpu
	$(info )

run-cpu: app-CPU
	$(info )
	$(info TO EXECUTE THIS APPLICATION ON CPU, USE THE FOLLOWING COMMAND: )
	$(info OMP_NUM_THREADS=... KMP_AFFINITY=... ./app-CPU)
	$(info )

clean: 
	rm -f $(CPUOBJECTS) $(TARGET) *.optrpt
