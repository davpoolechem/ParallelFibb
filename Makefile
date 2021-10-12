CC=g++
LINKER=g++

SRCDIR = src
OBJDIR = obj
BINDIR = bin

CFLAGS=-I. -I$(SRCDIR) -O3 -g -fopenmp
LDFLAGS=-lpthread -fopenmp

rm = rm

TARGET = fibb

SOURCES := $(wildcard $(SRCDIR)/*.cc)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@
	$(LINKER) $(LDFLAGS) $(OBJECTS) -o $(BINDIR)/$(TARGET)

.PHONY: clean
clean:
	$(rm) obj/*.o
	$(rm) bin/*
