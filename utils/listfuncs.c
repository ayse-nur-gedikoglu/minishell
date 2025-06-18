/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:52:57 by etorun            #+#    #+#             */
/*   Updated: 2025/06/17 20:09:59 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	token_add(t_dt *dt, t_token *new)
{
	t_token	*temp;

	if (new == NULL)
		return ;
	if (!dt->head)
	{
		dt->head = malloc(sizeof(t_token *));
		*dt->head = new;
		return ;
	}
	temp = *dt->head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}

t_token	*ntok(int type, void *con)
{
	t_token	*new;
	char	*ch;

	ch = (char *)con;
	if (con && (*ch == '\0' || (*ch == ' ' && *(ch + 1) == '\0')))
	{
		free(ch);
		return (NULL);
	}
	new = (t_token *) malloc (sizeof(t_token));
	if (!new)
		return (NULL);
	if (type < 3)
		new->con = ch;
	else
		new->con = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}

