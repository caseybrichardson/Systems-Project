
CC = g++
C = gcc
P = -c

FILES = cli.cpp CCLI/inc/cstr.cpp sicengine.o
INCLUDES = -ICCLI/inc/
INCLUDES2 = -I../inc/
OUT_EXE = -o cli

build: $(FILES)
	$(CC) $(FILES) $(INCLUDES) $(OUT_EXE)

withc:
	 $(C) $(P) sicengine.c; $(CC) $(P) $(FILES) $(INCLUDES); g++ sicengine.o cli.o -o cli

load:
	$(CC) ./CCLI/src/load.cpp CCLI/inc/cstr.cpp $(INCLUDES) -o load; mv load ./CCLI/bin/

execute:
	$(CC) ./CCLI/src/execute.cpp CCLI/inc/cstr.cpp $(INCLUDES) -o execute; mv execute ./CCLI/bin/

debug:
	$(CC) ./CCLI/src/debug.cpp CCLI/inc/cstr.cpp $(INCLUDES) -o debug; mv debug ./CCLI/bin/

dump:
	$(CC) ./CCLI/src/dump.cpp CCLI/inc/cstr.cpp $(INCLUDES) -o dump; mv dump ./CCLI/bin/

help:
	$(CC) ./CCLI/src/help.cpp CCLI/inc/cstr.cpp $(INCLUDES) -o help; mv help ./CCLI/bin/

assemble:
	$(CC) ./CCLI/src/assemble.cpp CCLI/inc/assemblerStr.cpp CCLI/inc/cstr.cpp CCLI/inc/assembler.cpp $(INCLUDES) -o assemble; mv assemble ./CCLI/bin/

directory:
	$(CC) ./CCLI/src/directory.cpp CCLI/inc/cstr.cpp $(INCLUDES) -o directory; mv directory ./CCLI/bin/

programs:
	make load; make execute; make debug; make dump; make help; make assemble; make directory

all:
	make programs; make build