GTEST_DIR := /usr/src/gtest

main : main.o libgtest.a
	g++ -o main main.o libgtest.a -lpthread -lgmock

main.o : main.cpp
	g++ -c -o main.o main.cpp

libgtest.a : gtest-all.o
	ar -rv libgtest.a gtest-all.o

gtest-all.o : ${GTEST_DIR}/src/gtest-all.cc
	g++ -g -o gtest-all.o -I${GTEST_DIR}/include -I${GTEST_DIR} -c ${GTEST_DIR}/src/gtest-all.cc

