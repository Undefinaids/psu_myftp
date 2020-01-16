/*
** EPITECH PROJECT, 2018
** passif
** File description:
** passif
*/

#include "ftp.h"

static struct protoent *get_pe(void)
{
	struct protoent *pe;

	pe = getprotobyname("TCP");
	return (pe);
}

static struct sockaddr_in get_sin(void)
{
	struct sockaddr_in s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = 0;
	s_in.sin_addr.s_addr = INADDR_ANY;
	return (s_in);
}

int cmd_pasv(t_info *info)
{
	struct sockaddr_in s_in = get_sin();
	struct sockaddr_in res;
	unsigned int len = sizeof(struct sockaddr);

	info->mode = 1;
	info->data_fd = socket(AF_INET, SOCK_STREAM, (get_pe())->p_proto);
	if (bind(info->data_fd,
		(const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		close(info->data_fd);
		return (0);
	}
	if (listen(info->data_fd, 42) == -1)
		return (0);
	getsockname(info->data_fd, (struct sockaddr *)&res, &len);
	dprintf(info->client_fd,
		"227 Entering Passive Mode (127,0,0,1,%d,%d)\r\n",
		ntohs(res.sin_port) >> 8, ntohs(res.sin_port) & 0xFF);
	return (0);
}
