# Makefile for thermal simulation
# Author: 03.24.2016
# Y. Yang

TARGET  = SimCOMETCaptureQuench.exe
CXX     = g++
MAINSRC = main.cpp
VPATH   = src
LIBSRC  = 

SRC     = $(MAINSRC) $(LIBSRC)
OBJS    = $(SRC:.cpp=.o)

CXXLIBS   = -L$(SOFTWARE)/gsl/gsl-2.1/lib -lgsl -lgslcblas -lm
CXXFLAGS  = -O3 -Wall -I include -I$(SOFTWARE)/gsl/gsl-2.1/include
ROOTLIBS  = `root-config --evelibs`
ROOTFLAGS = `root-config --cflags`

CXXLIBS  += $(ROOTLIBS)
CXXFLAGS += $(ROOTFLAGS)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXLIBS) $^ -o $@

.o:.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: install
install:
	mkdir -p bin
	cp -p $(TARGET) bin

