#include "../include/cub3d.h"

void error_exit(const char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
