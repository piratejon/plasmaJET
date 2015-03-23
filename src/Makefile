
CXX=clang
CXXFLAGS=-std=c++11 -Isrc -Wall -g3
CXX_SOURCES=src/TttGame.cpp src/AchiGame.cpp src/TttBoard.cpp
LDFLAGS=-lstdc++

all: test

.PHONY: test
test:
	$(CXX) $(CXXFLAGS) $(CXX_SOURCES) $(LDFLAGS) test/test.cpp -o test/test
	test/test

