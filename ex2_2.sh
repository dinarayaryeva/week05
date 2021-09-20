#!/bin/sh

touch ex2_2.txt

for i in {1..5}
do
  while [ -f "file" ] #if link exists => file is locked
  do 
    sleep 1
  done
  ln ex2_2.txt file #add link to the file
  val=$(tail -c 1 file)
  sleep 1 # added in order to cause race condition
  #but in this case even this delay cannot cause race condition
  echo -n `expr $val + 1` >> ex2_2.txt
  rm file #remove the link
done