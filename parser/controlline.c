/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cntlline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:02:30 by etorun            #+#    #+#             */
/*   Updated: 2025/05/25 23:38:12 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	greatcntl(char *c)
{
	if(*c == '>')
		c++;
	while (*c)
	{
		if (*c == ' ')
		{
			c++;
			continue;
		}
		else if (*c == '|' || *c == '>' || *c == '<')
		{
			e_err("bash: syntax error near unexpected token `", 2, 2, c);
			return (1);
		}
		else
			return (0);
	}
	e_err("bash: syntax error near unexpected token `", 2, 2, NULL);
	return (1);
}

int	lowercntl(char *c)
{
	if(*c == '<')
		c++;
	while (*c)
	{
		if (*c == ' ')
		{
			c++;
			continue;
		}
		else if (*c == '|' || *c == '>' || *c == '<')
		{
			e_err("bash: syntax error near unexpected token `", 2, 2, c);
			return (1);
		}
		else
			return (0);
	}
	e_err("bash: syntax error near unexpected token `", 2, 2, NULL);
	return (1);
}

int	quote_cntl(t_dt *dt, char *raw)
{
	while (*(raw))
	{
		if (*raw == '"' && dt->sq == 0 && dt->dq == 0)
			dt->dq = 1;
		else if (*raw == '"' && dt->sq == 0 && dt->dq == 1)
			dt->dq = 0;
		else if (*raw == '\'' && dt->sq == 0 && dt->dq == 0)
			dt->sq = 1;
		else if (*raw == '\'' && dt->sq == 1 && dt->dq == 0)
			dt->sq = 0;
		raw++;
	}
	if (!(dt->sq == 0 && dt->dq == 0))
	{
		ex_code(2);
		write(1, "Quote Error\n", 12);
		reset_q(dt);
		return (1);
	}
	reset_q(dt);
	return (0);
}

int	cntlline(t_dt *dt, char *c)
{
	if (*dt->line == '\0')
		return (1);
	tab_replacer(dt);
	if (quote_cntl(dt, dt->line) || first_pipe(dt->line) )
		return (1);
	while (*c)
	{
		def_q(c, dt);
		if (*c == '|' && dt->sq == 0 && dt->dq == 0)
			if (pipecntl(c + 1))
				return (1);
		if (*c == '>' && dt->sq == 0 && dt->dq == 0)
			if (greatcntl(c + 1))
				return (1);
		if (*c == '<' && dt->sq == 0 && dt->dq == 0)
			if (lowercntl(c + 1))
				return (1);
		c++;
	}
	return (0);
}
