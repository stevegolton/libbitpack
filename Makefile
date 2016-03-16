CXX = g++
CC = gcc
CFLAGS = -c -g3 -O3 -time
#WARNINGS = -Werror -Wall -Wextra -pedantic-errors -Wformat=2 -Wno-import -Wimplicit -Wmain -Wchar-subscripts -Wsequence-point -Wmissing-braces -Wparentheses -Winit-self -Wswitch-enum -Wstrict-aliasing=2 -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wdisabled-optimization -Wunused-macros -Wno-unused
WARNINGS =
LDFLAGS =
LIBRARIES = -lcmocka
SOURCES = main.c bit_pack.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = testme.out


all: $(SOURCES) $(EXECUTABLE)

test: all
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

debug: CFLAGS += -DDEBUG -g
debug: $(SOURCES) $(EXECUTABLE)

.c.o:
	$(CC) $< -o $@ $(CFLAGS) $(WARNINGS)

.PHONY: doc clean test     
doc: 
	$(DOXYGEN) doxygen.config    
clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
