compiler = g++
flags = -g -Wall -std=c++11
compile = $(compiler) $(flags)

hash: Hashtable.cpp Hashtable.h
	$(compile) Hashtable.cpp -o hash 

.PHONY: clean
clean:
	rm -rf *.o hash

