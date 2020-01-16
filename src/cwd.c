/*
** EPITECH PROJECT, 2018
** cwd
** File description:
** cwd
*/

#include "ftp.h"

char    *my_strcat(char *dest, char *src)
{
	int   i;
	int   j;
	char  *res;

	i = -1;
	j = -1;
	while (dest[++i] != '\0');
	while (src[++j] != '\0');
	if ((res = malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	res[i + j] = '\0';
	i = -1;
	while (dest[++i] != '\0')
		res[i] = dest[i];
	j = -1;
	while (src[++j] != '\0')
		res[i + j] = src[j];
	return (res);
}

int cmd_cwd(t_info *info)
{
	char *newpath;
	char *args;

	args = info->args[0];
	if (args == NULL) {
		dprintf(info->client_fd, "550 Failed to change directory.\r\n");
		return (0);
	}
	if (args[0] != '/')
		args = my_strcat("/", args);
	newpath = my_strcat(getcwd(NULL, PATH_MAX), args);
	newpath = realpath(newpath, NULL);
	if (newpath == NULL) {
		dprintf(info->client_fd, "550 Failed to change directory.\r\n");
		return (0);
	}
	chdir(newpath);
	dprintf(info->client_fd, "250 Directory successfully changed.\r\n");
	return (0);
}

int cmd_cdup(t_info *info)
{
	char *newpath;

	newpath = my_strcat(getcwd(NULL, PATH_MAX), "/..");
	newpath = realpath(newpath, NULL);
	if (newpath == NULL) {
		dprintf(info->client_fd, "550 Failed to change directory.\r\n");
		return (0);
	}
	chdir(newpath);
	dprintf(info->client_fd, "250 Directory successfully changed.\r\n");
	return (0);
}

int cmd_dele(t_info *i)
{
	char *newpath;
	char *args;

	args = i->args[0];
	if (args == NULL) {
		dprintf(i->client_fd, "550 Permission denied.\r\n");
		return (0);
	}
	if (args[0] != '/')
		args = my_strcat("/", args);
	newpath = my_strcat(getcwd(NULL, PATH_MAX), args);
	newpath = realpath(newpath, NULL);
	if (newpath == NULL || remove(newpath) == -1) {
		dprintf(i->client_fd, "550 Permission denied.\r\n");
		return (0);
	}
	dprintf(i->client_fd, "250 Requested file action okay, completed.\r\n");
	return (0);
}
