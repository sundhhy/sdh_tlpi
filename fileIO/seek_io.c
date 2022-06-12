#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "tlpi_hdr.h"



int main(int argc, char *argv[])
{
	size_t		len;
	off_t		offset;
	unsigned char *buf;
	int fd, ap, j;


	size_t		num_read, num_write;

	if (argc<3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);

	fd = open(argv[1], O_RDWR | O_CREAT, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | \
				S_IROTH | S_IWOTH);

	if (fd==-1)
		errExit("open");

	for (ap=2; ap<argc; ap++)
	{
		switch (argv[ap][0]) 
		{
			case 'r':
			case 'R':
				len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
				buf = malloc(len);
				if (buf == NULL)
					errExit("malloc");
				num_read = read(fd, buf, len);
				if (num_read == 0)
				{
					printf("%s: end-of-file\n", argv[ap]);
				}
				else 
				{

					printf("%s: ", argv[ap]);
					for (j=0; j<num_read; j++)
					{
						if (argv[ap][0] == 'r')
							printf("%c", isprint(buf[j]) ? buf[j]:'?');
						else 
							printf("%02x ", buf[j]);
					}
					printf("\n");
				}
				free(buf);
				break;
			case 'w':
				num_write = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
				if (num_write == -1)
					errExit("wite");
				printf("%s: write %ld bytes\n", argv[ap], (long)num_write);
				break;

			case 's':
				offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
				if (lseek(fd, offset, SEEK_SET) == -1)
					errExit("lseek");
				printf("%s: seek succeeded\n", argv[ap]);
				break;
			default:
				cmdLineErr("Argument must start wit [rRws]: %s\n", argv[ap]);

		}



	}



	if (close(fd) == -1)
		errExit("close");

	exit(EXIT_SUCCESS);


}
