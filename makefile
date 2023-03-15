CC=gcc
FLAGS=-Wall -DUNICODE
DEBUG=-DDEBUG -g3 -Wall -Wextra -Walloc-zero -Wformat-overflow -Wformat-truncation -Wnonnull -Wvla
LINKER=-lmingw32 -lSDL2main -lSDL2 -Bstatic

SRC=$(wildcard ./src/*.c) $(wildcard ./src/*/*.c)

INC=-I"src/" -I"include/"
LIB=-L"lib/SDL2"

OUT=bin\\wolf.exe

CLEAN=del /f $(OUT)

all: $(OUT)

$(OUT): .FORCE

.FORCE: $(SRC)
	$(CLEAN)
	$(CC) $(SRC) $(FLAGS) $(INC) $(LIB) $(LINKER) -o $(OUT)

debug: $(SRC)
	$(CC) $(SRC) $(FLAGS) $(DEBUG) $(INC) $(LIB) $(LINKER) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	$(CLEAN)

.PHONY: clean