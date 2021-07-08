.PHONY:clean all

all: libesqlite.so libsqlite3.a

CC=gcc
CFLAGS+=-Wall -ggdb -fPIC
CFLAGS+=-DSQLITE_HAS_CODEC
INC=-I./sqlite3/

LIBS=-lpthread -ldl libsqlite3.a

OBJS+=esqlite.o
OBJS+=esqlite_extend.o

SQLITE_OBJS+=sqlite3.o
SQLITE_OBJS+=rijndael.o
SQLITE_OBJS+=sqlite3code.o

libesqlite.so: $(OBJS) libsqlite3.a
	$(CC) $(CFLAGS) $(INC) -shared $(OBJS) $(SQLITE_OBJS) -o libesqlite.so $(LIBS)

libsqlite3.a:$(SQLITE_OBJS)
	ar -cr libsqlite3.a $(SQLITE_OBJS)

test:test.c libesqlite.so
	gcc -g -DDEBUG test.c -o test -L./ -lesqlite -Wl,-rpath=./

enc_test:enc_test.c libesqlite.so
	gcc -g -DDEBUG enc_test.c -o test -L./ -lesqlite -Wl,-rpath=./

tools_esqlite:tools_esqlite.c libesqlite.so
	gcc -g -DDEBUG tools_esqlite.c -o tools_esqlite -L./ -lesqlite -Wl,-rpath=./

$(SQLITE_OBJS):%.o:sqlite3/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	-rm -f libesqlite.so
	-rm -f libsqlite3.a
	-rm -f $(OBJS)
	-rm -f $(SQLITE_OBJS)
	-rm -f test

