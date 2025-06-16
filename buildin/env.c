/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 05:43:19 by etorun            #+#    #+#             */
/*   Updated: 2025/06/03 11:53:39 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	ft_env(t_dt *dt)
{
	char	**temp;

	temp = dt->envp;
	while (*temp)
	{
		printf("%s\n",*temp++);
	}
}
