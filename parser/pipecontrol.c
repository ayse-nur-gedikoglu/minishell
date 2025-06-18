/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:52:39 by etorun            #+#    #+#             */
/*   Updated: 2025/06/17 20:17:43 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_pipe(char *c)
{
	while (*c)
	{
		if (*c == ' ')
		{
			c++;
			continue ;
		}
		else if (*c == '|')
		{
			e_err("bash: syntax error near unexpected token `", 2, 2, c);
			return (1);
		}
		else
			break ;
	}
	return (0);
}

int	pipecntl(char *c)
{
	while (*c)
	{
		if (*c == ' ')
		{
			c++;
			continue ;
		}
		else if (*c == '|')
		{
			e_err("bash: syntax error near unexpected token `", 2, 2, c);
			return (1);
		}
		else if (*c == '>' || *c == '<')
		{
			e_err("bash: syntax error near unexpected token `", 2, 2, NULL);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}
