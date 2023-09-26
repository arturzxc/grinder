# Makefile for a C++ program linked with X11 and Xtst libraries

# Compiler
CXX = g++

# Source files
SRCS = Main.cpp

# Libraries to link
LIBS = -lX11 -lXtst

# Default target
all: a.out

# Compilation and linking
a.out: $(SRCS)
	$(CXX) $^ -o $@ $(LIBS)

# Clean up object files and the executable
clean:
	rm -f a.out

# Phony target to force the rebuild
build:
	@$(MAKE) clean
	@$(MAKE) all

.PHONY: all force-rebuild clean
