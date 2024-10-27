CC = gcc
CFLAGS = -I./src/include -std=c17 -O2 -Wall -Wextra -Wpedantic
OFLAGS = -c

BUILD_DIR = ./bin

HEADERS =  $(wildcard src/*.h) $(wildcard src/**/*.h) $(wildcard src/**/**/*.h)
CSRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJS = $(CSRC:.c=.o)

.PHONY: all clean
all: dirs leilao

dirs:
	mkdir -p $(BUILD_DIR)

%.o: %.c $(HEADERS)
	$(CC) $< -o $@ $(OFLAGS) $(CFLAGS)

leilao: $(OBJS)
	$(CC) -o $(BUILD_DIR)/leilao $(OBJS) $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(OBJS)
