# Directories
S_DIR=src
B_DIR=build

$(shell mkdir -p $(B_DIR))

# Files
S_FILES=$(S_DIR)/*.c

# Output
EXEC=PuissanceC

# Build settings
CC=gcc
# SDL options
CFLAGS=-O3 -lSDL `sdl2-config --cflags --libs`


all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(CFLAGS)

build_run:Build
	$(EXEC)

clean:
	rm -rf $(B_DIR)/*
