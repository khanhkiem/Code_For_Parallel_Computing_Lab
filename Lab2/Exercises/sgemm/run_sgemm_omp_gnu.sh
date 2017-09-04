#! /bin/bash
# $N to get value of variable N
# 'dirname $0' return the directory path where this bash stored
# Executed program and this bash must be in same directory

program='sgemm_omp_gnu'

mkdir -p `dirname $0`/output

for T in 1 8 16 32 48
do
  for N in 100 1000 2000 4000 6000 8000 10000
  do
    printf "\n********************\n\n"
    `dirname $0`/$program $N $T  | tee `dirname $0`/output/$program-$N-$T
  done
done