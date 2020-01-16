/*
** EPITECH PROJECT, 2018
** serv
** File description:
** serv
*/

#include "ftp.h"

int inside_loop_serv(t_info info, struct sockaddr_in s)
{
	pid_t child;

	if (info.client_fd == -1)
		return (-1);
	child = fork();
	if (child == 0) {
		info.client_ip = inet_ntoa(s.sin_addr);
		if (handle_client(info) == -1) {
			close(info.client_fd);
			close(fd);
			return (-1);
		}
	}
	close(info.client_fd);
	return (0);
}
