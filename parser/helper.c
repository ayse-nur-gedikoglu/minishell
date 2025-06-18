/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:47:44 by etorun            #+#    #+#             */
/*   Updated: 2025/06/16 06:15:34 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

void	reset_q(t_dt *dt)
{
	dt->dq = 0;
	dt->sq = 0;
	dt->w = 0;
	dt->flag = 0;
}

void	def_q(char *cur, t_dt *dt)
{
	if (*cur == '"' && dt->sq == 0 && dt->dq == 0)
		dt->dq = 1;
	else if (*cur == '"' && dt->sq == 0 && dt->dq == 1)
		dt->dq = 0;
	else if (*cur == '\'' && dt->sq == 0 && dt->dq == 0)
		dt->sq = 1;
	else if (*cur == '\'' && dt->sq == 1 && dt->dq == 0)
		dt->sq = 0;
}

void	tab_replacer(t_dt *dt)
{
	char	*raw;

	raw = dt->line;
	while (*raw)
	{
		if (*raw == '\t')
			*raw = ' ';
		raw++;
	}
	reset_q(dt);
}

void	work_again(t_dt *dt)
{
	free(dt->line);
	dt->sq = 0;
	dt->dq = 0;
	dt->w = 0;
	dt->flag = 0;
}

void	dt_init(t_dt *dt, char **argv, char **envp)
{
	ex_code(0);
	dt->argv = argv;
	dt->envp = envp;
	dt->sq = 0;
	dt->dq = 0;
	dt->w = 0;
	dt->flag = 0;
	dt->e_val = NULL;
	dt->line = NULL;
	dt->head = NULL;
	dt->c_arr = NULL;
	dt->p_command = NULL;
	dt->pf = 0;
}
