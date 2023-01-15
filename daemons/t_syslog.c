#include <syslog.h>
#include "tlpi_hdr.h"

static void
usageError(const char *progName)
{
	fprintf(stderr,"Usage: %s [-p] [-e] [-l level] \"message\"\n", progName);
	fprintf(stderr, "		-p		log PID\n");
	fprintf(stderr, "		-e		log to stderr also\n");
	fprintf(stderr, "		-l		level (g=EMERG; a=ALERT; c=CRIT; E=ERR\n");
	fprintf(stderr, "						w=WANING; n=NOTICE; i=INFO; d=DEBUG)\n");
	exit(EXIT_FAILURE);


}


int 
main(int argc, char *argv[])
{
	int level, options, opt;

	options = 0;
	level = LOG_INFO;

	while ((opt = getopt(argc, argv, "l:pe")) != -1)
	{

		switch (opt) {

			case 'l':
				switch (optarg[0]) {
					case 'a':	level = LOG_ALERT;		break;
					case 'c':	level = LOG_CRIT;		break;
					case 'e':	level = LOG_ERR;		break;
					case 'w':	level = LOG_WARNING;	break;
					case 'n':	level = LOG_NOTICE;		break;
					case 'i':	level = LOG_INFO;		break;
					case 'd':	level = LOG_DEBUG;		break;
					default:	cmdLineErr("Bad facility: %c\n", optarg[0]);


				}
			case 'p':
				options |= LOG_PID;
				break;
			case 'e':
				options |= LOG_PERROR;
				break;
			default:
				fprintf(stderr, "Bad options\n");
				usageError(argv[0]);

		}

	}

	if (argc != optind +1)
		usageError(argv[0]);

	openlog(argv[0], options, LOG_USER);
	syslog(LOG_USER | level, "%s", argv[optind]);
	closelog();
	exit(EXIT_SUCCESS);

}
