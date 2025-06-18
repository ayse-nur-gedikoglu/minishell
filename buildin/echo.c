/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:05:52 by etorun            #+#    #+#             */
/*   Updated: 2025/06/17 20:07:00 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	check_n(char *first)
{
	size_t	len;
	size_t	i;

	if (!first)
		return (0);
	len = ft_strlen(first);
	i = 1;
	while (i < len)
	{
		if (first[0] != '-')
			break ;
		if (first[i] == 'n')
			i++;
		else
			break ;
	}
	if (i == len && len != 1)
		return (1);
	return (0);
}

int	ft_echo(t_dt *dt, int flag, int i)
{
	char	**arr;

	arr = dt->c_arr;
	while (arr[i])
	{
		if (check_n(arr[i]))
		{
			i++;
			flag = 1;
		}
		else
			break ;
	}
	while (arr[i])
	{
		printf("%s", arr[i++]);
		if (arr[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
