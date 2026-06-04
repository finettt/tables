CC = cc
CFLAGS = -g -Wall
OBJ_DIR = build
BIN_DIR = build/bin
OUTPUT = $(BIN_DIR)/tables

OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/node.o $(OBJ_DIR)/token.o $(OBJ_DIR)/var.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/math_token.o $(OBJ_DIR)/math_node.o

all: tables

tables: $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJS) -lm

$(OBJ_DIR)/main.o: main.c node.h token.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/node.o: node.c var.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c node.c -o $(OBJ_DIR)/node.o

$(OBJ_DIR)/token.o: token.c token.h node.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c token.c -o $(OBJ_DIR)/token.o

$(OBJ_DIR)/var.o: var.c var.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c var.c -o $(OBJ_DIR)/var.o

$(OBJ_DIR)/utils.o: shared/utils.c shared/utils.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c shared/utils.c -o $(OBJ_DIR)/utils.o

$(OBJ_DIR)/math_token.o: engines/math/token.c engines/math/token.h engines/math/node.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c engines/math/token.c -o $(OBJ_DIR)/math_token.o

$(OBJ_DIR)/math_node.o: engines/math/node.c engines/math/node.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c engines/math/node.c -o $(OBJ_DIR)/math_node.o

clean:
	rm -rf $(OBJ_DIR) *.o

