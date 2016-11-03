#!/bin/bash
echo $1 | ./inw_gen > in
./inw < in > out1
./inw_brut < in > out2
cat in
cat out1
cat out2
diff -nsq out1 out2
