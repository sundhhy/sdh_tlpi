#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif


int main(int argc, char *argv[])
{
	int fd_input, fd_output, open_flags;
	mode_t	file_perms;
	ssize_t	num_read;
	char buf[BUF_SIZE];

	if (argc != 3)
	{
		usageErr("%s old-file new-file\n", argv[0]);
	}


	fd_input = open(argv[1], O_RDONLY);
	if (fd_input == -1)
		errExit("open file %s\n", argv[1]);

	open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH;  // rw-rw-rw
	fd_output = open(argv[2], open_flags, file_perms);
	if (fd_output == -1)
		errExit("open file %s\n", argv[2]);

	while ((num_read = read(fd_input, buf, BUF_SIZE)) > 0)
	{
		if (write(fd_output, buf, num_read) != num_read)
		{
			fatal("write() returned error or paritial write occurred");
		}

	}

	if (num_read == -1)
		errExit("read");
	if (close(fd_input))
		errExit("close input");
	if (close(fd_input))
		errExit("close output");

	exit(EXIT_SUCCESS);
}
