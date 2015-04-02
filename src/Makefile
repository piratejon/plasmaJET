
CXX=clang++
CXXFLAGS=-std=c++11 -Isrc -Wall -g3 -stdlib=libc++
TEST_FLAGS=-I../Catch/include
CXX_SOURCES=src/TttGame.cpp src/AchiGame.cpp src/TttBoard.cpp
LDFLAGS=-lc++ -lc++abi

all: check

test/test_main.o: CXXFLAGS += $(TEST_FLAGS)
test/test.o: CXXFLAGS += $(TEST_FLAGS)

test/test: test/test_main.o test/test.o $(CXX_SOURCES)
	$(CXX) $(CXXFLAGS) $(CXX_SOURCES) $(LDFLAGS) test/test_main.o test/test.o -o test/test
	test/test

check: test/test

clean:
	- rm -rf test/test.o test/test

superclean: clean
	- rm -rf test/test_main.o

