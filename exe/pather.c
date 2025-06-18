/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pather.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 06:55:15 by etorun            #+#    #+#             */
/*   Updated: 2025/06/17 20:16:10 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	free_array(char **temp, int len)
{
	while (0 < len)
		free(temp[len-- - 1]);
	free(temp);
}

char	**p_combiner(char *cmd, char **envp, char **paths, char *temp)
{
	int	full_len;
	int	len;

	len = 0;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			paths = ft_split(*envp + 5, ':');
		envp++;
	}
	if (!paths)
		return (NULL);
	while (paths[len++])
		continue ;
	full_len = len;
	while (len-- > 0)
	{
		temp = paths[len];
		paths[len] = ft_strpathjoin(paths[len], cmd, 0, 0);
		free(temp);
		if (!*paths)
			free_array(paths, full_len);
	}
	return (paths);
}

char	*c_exist(t_dt *dt, char *cmd, char **envp)
{
	char	**p_com;
	char	**temp;
	int		flag;

	flag = 0;
	p_com = p_combiner(cmd, envp, NULL, NULL);
	temp = p_com;
	while (*temp)
	{
		if (!access(*temp, R_OK | X_OK | F_OK) && flag == 0)
		{
			dt->p_command = *temp;
			temp++;
			flag = 1;
			continue ;
		}
		free(*temp);
		temp++;
	}
	free(p_com);
	return (dt->p_command);
}