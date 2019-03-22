#include <cerrno>
#include <stdlib.h>
#include <stdio.h>
#include "error.hpp"

void die(const char* msg)
{

	if (errno == 0)
	{
		fprintf(stderr, msg);
		fprintf(stderr, "\n");
		exit(1);
	}

	perror(msg);
	exit(1);

}