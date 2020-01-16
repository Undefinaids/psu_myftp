/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** signal handlers
*/

#include "ftp.h"

void sigint_handler(int signum)
{
	close(fd);
	exit(0);
	(void) signum;
}

int set_sig_handlers(void)
{
	struct sigaction act;

	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
	return (0);
}
