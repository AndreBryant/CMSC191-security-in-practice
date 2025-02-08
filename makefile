CC = gcc               # The compiler to use
CFLAGS = -Wall -g -I./src   # Compiler flags for warnings, debugging info, and include path
SRC = main.c src/auth_functions.c   # Source files
OBJ = $(SRC:.c=.o)     # Object files (compile all .c files into .o files)
EXEC = auth_simulation # The final executable name

# Default target to build the project
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule to compile .c files into .o files
# Adjusted to handle .o files inside src/
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(EXEC)

# Target to run the program
run: $(EXEC)
	./$(EXEC)
