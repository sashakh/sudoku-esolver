CFLAGS := -Wall -g

progs := sudoku-esolver
tools := gen-hz

all: $(tools) $(progs)

sudoku-esolver: main.o solver.o collection.o reader.o

solver.o: CFLAGS += -O5

$(progs): %:
	$(CC) $(CFLAGS) -o $@ $^

$(tools): %: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *~ *.o $(tools) $(progs)

dep:
	$(CC) -MM $(CFLAGS) $(wildcard *.c) > .depend
-include .depend
