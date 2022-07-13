#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "tlpi_hdr.h"



int main(int argc, char *argv[])
{
	bool	append = false;
	char	*file_name = NULL;

	if (argc<2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s [a] file\n", argv[0]);

	int opt;

	opt = getopt(argc, argv, "a:");
	if (opt == 'a')
	{
		append = true;
		file_name = optarg;


	}
	else if (opt == -1)
	{
		file_name = argv[1];
	}
	else 
	{


		printf("err arg\n");
		exit(-1);
	}

	int open_flag = O_RDWR | O_CREAT;
	if (append)
		open_flag |= O_APPEND;
	else 
		open_flag |= O_TRUNC;

	int fd = open(file_name, open_flag, S_IRUSR | S_IWUSR);
	if (fd == -1)
		errExit("open");
	
	uint8_t		rd_buf[1024];
	int			rd_len;

	while (1)
	{

		rd_len = read(0, rd_buf, sizeof(rd_buf));

		if (rd_len <= 0)
		{

			break;
		}

		printf("%s", rd_buf);
		write(fd, rd_buf, rd_len);

	}

		

	//printf("file_name=%s. %s\n", file_name, append?"append":"");
	return 0;
}
