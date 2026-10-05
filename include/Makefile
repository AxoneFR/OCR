CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OBJ = main.o solver.o

all: solver

solver: $(OBJ)
	$(CC) $(CFLAGS) -o solver $(OBJ)

%.o: %.c solver.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) solver

.PHONY: all clean
