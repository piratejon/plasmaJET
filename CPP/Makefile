
CXX=clang
CXXFLAGS=-std=c++11 -Isrc
CXX_SOURCES=src/TttBoard.cpp src/TttGame.cpp
LDFLAGS=-lgtest -lstdc++

all: test

.PHONY: test
test:
	$(CXX) $(CXXFLAGS) $(CXX_SOURCES) $(LDFLAGS) test/test.cpp -o test/test
	test/test

