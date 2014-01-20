CXX := c++ -std=c++11
LD := c++ -std=c++11
LDFLAGS := -lpthread
GMOCK_DIR := /usr/src/gmock
GTEST_DIR := /usr/src/gmock/gtest
OBJECTS := main.o
CXXFLAGS := -g -I${GMOCK_DIR}/gtest/include

.PHONY: run clean

main : $(OBJECTS) libgmock.a libgtest.a
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run : main
	./main

clean:
	-$(RM) $(OBJECTS)
	-$(RM) gtest-all.o libgtest.a
	-$(RM) gmock-all.o libgmock.a

libgtest.a : gtest-all.o
	$(AR) -rv $@ $^

gtest-all.o : ${GTEST_DIR}/src/gtest-all.cc
	$(CXX) -g -o $@ -I${GTEST_DIR} -I${GTEST_DIR}/include -c $^

libgmock.a : gmock-all.o
	$(AR) -rv $@ $^

gmock-all.o : ${GMOCK_DIR}/src/gmock-all.cc
	$(CXX) -g -o $@ -I${GMOCK_DIR} -I${GTEST_DIR}/include -c $^

