.PHONY:clean all

all: libesqlite.so

CC=gcc
CFLAGS+=-Wall -ggdb -fPIC
CFLAGS+=-DSQLITE_HAS_CODEC
INC=-I./sqlite3/
LIBS=-lpthread -ldl

OBJS+=esqlite.o
OBJS+=esqlite_extend.o

SQLITE_OBJS+=sqlite3.o
SQLITE_OBJS+=rijndael.o
SQLITE_OBJS+=sqlite3code.o

libesqlite.so: $(OBJS) $(SQLITE_OBJS)
	$(CC) $(CFLAGS) $(INC) -shared $(OBJS) $(SQLITE_OBJS) -o libesqlite.so $(LIBS)

test:test.c libesqlite.so
	gcc -g -DDEBUG test.c -o test -L./ -lesqlite -Wl,-rpath=./

enc_test:enc_test.c libesqlite.so
	gcc -g -DDEBUG enc_test.c -o test -L./ -lesqlite -Wl,-rpath=./

$(SQLITE_OBJS):%.o:sqlite3/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	-rm -f libesqlite.so
	-rm -f $(OBJS)
	-rm -f $(SQLITE_OBJS)
	-rm -f test

