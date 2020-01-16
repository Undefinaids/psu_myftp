/*
** EPITECH PROJECT, 2018
** actif
** File description:
** actif
*/

#include "ftp.h"

static char *get_ip_str(char *str)
{
	char *ip = strdup(str);
	int n = 0;

	for (int i = 0; ip[i] != '\0'; i++) {
		if (ip[i] == '.') {
			n++;
		}
		if (n == 4) {
			ip[i] = '\0';
			return (ip);
		}
	}
	return (ip);
}

static int get_port_actif(char *str)
{
	int n = 0;
	int byte = 0;

	while (n != 4) {
		if (str[0] == '.')
			n++;
		str++;
	}
	byte = atoi(str) * 256;
	while (*str != '.')
		str++;
	str++;
	byte += atoi(str);
	return (byte);
}

static char *valid_args(char *str)
{
	int n = 0;

	if (str == NULL)
		return (NULL);
	for (int i = 0; str[i] != '\0'; i++) {
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',')
			return (NULL);
		if (str[i] == ',' && str[i + 1] != '\0') {
			str[i] = '.';
			n++;
		}
	}
	if (n != 5)
		return (NULL);
	return (str);
}

int cmd_port(t_info *info)
{
	struct sockaddr_in server;

	if (info->args[0] == NULL || valid_args(info->args[0]) == NULL) {
		dprintf(info->client_fd, "500 Illegal PORT command.\r\n");
		return (0);
	}
	info->data_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (info->data_fd == -1)
		return (0);
	server.sin_addr.s_addr = inet_addr(get_ip_str(info->args[0]));
	server.sin_family = AF_INET;
	server.sin_port = htons(get_port_actif(info->args[0]));
	if (connect(info->data_fd, (struct sockaddr *)&server, sizeof(server)))
		return (0);
	info->mode = 2;
	return (0);
}
