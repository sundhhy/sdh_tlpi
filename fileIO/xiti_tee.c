#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
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

		

	printf("file_name=%s. %s\n", file_name, append?"append":"");
	return 0;
}
