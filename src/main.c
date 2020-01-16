/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "ftp.h"

int main(int ac, char **av)
{
	if (ac != 3)
		return (84);
	set_sig_handlers();
	if (chdir(av[2]) == -1) {
		dprintf(2, "Path argument is  not valid: %s\n", av[2]);
		return (84);
	}
	server(atoi(av[1]), "coucou");
	return (0);
}
