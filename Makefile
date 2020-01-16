##
## EPITECH PROJECT, 2018
## make
## File description:
## make
##

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wextra -Wall -Werror -I $(INC)

LDFLAGS	=

INC	=	include

NAME	=	server

OBJS	=	$(SRCS:.c=.o)

SRCS	=	src/main.c \
		src/commands.c \
		src/commands2.c \
		src/server.c \
		src/server2.c \
		src/signals.c \
		src/passif.c \
		src/actif.c \
		src/cwd.c \
		src/list.c \
		src/retr.c \
		src/stor.c \
		src/fill_struct.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
