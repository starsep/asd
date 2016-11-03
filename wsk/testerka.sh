#!/bin/bash
#Emil Hotkowski
g++ -o make_test make_test.cpp
g++ -o brut brut.cpp
g++ -std=c++11 -o wsk wsk.cpp

while [ true ] ; do
	./make_test >test 
	./brut <test >odp1
	./wsk <test >odp2	
	DIFF=$(diff odp1 odp2) 
	if [ "$DIFF" != "" ] 
	then
	    echo "Outputy sie nie zgadzaja"
	    break
	fi
done
