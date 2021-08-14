all: clean build
build:
	mkdir -p ./build
	gcc ./src/main.c -o ./build/leo_lang.out
clean:
	rm -rf build
