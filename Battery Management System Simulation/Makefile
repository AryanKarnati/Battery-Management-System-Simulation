CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = bms_sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TARGET) test/test_cases
	./test/test_cases

test/test_cases: test/test_cases.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f src/*.o $(TARGET) test/test_cases

.PHONY: all test clean