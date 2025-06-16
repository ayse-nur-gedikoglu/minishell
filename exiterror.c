/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiterror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 05:51:41 by etorun            #+#    #+#             */
/*   Updated: 2025/06/11 06:39:14 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ex_code(int new)
{
	static int	keep;

	if (new != -1)
		keep = new;
	return (keep);
}

void use_err(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		++s;
	}
}

void	e_err(char *s, int fd, int code, char *special)
{
	ex_code(code);
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		++s;
	}
	if (special != NULL)
		write(fd, special, 1);
	else
		write(fd, "newline", 7);
	write(fd, "'\n", 2);
}