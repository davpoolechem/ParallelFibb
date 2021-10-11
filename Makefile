CC=g++
CFLAGS=-I. -O3

LINKER=g++
LDFLAGS=-lpthread

SRCDIR = src
OBJDIR = obj
BINDIR = bin

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
