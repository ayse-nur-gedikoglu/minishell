/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiterror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 05:51:41 by etorun            #+#    #+#             */
/*   Updated: 2025/06/17 20:18:38 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include <stdlib.h>

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


