/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikog <gedikoglu_27@icloud.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:03:02 by etorun            #+#    #+#             */
/*   Updated: 2025/06/20 10:56:05 by agedikog         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"
#include <sys/wait.h>

t_token	*c_executer(t_dt *dt, t_token *start)
{
	int				counts[2];
	static t_token	*keeper;

	if (!keeper)
		keeper = start;
	counttoken(counts, keeper);
	keeper = c_maker(dt, counts[0], 0, keeper);
	return (keeper);
}

void	forker(t_dt *dt, int type, t_token *status, int *fd)
{
	int	pid;
	int	e_code;

	pid = fork();
	if (pid == 0)
	{
		if (status)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		if (type == 1)
			execve(dt->p_command, dt->c_arr, dt->envp);
		execve(dt->c_arr[0], dt->c_arr, dt->envp);
	}
	wait(&e_code);
	ex_code(e_code % 255);
}

int	check_buildin(t_dt *dt, char *s)
{
	int	ret_val;

	ret_val = 1;
	if (!ft_strncmp(s, "echo", 5) && dt->pf == 0)
		ret_val = ft_echo(dt, 0, 1);
	else if (!ft_strncmp(s, "cd", 3) && dt->pf == 0)
		ret_val = ft_cd(dt, dt->c_arr, 0, NULL);
	else if (!ft_strncmp(s, "pwd", 4) && dt->pf == 0)
		ret_val = ft_pwd();
	else if (!ft_strncmp(s, "export", 7) && dt->pf == 0)
		ft_export(dt);
	else if (!ft_strncmp(s, "unset", 6) && dt->pf == 0)
		ft_unset(dt);
	else if (!ft_strncmp(s, "env", 4) && dt->pf == 0)
		ft_env(dt);
	else if (!ft_strncmp(s, "exit", 5) && dt->pf == 0)
		ft_exit(dt);
	if (!ret_val)
		free_command(dt);
	return (ret_val);
}

int	exe(t_dt *dt, t_token *cur)
{
	t_token	*status;
	int		fd[2];

	dt->std_in = dup(STDIN_FILENO);
	dt->std_out = dup(STDOUT_FILENO);
	while (1)
	{
		status = c_executer(dt, cur);
		if (!check_buildin(dt, dt->c_arr[0]))
			break ;
		if (status)
			pipe(fd);
		if (ft_strchr(dt->c_arr[0], '/'))
			forker(dt, 0, status, fd);
		else if (c_exist(dt, dt->c_arr[0], dt->envp))
			forker(dt, 1, status, fd);
		else
			e_ex(": command not found\n", dt->c_arr[0]);
		free_command(dt);
		if (!status)
			break ;
	}
	dup2(dt->std_in, STDIN_FILENO);
	return (0);
}
