CFLAGS += -Wall -g -O2 # -pg

progs := sudoku-esolver
tools := gen-hz

all: $(tools) $(progs)

sudoku-esolver: main.o solver.o collection.o reader.o
$(tools): %: %.o

$(tools) $(progs):
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *~ *.o $(tools) $(progs)

dep:
	$(CC) -MM $(CFLAGS) $(wildcard *.c) > .depend
-include .depend
