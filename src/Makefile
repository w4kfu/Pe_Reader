include ../makefile.rules

OBJS = $(FILES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) $^ -o ../$(NAME_PROJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o

distclean: clean
	rm -f *~
