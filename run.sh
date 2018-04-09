#!/usr/bin/env  bash

# for i in `seq 10`;
# do
#   ./gen_rand_buffer &&
#     g++ main.cpp -o main &&
#     ./main < random.dat &&
#     ls -alS *.zip | tail -n 1 | awk '{print $9 " " $5}'
# done

for i in `seq 10`;
do
    g++ main.cpp -o main &&
    ./main < nice_geometric_tat.jpg &&
    ls -alS *.zip | tail -n 1 | awk '{print $9 " " $5}'
done
