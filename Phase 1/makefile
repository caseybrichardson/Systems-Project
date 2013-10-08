
CC = g++

FILES = phase1.cpp CCLI/inc/cstr.cpp
INCLUDES = -ICCLI/inc/
INCLUDES2 = -I../inc/
OUT_EXE = -o cli

build: $(FILES)
	$(CC) $(FILES) $(INCLUDES) $(OUT_EXE)

load:
	$(CC) ./CCLI/src/load.cpp -o load; mv load ./CCLI/bin/

execute:
	$(CC) ./CCLI/src/execute.cpp -o execute; mv execute ./CCLI/bin/

debug:
	$(CC) ./CCLI/src/debug.cpp -o debug; mv debug ./CCLI/bin/

dump:
	$(CC) ./CCLI/src/dump.cpp -o dump; mv dump ./CCLI/bin/

help:
	$(CC) ./CCLI/src/help.cpp $(INCLUDES) -o help; mv help ./CCLI/bin/

assemble:
	$(CC) ./CCLI/src/assemble.cpp -o assemble; mv assemble ./CCLI/bin/

directory:
	$(CC) ./CCLI/src/directory.cpp -o directory; mv directory ./CCLI/bin/

programs:
	make load; make execute; make debug; make dump; make help; make assemble; make directory

all:
	make programs; make build