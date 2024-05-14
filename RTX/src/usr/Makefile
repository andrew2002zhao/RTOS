CC = gcc
CFLAGS = -m32 -I../INC  -I../kernel -I../board/DE1_SoC_A9
SRCS = usr_tst.c usr_mem.c
OBJS = $(SRCS:.c=.o)
OUTPUT = output

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OBJS) $(OUTPUT)