CC := g++
CXX := g++
CFLAGS := --std=c++11 -I ../include

DPDC := main.cpp LeetCode.cpp

all: target 

.PHONY : all clean

target: $(DPDC)
	$(CC) $(CFLAGS) $(DPDC) -o target

clean:
	rm -rf target
