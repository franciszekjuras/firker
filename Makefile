IDIR =include
#LDIR =
CXX=g++
CXXFLAGS=-I$(IDIR) -std=c++14
#-L$(LDIR)
ODIR=obj

#LIBS=-lm
LIBS= -lm

_DEPS = firker.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o firker.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all

all: firker

$(ODIR)/%.o: %.cpp $(DEPS) | $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR):
	mkdir -p $@

firker: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
