
CC=clang
OPT=-O2
DEBUG_FLAG=-DDEBUG

COMPILE_FILE=main.c
TEST_FILE=./test/main_test.c
TUI_TEST_FILE=./test/tui_test.c
NCURSES_FLAG=-lncurses
BUILD_DIRECTORY= ./out
WARNING_FLAGS=-Wall -pedantic


all: 
	$(CC) $(OPT) -o ./out/a.out $(COMPILE_FILE)


testing:
	$(CC) $(OPT) -o ./out/test.out $(WARNING_FLAGS) $(TEST_FILE)

tui_testing:
	$(CC) $(OPT) $(NCURSES_FLAG) -o ./out/test.out $(WARNING_FLAGS) $(TUI_TEST_FILE)

debug:
	$(CC) $(DEBUG_FLAG) -o ./out/debug.out $(WARNING_FLAGS) $(COMPILE_FILE)

test_debug:
	$(CC) $(DEBUG_FLAG) -o ./out/debug.out $(WARNING_FLAGS) $(TEST_FILE)


clean: 
	rm -r ./out