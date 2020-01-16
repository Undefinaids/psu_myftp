/*
** EPITECH PROJECT, 2018
** fill_struct
** File description:
** fill_struct
*/

#include "ftp.h"

void fill_struct(t_info *info)
{
	char *inipath = calloc(PATH_MAX, sizeof(char));
	char *curpath = calloc(PATH_MAX, sizeof(char));

	inipath = getcwd(inipath, PATH_MAX);
	curpath = getcwd(curpath, PATH_MAX);
	info->username = NULL;
	info->password = NULL;
	info->currentpath = curpath;
	info->initialpath = inipath;
	info->login = 0;
	info->mode = 0;
	info->client_ip = NULL;
	info->port = 0;
	info->data_fd = -1;
}

char *check_line(char *str)
{
	char *tmp = strdup(str);

	if (tmp[strlen(tmp) - 1] == '\n')
		tmp[strlen(tmp) - 1] = '\0';
	if (tmp[strlen(tmp) - 1] == '\r')
		tmp[strlen(tmp) - 1] = '\0';
	return (tmp);
}

char **get_args(char *str)
{
	char **res;
	int i = 0;
	char *s;

	res = malloc(sizeof(char *) * 1);
	if (res == NULL)
		return (NULL);
	strtok(str, " ");
	while ((s = strtok(NULL, " "))) {
		res = realloc(res, sizeof(char *) * (i + 2));
		res[i] = strdup(s);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	is_command_ok(char *str, t_info *info)
{
	for (int i = 0; com[i].command != NULL; i++) {
		if (strncmp(str, com[i].command, strlen(com[i].command)) == 0)
			return;
	}
	if (info->login == 1 && strlen(str) > 0)
		dprintf(info->client_fd, "500 Unknown command.\r\n");
	else if (strlen(str) > 0)
		dprintf(info->client_fd,
			"530 Please login with USER and PASS.\r\n");
	return;
}

int is_a_slash(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '/')
			return (1);
	}
	return (0);
}
