CC=g++
CFLAGS = -g -std=c++17 -Wall -Wextra
all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	$(CC) $(CFLAGS) $< -o $@ -lm
clean:
	rm *.out
