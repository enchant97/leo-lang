CC=gcc
SOURCES=src/main.c src/tokens.c src/utils.c src/writers.c

all: clean build
build:
	mkdir -p ./build
	$(CC) $(SOURCES) -o ./build/leo_lang.out
clean:
	rm -rf build
