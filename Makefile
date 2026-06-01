CC = cc
CFLAGS = -g -Wall
OUTPUT = build/

all: tables


 tables: main.o node.o token.o var.o
	mkdir -p $(OUTPUT)bin/
	cd $(OUTPUT)
	$(CC) $(CFLAGS) -lm -o $(OUTPUT)bin/tables $(OUTPUT)main.o $(OUTPUT)node.o $(OUTPUT)token.o $(OUTPUT)var.o


$(OUTPUT)main.o: main.c node.h token.h
	$(CC) $(CFLAGS) -c main.c -o $(OUTPUT)main.o

$(OUTPUT)node.o: node.c var.h
	$(CC) $(CFLAGS) -c node.c -o $(OUTPUT)node.o

$(OUTPUT)token.o: token.c token.h node.h
	$(CC) $(CFLAGS) -c token.c -o $(OUTPUT)token.o

$(OUTPUT)var.o: var.c var.h
	$(CC) $(CFLAGS) -c var.c -o $(OUTPUT)var.o
