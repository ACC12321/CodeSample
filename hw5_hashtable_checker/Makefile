CC = g++
CPPFLAGS = -g -Wall -std=c++17
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all test tests: HashtableTest
	./HashtableTest

HashtableTest: HashtableTest.cpp ../Hashtable.h
	$(CC) $(CPPFLAGS) $< $(GTEST_LL) -o $@

.phony: clean test

clean:
	rm HashtableTest