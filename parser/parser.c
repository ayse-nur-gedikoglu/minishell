/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:27:50 by etorun            #+#    #+#             */
/*   Updated: 2025/06/09 08:26:59 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	tok_op(t_dt *dt, char **cur, int type)
{
	if (3 == type)
		token_add(dt, ntok(PIPE, NULL));
	if (4 == type)
		token_add(dt, ntok(INPUT, NULL));
	if (5 == type)
		token_add(dt, ntok(OUTPUT, NULL));
	if (6 == type)
		token_add(dt, ntok(APPEND, NULL));
	if (7 == type)
		token_add(dt, ntok(HEREDOC, NULL));
	if (type > 5)
		*cur = *cur + 1;
}

void	tok_space(char **ch, t_dt *dt)
{
	dt->sta = *ch;
	while (1)
	{
		while (**ch == ' ' && dt->sq == 0 && dt->dq == 0 && dt->w == 0)
		{
			(*ch)++;
			dt->sta = *ch;
		}
		dt->w = 1;
		def_q(*ch, dt);
		if ((**ch == '|' || **ch == '<' || **ch == '>'
				|| **ch == '\0') && (dt->sq == 0 && dt->dq == 0))
		{
			token_add(dt, ntok(FIRST, ft_substr(dt->sta, 0, *ch - dt->sta)));
			dt->w = 0;
			return ;
		}
		if (**ch == ' ' && dt->w && dt->sq == 0 && dt->dq == 0)
		{
			token_add(dt, ntok(FIRST, ft_substr(dt->sta, 0, *ch - dt->sta)));
			dt->w = 0;
			dt->sta = *ch + 1;
		}
		(*ch)++;
	}
}

void	env_add(t_token *tok, char *c, t_dt *dt)
{
	while (*c)
	{
		def_q(c, dt);
		if (*c == '$' && *(c + 1) != '?' && *(c + 1) != '$' && *(c + 1) != '\0'
			&& *(c + 1) != ' ' && *(c + 1) != '"'
			&& ((1 == dt->dq && 0 == dt->sq) || (0 == dt->dq && 0 == dt->sq)))
		{
			dt->dol = c++;
			if (ft_isdigit(*c))
				c++;
			else
				while ((ft_isalnum(*c) || *c == '_') && *c != '\0')
					c++;
			dt->finish = c;
			dt->var = ft_substr(dt->dol + 1, 0, dt->finish - dt->dol -1);
			if (dt->var)
			{
				c = concat(tok, tok->con, dt, 0);
				dt->flag = 0;
				free(dt->var);
				continue ;
			}
		}
		c++;
	}
}

void	env_check(t_dt *dt)
{
	t_token	*tok;

	reset_q(dt);
	if (!dt->head)
		return ;
	tok = *dt->head;
	while (tok)
	{
		if (1 == tok->type)
		{
			env_add(tok, tok->con, dt);
			tok->con = ex_code_add(tok->con, tok->con, tok->con, dt);
			tok->con = q_remover(tok->con, tok->con, NULL, dt);
		}
		tok = tok->next;
	}
}

void	parser(t_dt *dt, char *cur)
{
	while (1)
	{
		tok_space(&cur, dt);
		if (*cur == '|' && dt->sq == 0 && dt->dq == 0)
			tok_op(dt, &cur, 3);
		if (*cur == '<' && *(cur + 1) != '<' && dt->sq == 0 && dt->dq == 0)
			tok_op(dt, &cur, 4);
		if (*cur == '>' && *(cur + 1) != '>' && dt->sq == 0 && dt->dq == 0)
			tok_op(dt, &cur, 5);
		if (*cur == '>' && *(cur + 1) == '>' && dt->sq == 0 && dt->dq == 0)
			tok_op(dt, &cur, 6);
		if (*cur == '<' && *(cur + 1) == '<' && dt->sq == 0 && dt->dq == 0)
			tok_op(dt, &cur, 7);
		if (*cur == '\0')
			break ;
		cur++;
		dt->sta = cur;
	}
	env_check(dt);
}
