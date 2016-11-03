COMPILER=clang-3.7
CFLAGS=-lstdc++ -Wall -Wunused -Wshadow -pedantic -O2 -std=c++11 -g

all: mal

mal: mal.cpp
	$(COMPILER) $(CFLAGS) -o $@ $^

mal_brut: mal_brut.cpp
	$(COMPILER) $(CFLAGS) -o $@ $^

clean:
	rm -rf mal *.o
