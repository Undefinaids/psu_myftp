/*
** EPITECH PROJECT, 2018
** server
** File description:
** server
*/

#include "ftp.h"

int leave;
int fd;
const t_commands com[15] = {
	{"USER", 1, &cmd_user},
	{"PASS", 1, &cmd_pass},
	{"CWD", 1, &cmd_cwd},
	{"CDUP", 0, &cmd_cdup},
	{"QUIT", 0, &cmd_quit},
	{"DELE", 1, &cmd_dele},
	{"PWD", 0, &cmd_printwd},
	{"PASV", 0, &cmd_pasv},
	{"PORT", 1, &cmd_port},
	{"HELP", -1, &cmd_help},
	{"NOOP", 0, &cmd_noop},
	{"RETR", 1, &cmd_retr},
	{"STOR", 1, &cmd_stor},
	{"LIST", -1, &cmd_list},
	{NULL, 0, NULL}
};

int exec_command(char *str, t_info *info)
{
	int rt = 0;

	for (int i = 0; com[i].command != NULL; i++) {
		if (strncmp(str, com[i].command, strlen(com[i].command)) == 0 &&
		(strncmp(str, "USER", 4) == 0 || strncmp(str, "PASS", 4) == 0
		|| strncmp(str, "QUIT", 4) == 0)) {
			rt = (*(com[i].fct))(info);
			return (rt);
		}
		if (info->login == 1 &&
		strncmp(str, com[i].command, strlen(com[i].command)) == 0)
			rt = (*(com[i].fct))(info);
		if (info->login == 0 &&
		strncmp(str, com[i].command, strlen(com[i].command)) == 0)
			dprintf(info->client_fd,
				"530 Please login with USER and PASS.\r\n");
		if (rt == -1)
			return (-1);
	}
	return (0);
}

int handle_client(t_info info)
{
	FILE *stream = fdopen(info.client_fd, "r");
	ssize_t nread;
	size_t len = 0;
	char *line = NULL;

	write(info.client_fd, "220 Service ready for new user.\r\n", 33);
	while (leave == 0 && (nread = getline(&line, &len, stream)) != -1) {
		line = check_line(line);
		is_command_ok(line, &info);
		printf("Retrieved line of length %zu:\n", nread);
		write(1, line, nread);
		printf("\n");
		info.args = get_args(line);
		if (exec_command(line, &info) == -1)
			return (-1);
	}
	return (0);
}

int param_socket(int fd, int port)
{
	struct sockaddr_in s_in;
	int opt = 1;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
		return (-1);
	if (listen(fd, 42) == -1)
		return (-1);
	return (0);
}

int get_socket_ftp(int port)
{
	struct protoent *pe;
	int fd;

	pe = getprotobyname("TCP");
	if (!pe)
		return (-1);
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (param_socket(fd, port) == -1) {
		close(fd);
		return (-1);
	}
	return (fd);
}

void server(int port, __attribute__((unused)) char *rootpath)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size;
	t_info info;

	fd = get_socket_ftp(port);
	s_in_size = sizeof(s_in_client);
	if (fd == -1) {
		printf("Port already opened\n");
		return;
	}
	fill_struct(&info);
	while (leave == 0) {
		info.client_fd = accept(fd, (struct sockaddr *)&s_in_client
					, &s_in_size);
		if (inside_loop_serv(info, s_in_client) == -1)
			break;
	}
	close(info.client_fd);
	close(fd);
}
