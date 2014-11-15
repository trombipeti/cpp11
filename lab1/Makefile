BINARY=strtest
OBJECTS=main.o strswap.o
HEADERS=strswap.h
CC=clang

.PHONY: all clean

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) -std=c99 -Wall -Wdeprecated -pedantic -c $< -o $@ -O3

clean:
	rm -f $(OBJECTS) $(BINARY)
