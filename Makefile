all:
	gcc ./src/*.c -I ./include/ -o main -Wall -g

run:
	./main