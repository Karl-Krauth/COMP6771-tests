CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror -O3 -flto
LDFLAGS = -ldl -O3 -flto

CXXFILES := $(wildcard *.cpp)
OBJFILES := $(CXXFILES:.cpp=.o)

.PHONY: all clean

all: GraphTester
clean:
	rm -f GraphTester *.o

GraphTester: $(OBJFILES)
	$(CXX) -o $@ $+ $(LDFLAGS)
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
