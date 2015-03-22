
CXX=clang
CXXFLAGS=-std=c++11 -Isrc -Igtest
CXX_SOURCES=src/TttGame.cpp src/AchiGame.cpp #src/TttBoard.cpp src/AchiGame.cpp
LDFLAGS=-lgtest -lstdc++

all: test

.PHONY: test
test:
	$(CXX) $(CXXFLAGS) $(CXX_SOURCES) $(LDFLAGS) test/test.cpp -o test/test
	test/test

