# Default target
all: rebuild; 

# Clean up object files and the executable
clean:
	rm -f a.out

# Compilation and linking
a.out: $(SRCS)
	g++ Main.cpp -o a.out -lX11 -lXtst -lXcomposite


# clean & build
rebuild:
	@$(MAKE) clean
	@$(MAKE) a.out
	echo "SUCCESS!"

