
CC = gcc

CFLAGS = -O2 -Iinclude

SRCS = src/main.c src/c_alloc.c src/helpers/memory_helper.c src/utils/handle_err.c src/utils/libs.c

OBJS = $(SRCS:.c=.o)

OUTPUT_DIR = bin

TARGET = $(OUTPUT_DIR)/the_program

all: $(OUTPUT_DIR) $(TARGET)

$(OUTPUT_DIR): 
	mkdir -p $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET)
	
