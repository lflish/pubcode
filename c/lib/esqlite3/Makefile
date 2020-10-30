all: libesqlite.so

libesqlite.so: esqlite.c
	gcc -g -shared esqlite.c -o libesqlite.so -fPIC -Wall

test:test.c libesqlite.so
	gcc -g -DDEBUG test.c -o test -L./ -lesqlite -lsqlite3 -Wl,-rpath=./

clean:
	-rm -f libesqlite.so
	-rm -f testsql
	-rm -f test
