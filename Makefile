
CC=clang


all: 
	$(CC) -o ./out/a.out main.c


testing:
	$(CC) -o ./out/test.out -Wall test/main_test.c

debug:
	$(CC) -o ./out/debug.out -Wall main.c


clean: 
	rm -r ./out/