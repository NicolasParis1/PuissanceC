# Directories
S_DIR=.

# Files
S_FILES=$(S_DIR)/*.c

# Output
EXEC=PuissanceC

# Build settings
CC=gcc
# SDL options
CFLAGS=-O3 -lSDL2 `sdl2-config --cflags --libs`


all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(CFLAGS)

build_run:Build
	$(EXEC)

