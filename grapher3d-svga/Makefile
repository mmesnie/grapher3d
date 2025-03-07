grapher: main.o graph.o calc.o trans.o function.o stacks.o lnodes.o 
	cc -o grapher main.o graph.o calc.o trans.o function.o stacks.o lnodes.o -lm -lvga -lncurses

main.o: main.c
	cc -c main.c

graph.o: graph.c
	cc -c graph.c

trans.o: trans.c
	cc -c trans.c

calc.o: calc.c
	cc -c calc.c

function.o: function.c
	cc -c function.c

stacks.o: stacks.c
	cc -c stacks.c

lnodes.o: lnodes.c
	cc -c lnodes.c

clean:
	rm -f *.o grapher
