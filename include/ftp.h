/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** ftp
*/

#ifndef FTP_H_
#define FTP_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>

typedef struct	s_info
{
	char	*username;
	char	*password;
	char	*currentpath;
	char	*initialpath;
	int	login;
	int	mode;
	char	*client_ip;
	int	port;
	int	client_fd;
	char	**args;
	int	data_fd;
}		t_info;

typedef struct	s_commands
{
	char	*command;
	char	ac;
	int	(*fct)(t_info *info);
}		t_commands;

int notimplemented(t_info *info);
int print_wd(t_info *info);
int cmd_quit(t_info *info);
int cmd_user(t_info *info);
int cmd_printwd(t_info *info);
void server(int port, char *rootpath);
void fill_struct(t_info *info);
char **get_args(char *str);
int set_sig_handlers(void);
int cmd_pass(t_info *info);
int cmd_noop(t_info *info);
int cmd_help(t_info *info);
int cmd_cwd(t_info *info);
int cmd_cdup(t_info *info);
int cmd_pasv(t_info *info);
int cmd_dele(t_info *info);
int cmd_list(t_info *info);
int cmd_port(t_info *info);
int cmd_retr(t_info *info);
int cmd_stor(t_info *info);
char *check_line(char *str);
void is_command_ok(char *str, t_info *i);
char *my_strcat(char *s, char *s2);
int inside_loop_serv(t_info i, struct sockaddr_in s);
int handle_client(t_info info);
int is_a_slash(char *str);

extern int fd;
extern int leave;
extern const t_commands com[15];
#endif /* FTP_H_ */
