CC = g++
IDIR = inc
CFLAGS = -I $(IDIR) -Wall -Wextra -lm -g -O2 -std=c++11

_DEPS = 2048.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = src/2048.o main.o
ODIR=obj
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $(patsubst %,$(ODIR)/%,$(notdir $@)) $< $(CFLAGS)

2048: $(OBJ)
	$(CC) -o $@ $(patsubst %,$(ODIR)/%,$(notdir $^)) $(CFLAGS)

clean:
	-rm -f $(ODIR)/*.o 2048 traces/*.trace2048 traces/*.html


