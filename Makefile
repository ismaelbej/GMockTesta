CXX := g++ -std=c++11
CXXFLAGS := -g
LD := g++ -std=c++11
LDFLAGS := -lpthread -lgmock
GTEST_DIR := /usr/src/gtest
OBJECTS := main.o

.PHONY: run clean

main : $(OBJECTS) libgtest.a
	$(LD) -o $@ $^ $(LDFLAGS)

libgtest.a : gtest-all.o
	ar -rv libgtest.a gtest-all.o

gtest-all.o : ${GTEST_DIR}/src/gtest-all.cc
	g++ -g -o gtest-all.o -I${GTEST_DIR}/include -I${GTEST_DIR} -c ${GTEST_DIR}/src/gtest-all.cc

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run : main
	./main

clean:
	rm $(OBJECTS)

