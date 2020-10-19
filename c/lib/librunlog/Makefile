all: librunlog.so

librunlog.so: runlog.c
	gcc -shared runlog.c -o librunlog.so -fPIC -Wall

testlog:runlog.c
	gcc -DDEBUG runlog.c wmtime.c -o testlog

clean:
	-rm -f librunlog.so
	-rm -f testlog
	-rm -f test
