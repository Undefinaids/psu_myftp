/*
** EPITECH PROJECT, 2018
** retr
** File description:
** retr
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ftp.h"

static char *get_file_content(char *name, struct stat *sb)
{
	int fd = open(name, O_RDONLY);
	char *file = NULL;

	if (fd == -1 || fstat(fd, sb) == -1)
		return (NULL);
	file = calloc(sb->st_size + 1, sizeof(char));
	if (file == NULL)
		return (NULL);
	if (read(fd, file, sb->st_size) == 0)
		return (NULL);
	return (file);
}

static int retr_pssf(t_info *info, char *file, int size)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size;
	int client_fd;

	s_in_size = sizeof(s_in_client);
	client_fd = accept(info->data_fd,
			(struct sockaddr *)&s_in_client, &s_in_size);
	dprintf(info->client_fd,
		"150 Opening ASCII mode data connexion for %s (%d bytes).\r\n",
		info->args[0], size);
	if (client_fd == -1)
		return (0);
	dprintf(client_fd, "%s", file);
	dprintf(info->client_fd, "226 Transfer complete.\r\n");
	close(client_fd);
	close(info->data_fd);
	info->mode = 0;
	return (0);
}

static int retr_actf(t_info *info, char *file, int size)
{
	dprintf(info->client_fd,
		"150 Opening ASCII mode data connexion for %s (%d bytes).\r\n",
		info->args[0], size);
	dprintf(info->data_fd, "%s", file);
	dprintf(info->client_fd, "226 Transfer complete.\r\n");
	close(info->data_fd);
	info->mode = 0;
	return (0);
}

int cmd_retr(t_info *info)
{
	struct stat sb;
	char *file;

	if (info->mode == 0) {
		dprintf(info->client_fd, "425 Use PORT or PASV first\r\n");
		return (0);
	}
	file = get_file_content(info->args[0], &sb);
	if (file == NULL)
		dprintf(info->client_fd, "550 Failed to open file.\r\n");
	if (info->mode == 1)
		return (retr_pssf(info, file, sb.st_size));
	if (info->mode == 2)
		return (retr_actf(info, file, sb.st_size));
	return (0);
}
