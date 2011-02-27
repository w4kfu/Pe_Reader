include makefile.rules

OBJS = $(FILES:.c=.o)

all:
	cd ./src/ && $(MAKE)
clean:
	cd ./src/ && $(MAKE) clean

distclean: clean
	cd ./src/ && $(MAKE) distclean
	rm -f makefile.rules
	rm -rf ./doc
	rm -f $(NAME_PROJ)