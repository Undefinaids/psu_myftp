/*
** EPITECH PROJECT, 2018
** list
** File description:
** list
*/

#include "ftp.h"

char *get_cmd_list(t_info *info, int client_fd)
{
	char *msg = my_strcat("", "ls --time-style=+%b\\ %m\\ %Y -l ");
	char *fd = calloc(sizeof(char), 20);

	if (info->args[0] != NULL)
		msg = my_strcat(msg, info->args[0]);
	msg = my_strcat(msg, "|tail -n+2>&");
	sprintf(fd, "%d", client_fd);
	msg = my_strcat(msg, fd);
	return (msg);
}

static int list_passf(t_info *info)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size;
	int client_fd;

	s_in_size = sizeof(s_in_client);
	client_fd = accept(info->data_fd,
			(struct sockaddr *)&s_in_client, &s_in_size);
	dprintf(info->client_fd, "150 Here comes the directory listing.\r\n");
	if (client_fd == -1)
		return (0);
	system(get_cmd_list(info, client_fd));
	dprintf(info->client_fd, "226 Directory send OK.\r\n");
	close(client_fd);
	close(info->data_fd);
	info->mode = 0;
	return (0);
}

static int list_actf(t_info *info)
{
	dprintf(info->client_fd, "150 Here comes the directory listing.\r\n");
	system(get_cmd_list(info, info->data_fd));
	dprintf(info->client_fd, "226 Directory send OK.\r\n");
	close(info->data_fd);
	info->mode = 0;
	return (0);
}

int cmd_list(t_info *info)
{
	if (info->mode == 0) {
		dprintf(info->client_fd, "425 Use PORT or PASV first\r\n");
		return (0);
	}
	if (info->mode == 1)
		return (list_passf(info));
	if (info->mode == 2)
		return (list_actf(info));
	return (0);
}
