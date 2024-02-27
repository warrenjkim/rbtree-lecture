CC=gcc

CFLAGS=-Wall -g

TARGET=rbt

SRC=main.c rbt.c
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)


