#! /bin/bash
# $N to get value of variable N
# 'dirname $0' return the directory path where this bash stored
# Executed program and this bash must be in same directory

program='pi_omp_gnu'
output_dir='output_'$program

mkdir -p `dirname $0`/$output_dir

for T in 1 8 16 32 48
do 
  for N in 1000000 10000000 100000000 200000000 300000000 400000000 500000000
  do
    process_output_dir=`dirname $0`/$output_dir/$program-$N-$T
    if [ -e process_output_dir ]
    then
      continue
    else
      printf "\n********************\n\n"
      printf "$program $N $T\n\n"
      `dirname $0`/$program $N $T  | tee process_output_dir
    fi
  done
done