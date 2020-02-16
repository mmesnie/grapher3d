ARCH = \"`uname`\"
CFLAGS = -O -DARCH=$(ARCH)
CC     = cc
FILES  = widgets.o child.o main.o graph.o calc.o \
         trans.o postfix2real.o get_points.o \
         infix2postfix.o graph_points.o

grapher3d: $(FILES)
	$(CC) $(CFLAGS) -o grapher3d $(FILES) -lm

clean:
	rm -rf *.o grapher3d
