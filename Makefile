CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 `sdl2-config --cflags` -O2 -Iinclude
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lm

# Složky
SRC_DIR = src
ASSETS_DIR = assets
BUILD_DIR = build

# Seznam souborů
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/menu.c $(SRC_DIR)/scoreboard.c $(SRC_DIR)/game.c
OBJ = $(SRC:.c=.o)
TARGET = breakout

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
