CC = icc
CXX = icpc
CFLAGS = -qopenmp -g
NATIVEFLAG = -mmic
NO_OFFLOAD = -qno-offload
DEBUG = -qopt-report-phase=offload

# set env for OFFLOAD_REPORT
#export OFFLOAD_REPORT = 2

# the build target executables:
# TARGET1 = pi_serial
# TARGET2 = pi_omp
TARGET3 = pi_omp_mic_offload
# TARGET4 = pi_omp_mic_native
# TARGET5 = pi_cilk
# TARGET6 = pi_cilk_mic_offload
# TARGET7 = pi_cilk_mic_native

# $(TARGET1):	$(TARGET1).cpp
# 	$(CXX)	$(NO_OFFLOAD)	$(TARGET1).cpp pi.h	-o	$(TARGET1)

# $(TARGET2):	$(TARGET2).cpp
# 	$(CXX)	$(CFLAGS)	$(DEBUG)	$(TARGET2).cpp pi.h	-o	$(TARGET2)

$(TARGET3):	$(TARGET3).cpp
	$(CXX)	$(CFLAGS)	$(DEBUG)	$(TARGET3).cpp pi.h	-o	$(TARGET3)

# $(TARGET4):	$(TARGET4).cpp
# 	$(CXX)	$(NATIVEFLAG) $(CFLAGS) $(TARGET4).cpp	-o $(TARGET4)

# $(TARGET5): $(TARGET5).cpp
# 	$(CXX)	$(TARGET5).cpp pi_cilk.h	-o $(TARGET5)

# $(TARGET6): $(TARGET6).cpp
# 	$(CXX)	$(TARGET6).cpp pi_cilk_mic.h	-o $(TARGET6)

# $(TARGET7):	$(TARGET7).cpp
# 	$(CXX)	$(NATIVEFLAG)	$(CFLAGS)	$(TARGET7).cpp pi_cilk_mic	-o $(TARGET7)

# clean
clean:
	$(RM) $(TARGET2) $(TARGET3)
	# $(RM) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7)
