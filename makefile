TARGET=clib
CFLAGS= -Wall
OPT_LVL=
LDFLAGS=-I$(IDIR)

IDIR=./include
SDIR=./src
ODIR=./bin

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ifeq ($(shell which gcc-8), /usr/local/bin/gcc-8)
		CC=gcc-8#MacOS GNU gcc, not clang
		CXX=g++-8
	else
		CC=clang
		CXX=clang
	endif
else
	CC=gcc#GNU gcc
	CXX=gcc
endif

_DEPS=main.h debug.h error.h array.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_SRC=main.c debug.c error.c
SRC=$(patsubst %,$(SDIR)/%,$(_SRC))

_OBJ=main.o debug.o error.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

all: $(ODIR)/$(TARGET)
	@printf "%b" "Compilation successful\n"

$(ODIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OPT_LVL) $(LDFLAGS) $^ -o $@

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) $(OPT_LVL) -MMD -c $< -o $@

-include $(ODIR)/*.d

.PHONY: clean

clean:
	rm -f $(ODIR)/*
