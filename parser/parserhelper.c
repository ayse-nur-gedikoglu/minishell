/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserhelper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:53:04 by etorun            #+#    #+#             */
/*   Updated: 2025/06/19 19:10:25 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

char	*triple_adder(t_token *tok, size_t l_eval, size_t dol, t_dt *dt)
{
	char	*new;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(tok->con) + l_eval - ft_strlen(dt->var) + 1;
	new = ft_calloc(len, sizeof(char));
	if (!new)
		return (NULL);
	new[len - 1] = '\0';
	while (i < dol)
	{
		new[i] = (tok->con)[i];
		i++;
	}
	while (dt->flag < l_eval)
		new[i++] = dt->e_val[dt->flag++];
	dt->dol = &new[i];
	while (*(dt->finish))
		new[i++] = *dt->finish++;
	free(tok->con);
	tok->con = new;
	return (dt->dol);
}

char	*concat(t_token *tok, char *counter, t_dt *dt, int i)
{
	size_t	l_eval;
	char	*new;
	size_t	new_len;

	new = NULL;
	dt->e_val = getenv(dt->var);
	if (dt->e_val)
	{
		l_eval = ft_strlen(dt->e_val);
		return (triple_adder(tok, l_eval, dt->dol - tok->con, dt));
	}
	new_len = ft_strlen(tok->con) - ft_strlen(dt->var);
	new = malloc(sizeof(char) * new_len);
	if (!new)
		return (NULL);
	new[new_len - 1] = '\0';
	while (counter != dt->dol)
		new[i++] = *counter++;
	dt->dol = &new[i];
	while (*dt->finish)
		new[i++] = *dt->finish++;
	free(tok->con);
	tok->con = new;
	return (dt->dol);
}

char	*ex_code_add(char *whole, char *raw, char *sta, t_dt *dt)
{
	char	*dolar;
	char	*new;
	char	*it;

	while (*raw)
	{
		def_q(raw, dt);
		if ('$' == *raw && '?' == *(raw + 1) && 1 != dt->sq)
		{
			dolar = raw;
			*dolar = '\0';
			it = ft_itoa(ex_code(-1));
			new = ft_strjoin(sta, it);
			free(it);
			whole = ft_strjoin(new, dolar + 2);
			free(new);
			raw = whole;
			free(sta);
			sta = whole;
			reset_q(dt);
			continue ;
		}
		raw++;
	}
	return (whole);
}

char	*q_remover(char *sta, char *cur, char *new, t_dt *dt)
{
	char	*keep;

	reset_q(dt);
	new = ft_calloc(ft_strlen(sta) + 1, sizeof(char));
	if (!new)
		return (NULL);
	keep = new;
	while (*cur)
	{
		def_q(cur, dt);
		if (*cur == '"' && dt->sq == 0)
			cur++;
		else if (*cur == '\'' && dt->dq == 0)
			cur++;
		else
			*new++ = *cur++;
	}
	*new = '\0';
	free(sta);
	sta = ft_strdup(keep);
	free(keep);
	reset_q(dt);
	return (sta);
}
