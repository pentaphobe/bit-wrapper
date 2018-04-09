#!/usr/bin/env  bash

filename="$1"

if [ "$filename" == "demo" ]; then
  filename="nice_geometric_tat.jpg"
fi

if [ ! -f "$filename" ]; then
  echo "$filename not found, going with default random.dat..."

  g++ gen_rand_buffer.cpp -o gen_rand_buffer
  ./gen_rand_buffer
  filename="random.dat"
fi

# for i in `seq 10`;
# do
#   ./gen_rand_buffer &&
#     g++ main.cpp -o main &&
#     ./main < random.dat &&
#     ls -alS *.zip | tail -n 1 | awk '{print $9 " " $5}'
# done

# for i in `seq 10`;
# do

g++ main.cpp -o main

./main < "$filename"

echo "TOP 5:"
ls -alS data/*.zip | tail -n 5 | awk '{print $5 " " $9}'

best=$(ls -alS data/*.zip | tail -n 1 | awk '{print $5 " " $9}')
echo "$best"

bestfile=$(echo "$best" | cut -f 2 -d' ')
echo "bestfile: $bestfile"
cp "$bestfile" "$(dirname $bestfile)/best.$(basename $bestfile)"

zip -9 data/original.zip $filename > /dev/null

original=$(ls -al data/original.zip | awk '{print $5}')

echo "-----"
echo "BEST:"
echo "  $best"
echo "ORIGINAL:"
echo "  $original"

rm data/skip*.bin
rm data/skip*.zip
# rm data/original.zip
