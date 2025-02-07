CC = gcc               # The compiler to use
CFLAGS = -Wall -g      # Compiler flags for warnings and debugging info
SRC = main.c auth_functions.c   # Source files
OBJ = $(SRC:.c=.o)     # Object files (compile all .c files into .o files)
EXEC = your_program     # The final executable name

# Default target to build the project
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(EXEC)

# Target to run the program
run: $(EXEC)
	./$(EXEC)
