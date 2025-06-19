#include "../minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>

t_token *c_executer(t_dt *dt, t_token *start)
{
	int counts[2];
	static t_token *keeper;

	if (!keeper)
		keeper = start;
	counttoken(counts, keeper);
	keeper = c_maker(dt, counts[0], 0, keeper);
	return (keeper);
}

int check_buildin(t_dt *dt, char *s)
{
	if (!ft_strncmp(s, "echo", 5))
		return (ft_echo(dt, 0, 1) == 0);
	if (!ft_strncmp(s, "pwd", 4))
		return (ft_pwd() == 0);
	if (!ft_strncmp(s, "export", 7))
	{
		ft_export(dt);
		return 0;
	}
	if (!ft_strncmp(s, "unset", 6))
	{
		ft_unset(dt);
		return 0;
	}
	if (!ft_strncmp(s, "env", 4))
		return (ft_env(dt) == 0);
	if (!ft_strncmp(s, "exit", 5))
	{
		ft_exit(dt);
		return 0;
	}
	return 1;
}

static void do_exec(t_dt *dt)
{
	if (ft_strchr(dt->c_arr[0], '/'))
		execve(dt->c_arr[0], dt->c_arr, dt->envp);
	else if ((dt->p_command = c_exist(dt, dt->c_arr[0], dt->envp)))
		execve(dt->p_command, dt->c_arr, dt->envp);
	else
		e_ex(": command not found\n", dt->c_arr[0]);
	exit(127);
}

static int child_proc(t_dt *dt, int *fd, int in_fd, t_token *status)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (status)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (dt->head)
		handle_redir(*dt->head);
	if (check_buildin(dt, dt->c_arr[0]) == 0)
		exit(0);
	do_exec(dt);
	return (0);
}

int exe(t_dt *dt, t_token *cur)
{
	int fd[2];
	int in_fd;
	int status;
	pid_t pid;
	t_token *status_tok;
	int orig_in;

	orig_in = dup(STDIN_FILENO);
	in_fd = dup(STDIN_FILENO);
	while (cur)
	{
		status_tok = c_executer(dt, cur);
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child_proc(dt, fd, in_fd, status_tok);
		close(fd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		in_fd = fd[0];
		while (cur && cur->type != PIPE)
			cur = cur->next;
		if (cur)
			cur = cur->next;
	}
	while (wait(&status) > 0)
		ex_code(WEXITSTATUS(status));
	dup2(orig_in, STDIN_FILENO);
	close(orig_in);
	return (0);
}
