/*
** EPITECH PROJECT, 2018
** commands2
** File description:
** commands2
*/

#include "ftp.h"

int cmd_user(t_info *info)
{
	if (info->login == 1) {
		dprintf(info->client_fd,
			"530 Can't change from guest user.\r\n");
		return (0);
	}
	if (info->args[0] != NULL) {
		info->username = strdup(info->args[0]);
		dprintf(info->client_fd,
			"331 Please specify the password.\r\n");
		return (0);
	}
	info->username = NULL;
	dprintf(info->client_fd, "530 Permission denied.\r\n");
	return (0);
}

int cmd_pass(t_info *info)
{
	if (info->login == 1) {
		dprintf(info->client_fd, "230 Already logged in.\r\n");
		return (0);
	}
	if (info->username == NULL) {
		dprintf(info->client_fd, "503 Login with USER first.\r\n");
		return (0);
	}
	if (info->args[0] != NULL) {
		dprintf(info->client_fd, "530 Login incorrect.\r\n");
		return (0);
	}
	if (strncmp(info->username, "Anonymous", 4) == 0) {
		dprintf(info->client_fd, "230 Login successful.\r\n");
		info->login = 1;
		return (0);
	}
	return (0);
}

int cmd_quit(t_info *info)
{
	dprintf(info->client_fd, "221 Goodbye.\r\n");
	return (-1);
}

int cmd_noop(__attribute__((unused))t_info *info)
{
	dprintf(info->client_fd, "200 NOOP ok.\r\n");
	return (0);
}
