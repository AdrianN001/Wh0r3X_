CC 			:= clang
CFLAGS 		:= 
PROJECT_DIR := $(shell pwd)
CFLAGS		+= -I$(PROJECT_DIR)

LDLIBS		:= -lncurses

SourceDirectory 		:= src
HeaderDirectory 		:= whorex


SourceFiles	:= $(shell find $(SourceDirectory)/ -name "*.c" | tr '\n' ' ')
HeaderDirectoryFiles	:= $(shell find $(HeaderDirectory)/ -name "*.h" | tr '\n' ' ')

ObjectFiles	:= main.o
ObjectFiles += $(patsubst $(SourceDirectory)/%.c, $(SourceDirectory)/%.o, $(SourceFiles))

BinaryOutput := a.out


all := $(BinaryOutput)

$(BinaryOutput): $(ObjectFiles)  $(SourceDirectory)
	$(CC) -o $@ $(CFLAGS) $(ObjectFiles) $(LDLIBS)

$(SourceDirectory)/%.o: $(SourceDirectory)/%.c
	$(CC) -c $< $(CFLAGS) $(LDLIBS) -o $@


clean: 
	rm -r $(ObjectFiles)
	rm $(BinaryOutput)
