#include "../minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>

static void do_heredoc(t_token *tok)
{
	int fd[2];
	char *line;

	pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, tok->next->con, ft_strlen(tok->next->con) + 1))
			break;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

static void do_input(t_token *tok)
{
	int fd;

	fd = open(tok->next->con, O_RDONLY);
	if (fd < 0)
		e_ex(": No such file or directory\n", tok->next->con);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void do_output(t_token *tok, int append)
{
	int fd;
	int flags;

	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	fd = open(tok->next->con, flags, 0644);
	if (fd < 0)
		e_ex(": Cannot open file\n", tok->next->con);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void handle_redir(t_token *tok)
{
	while (tok)
	{
		if (tok->type == INPUT)
			do_input(tok);
		else if (tok->type == OUTPUT)
			do_output(tok, 0);
		else if (tok->type == APPEND)
			do_output(tok, 1);
		else if (tok->type == HEREDOC)
			do_heredoc(tok);
		tok = tok->next;
	}
}
