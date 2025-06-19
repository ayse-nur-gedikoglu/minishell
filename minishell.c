/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:00:54 by etorun            #+#    #+#             */
/*   Updated: 2025/06/19 17:54:51 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>

void	free_all(t_dt *dt)
{
	t_token	*sta;
	t_token	*temp;

	sta = *(dt->head);
	while (sta)
	{
		temp = sta->next;
		free(sta->con);
		free(sta);
		sta = temp;
	}
	free(dt->head);
	dt->head = NULL;
	free(dt->line);
	reset_q(dt);
	dt->pf = 0;
}

void	sigc(int x)
{
	(void)x;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	eof_addhist(char *start, char *cntl, t_dt *dt)
{
	if (cntl == NULL)
	{
		free(cntl);
		freeandleave(dt);
		write(1, "exit\n", 6);
		exit (ex_code(-1));
	}
	while (*cntl)
	{
		if (*cntl != ' ' && *cntl != '\t')
			dt->flag = 1;
		cntl++;
	}
	if (ft_strlen(start) && dt->flag == 1)
		add_history(start);
	if (dt-> flag == 0)
	{
		work_again(dt);
		return (1);
	}
	reset_q(dt);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_dt	dt;

	if (1 != argc)
	{
		use_err("Usage: ./minishell\n", 2);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigc);
	dt_init(&dt, argv, envp);
	while (1)
	{
		dt.line = readline("\033[0;35m(ElShellito) \033[0m");
		if (eof_addhist(dt.line, dt.line, &dt))
			continue ;
		if (parser(&dt, dt.line))
			continue ;
		env_check(&dt);
		exe(&dt,*(dt.head));
		free_all(&dt);
	}
	freeandleave(&dt);
	return (0);
}
