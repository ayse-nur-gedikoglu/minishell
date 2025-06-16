/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:00:54 by etorun            #+#    #+#             */
/*   Updated: 2025/06/11 06:40:19 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>

void	freeall(t_dt *dt)
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
		rl_clear_history();
		write(1, "exit\n", 6);
		exit (0);
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

void	printer(t_token *token)
{
	while (token)
	{
		printf("TYPE= %d token=%s|*|\n", token->type, token->con);
		printf("*******************************\n");
		token = token->next;
	}
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
		if (cntlline(&dt, dt.line))
		{
			work_again(&dt);
			continue ;
		}
		dt.sta = dt.line;
		parser(&dt, dt.sta);
		printer(*(dt.head));
		//execute(&dt,*(dt.head), envp);
		freeall(&dt);
	}
	rl_clear_history();
	return (0);
}
