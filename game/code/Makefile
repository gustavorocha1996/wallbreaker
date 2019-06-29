CC=gcc
CFLAGS=-Wall
LIBS=-lncurses

CFILES = menu.c inter.c trans.c kbhit.c bonus.c global.c wallbreaker.c  
HFILES = menu.h inter.h trans.h kbhit.h bonus.h
OFILES = menu.o inter.o trans.o kbhit.o bonus.o global.o wallbreaker.o 

all:		wallbreaker
		mv wallbreaker ../bin
		rm -f $(OFILES)
		../bin/wallbreaker

wallbreaker: 	$(OFILES) 
		$(CC) $(LDFLAGS) -o$@ $(OFILES) $(LIBS)

.c.o:
		$(CC) -I../header -c $(CFLAGS) $(OPTIONS) $<
clean:
		rm -f wallbreaker $(OFILES)

run:		all
	


	






