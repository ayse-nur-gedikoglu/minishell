/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiterror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 05:51:41 by etorun            #+#    #+#             */
/*   Updated: 2025/06/19 19:12:12 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>

int	ex_code(int new)
{
	static int	keep;

	if (new != -1)
		keep = new;
	return (keep);
}

void	use_err(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	e_err(char *s, int fd, int code, char *special)
{
	ex_code(code);
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	if (special != NULL)
		write(fd, special, 1);
	else
		write(fd, "newline", 7);
	write(fd, "'\n", 2);
}

void	e_ex(char *s, char *special)
{
	ex_code(127);
	while (*special)
	{
		write(2, special, 1);
		special++;
	}
	while (*s)
	{
		write(2, s, 1);
		s++;
	}
}

void	freeandleave(t_dt *dt)
{
	rl_clear_history();
	free(dt->oldpwd);
	free(dt->home);
}
