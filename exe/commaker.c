/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commaker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:08:31 by etorun            #+#    #+#             */
/*   Updated: 2025/06/17 20:14:21 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

void	free_command(t_dt *dt)
{
	free(dt->c_arr);
	free(dt->p_command);
	dt->c_arr = NULL;
	dt->p_command = NULL;
}

t_token	*counttoken(int *counts, t_token *tok)
{
	counts[0] = 0;
	counts[1] = 0;
	while (tok)
	{
		if (tok->type == 3)
			return (tok);
		else if (tok->type == 1)
			counts[0]++;
		else if (tok->type > 3)
		{
			counts[1]++;
			tok = tok->next->next;
			continue ;
		}
		tok = tok->next;
	}
	return (tok);
}

t_token	*c_maker(t_dt *dt, int x, int start, t_token *tok)
{
	dt->c_arr = malloc(sizeof(char *) * (x + 1));
	if (!dt->c_arr)
		return (NULL);
	dt->c_arr[x] = NULL;
	while (tok)
	{
		if (tok->type == 3)
			return (tok->next);
		else if (tok->type == 1)
			dt->c_arr[start++] = tok->con;
		else if (tok->type > 3)
		{
			tok = tok->next->next;
			continue ;
		}
		tok = tok->next;
	}
	return (tok);
}
