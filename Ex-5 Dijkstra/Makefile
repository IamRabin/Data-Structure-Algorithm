CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -o4 -I . -I ../Heap

SRC = Dijkstra.cc
TARGET = Dijkstra.x

all: $(TARGET)

$(TARGET): $(SRC)
	  $(CXX) $(CXXFLAGS) $< -o $@

.PHONY: all clean

clean:
	  rm $(TARGET)

$(SRC): ./graph_routines.h ../Heap/heap.h
