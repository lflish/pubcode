#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct mmm{
	char pos[32];
	char file[4096 - 32];
};

int
main(int argc, char *argv[])
{
	char *addr;
	int fd;
	struct stat sb;
	off_t offset, pa_offset;
	size_t length;
	ssize_t s;

	fd = open(argv[1], O_RDWR|O_CREAT, 0644);
	if (fd == -1)
		handle_error("open");

	//addr = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, fd, 0);
	addr = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
		handle_error("mmap");


	printf("addr=%s\n", addr);

	strcpy(addr, "jjjjjj");

	printf("addr=%s\n", addr);

	sleep(2);

	return 0;

	exit(EXIT_SUCCESS);
}
