# Compilador
CC := gcc

# Flags compilador
CFLAGS := -Wall -Wextra -Wno-unknown-pragmas

# Diretorias
SRC_DIR := src
BUILD_DIR := build

# Targets
PROG := bemestar
LIB := GestorDadosIO

# Encontrar todos os ficheiros source dentro das diretorias (.c)
PROG_SRCS := $(wildcard $(SRC_DIR)/LESI_PI_TP_a28602/*.c)
LIB_SRCS := $(wildcard $(SRC_DIR)/GestorDadosIO/*.c)

# Criar objetos (.o) dos ficheiros source (.c)
PROG_OBJS := $(PROG_SRCS:.c=.o)
LIB_OBJS := $(LIB_SRCS:.c=.o)

# Target principal
all: $(PROG) move

# Target Programa
$(PROG): $(PROG_OBJS) lib$(LIB).so | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -I$(SRC_DIR)/GestorDadosIO -L. -l$(LIB) -Wl,-rpath,'$$ORIGIN'

# Shared library target
lib$(LIB).so: $(LIB_OBJS) | $(BUILD_DIR)
	$(CC) -shared -o $@ $^

# Compilacao dos objetos (.o) para o programa
%.o: $(SRC_DIR)/LESI_PI_TP_a28602/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(SRC_DIR)/GestorDadosIO -I$(SRC_DIR)/LESI_PI_TP_a28602

# Compilacao dos objetos (.o) para a biblioteca
%.o: $(SRC_DIR)/GestorDadosIO/%.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $< -I$(SRC_DIR)/LESI_PI_TP_a28602

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Move files to build directory
move: $(BUILD_DIR)
	mv $(PROG) lib$(LIB).so $(BUILD_DIR)

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean move
