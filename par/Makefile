COMPILER = g++
CXXFLAGS = -O2 -std=c++11 -Wall -Wshadow -Wunused -g

all: par par_gen par_checker

par: par.cpp
	${COMPILER} ${CXXFLAGS} -o $@ $^

par_checker: par_checker.cpp
	${COMPILER} ${CXXFLAGS} -o $@ $^

par_gen: par_gen.cpp
	${COMPILER} ${CXXFLAGS} -o $@ $^

clean:
	rm -rf *.o par par_gen par_checker .in .out .test

tests: all
	./par_gen 5000 50000 > .in
	./par < .in > .out
	cat .in .out > .test
	./par_checker < .test
	
