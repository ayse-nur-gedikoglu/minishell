.SILENT:

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = minishell.c exiterror.c \
	parser/parser.c parser/controlline.c parser/helper.c parser/parserhelper.c \
	parser/pipecontrol.c \
	utils/liblike.c utils/listfuncs.c utils/libexec.c utils/libitoa.c utils/libsmalls.c utils/libjoins.c \
	buildin/cd.c buildin/echo.c buildin/env.c buildin/exit.c buildin/export.c buildin/pwd.c buildin/unset.c \
	exe/exe.c exe/pather.c exe/commaker.c exe/exe_redir.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re