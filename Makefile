# Makefile para Tetris Stack - Fila de Peças (C)
# Uso:
#   make            -> compila
#   make run        -> compila e executa
#   make clean      -> remove binários

CC      := gcc
CFLAGS  := -std=c99 -O2 -Wall -Wextra -Wshadow -Wconversion
LDFLAGS :=
TARGET  := tetris_stack_fila
SRC     := tetris_stack_fila.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)
