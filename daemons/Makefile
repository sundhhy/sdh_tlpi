include ../Makefile.inc

#GEN_EXE = atomic_append bad_exclusive_open copy \
	multi_descriptors seek_io t_readv t_truncate

SYSLOG_EXE = t_syslog

EXE = ${SYSLOG_EXE} 

all : ${EXE}


clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
