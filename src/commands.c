/*
** EPITECH PROJECT, 2018
** commands
** File description:
** commands
*/

#include "ftp.h"

int notimplemented(t_info *info)
{
	for (int i = 0; info->args[i] != NULL; i++) {
		dprintf(info->client_fd, "loooool : %s\n", info->args[i]);
	}
	dprintf(info->client_fd, "COUCOU BONNE FCT\n");
	return (0);
}

int cmd_help(__attribute__((unused))t_info *info)
{
	dprintf(info->client_fd,
		"214-The following commands are recognized.\r\n");
	for (int i = 0; com[i].command != NULL; i++) {
		dprintf(info->client_fd, " %s", com[i].command);
	}
	dprintf(info->client_fd, "\n214 Help OK.\r\n");
	return (0);
}

int cmd_printwd(t_info *info)
{
	char *path = calloc(PATH_MAX, sizeof(char));

	if (path == NULL) {
		dprintf(info->client_fd, "xxx Error (RFC compliant)");
		return (0);
	}
	path = getcwd(path, PATH_MAX);
	if (path == NULL) {
		dprintf(info->client_fd, "xxx Error (RFC compliant)");
		return (0);
	}
	dprintf(info->client_fd, "257 \"%s\"\r\n", path);
	return (0);
}
