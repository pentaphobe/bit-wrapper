for i in `seq 10`; do ./random_buffer && g++ main.cpp -o main && ./main < random.dat && ls -alS *.zip | tail -n 1 | awk '{print $9 " " $5}'; done
