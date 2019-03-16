#!/bin/bash
#./server &

#generate clients with random parameters
for i in {1..200}
do
    ./client "name$(( $RANDOM % 10 ))" "measurement$(( $RANDOM % 100 ))"
done