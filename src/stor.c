/*
** EPITECH PROJECT, 2018
** stor
** File description:
** stor
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ftp.h"

static char *get_file_name(char *str)
{
	char *name = strdup(str);

	while (is_a_slash(name) == 1) {
		name++;
	}
	return (name);
}

static int write_content(int fd, char *name)
{
	char *file = NULL;
	struct stat sb;
	FILE *nf;

	if (fd == -1 || fstat(fd, &sb) == -1)
		return (-1);
	file = calloc(sb.st_size + 1, sizeof(char));
	if (file == NULL)
		return (-1);
	read(fd, file, sb.st_size);
	nf = fopen(name, "w+");
	fprintf(nf, "%s", file);
	fclose(nf);
	return (0);
}

static int stor_pssf(t_info *info)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size;
	int client_fd;

	s_in_size = sizeof(s_in_client);
	client_fd = accept(info->data_fd,
			(struct sockaddr *)&s_in_client, &s_in_size);
	dprintf(info->client_fd,
		"150 Opening ASCII mode.\r\n");
	if (client_fd == -1)
		return (0);
	write_content(client_fd, get_file_name(info->args[0]));
	dprintf(info->client_fd, "226 Transfer complete.\r\n");
	close(client_fd);
	close(info->data_fd);
	info->mode = 0;
	return (0);
}

static int stor_actf(t_info *info)
{
	dprintf(info->client_fd,
		"150 Opening ASCII mode.\r\n");
	write_content(info->data_fd, get_file_name(info->args[0]));
	dprintf(info->client_fd, "226 Transfer complete.\r\n");
	close(info->data_fd);
	info->mode = 0;
	return (0);
}

int cmd_stor(t_info *info)
{
	if (info->args[0] == NULL) {
		dprintf(info->client_fd, "550 Permission denied.\r\n");
		return (0);
	}
	if (info->mode == 0) {
		dprintf(info->client_fd, "425 Use PORT or PASV first\r\n");
		return (0);
	}
	if (info->mode == 1)
		return (stor_pssf(info));
	if (info->mode == 2)
		return (stor_actf(info));
	return (0);
}
