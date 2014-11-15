BINARY = templateproba
OBJECTS = main.o proba.o
HEADERS = less.h

CC = gcc
CXX = g++
CFLAGS = -std=c11 -O0 -Wall -Wdeprecated -pedantic -g
CXXFLAGS = -O0 -Wall -std=c++11
LDFLAGS = -g

.PHONY: all clean

all: $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)

$(BINARY): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

