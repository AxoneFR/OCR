CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude -Iinclude/solver -Iinclude/image_proc -Iinclude/neural_network -Iinclude/segmentation
LDFLAGS = -lm

SRC_DIR = src

TARGETS = solver test_binarization nn

SRC_SOLVER = $(SRC_DIR)/main.c $(SRC_DIR)/grid.c $(SRC_DIR)/solver.c
SRC_BINA   = $(SRC_DIR)/test_binarization.c $(SRC_DIR)/binarization.c
SRC_NN     = $(SRC_DIR)/neural_network.c

OBJ_SOLVER = $(SRC_SOLVER:.c=.o)
OBJ_BINA   = $(SRC_BINA:.c=.o)
OBJ_NN     = $(SRC_NN:.c=.o)

ALL_OBJ    = $(OBJ_SOLVER) $(OBJ_BINA) $(OBJ_NN)

all: $(TARGETS)

solver: $(OBJ_SOLVER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_binarization: $(OBJ_BINA)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

nn: $(OBJ_NN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(ALL_OBJ)

distclean: clean
	rm -f $(TARGETS)

.PHONY: all clean distclean solver test_binarization nn
