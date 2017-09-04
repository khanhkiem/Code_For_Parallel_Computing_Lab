#! /bin/bash
for N in 1000000 10000000 100000000 200000000 300000000 400000000 500000000
do 
  for T in 1 8 16 32 48
  do
    printf "\n********************\n\n"
    ./pi_omp_gnu $N $T 
  done
done