#!/bin/sh

touch ex2_1.txt

for i in {1..5}
do
  val=$(tail -c 1 ex2_1.txt)
  sleep 1 # added in order to cause race condition
  echo -n `expr $val + 1` >> ex2_1.txt
done

#critical region is bounded by the for loop
#race condition caused by simultaneous output of several threads, based on the last number from the same file
