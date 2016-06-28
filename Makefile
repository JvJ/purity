
# C Compiler
CC = clang

# Compiler flags
# -g : Debugging information
# -Wall : Most compiler warnings
CFLAGS = -g -Wall

# Files to link
# LFLAGS = -lcs50

OBJECTS = test_main.o ws_trie.o
EXE = test_main

all: test_main

test_main: $(OBJECTS) ws_trie test_main.c
	$(CC) $(OBJECTS) -o $(EXE).exe

ws_trie: ws_trie.c
	$(CC) -c ws_trie.c


# $( LFLAGS ) -- was the last param previously
