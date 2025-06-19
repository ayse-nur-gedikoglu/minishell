/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:08:54 by etorun            #+#    #+#             */
/*   Updated: 2025/06/19 19:09:19 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	cdtilda(t_dt *dt)
{
	char	*homecheck;
	int		flag;

	flag = 0;
	free(dt->oldpwd);
	dt->oldpwd = getcwd(NULL, 0);
	homecheck = getenv("HOME");
	if (!homecheck)
		flag = chdir(dt->home);
	else
		flag = chdir(getenv("HOME"));
	if (flag == 0)
		ex_code(0);
	else
		ex_code(1);
	return (0);
}

int	cd_errcontrol(t_dt *dt, char **c_arr)
{
	if (c_arr[1] != NULL && c_arr[2] != NULL)
	{
		printf("bash: cd: too many arguments\n");
		ex_code(1);
		return (1);
	}
	if (dt->pf == 1)
		return (1);
	if (c_arr[1] == NULL)
	{
		cdtilda(dt);
		return (1);
	}
	return (0);
}

int	cdminus(t_dt *dt)
{
	char	*curpwd;

	curpwd = getcwd(NULL, 0);
	if (dt->oldpwd == NULL)
	{
		printf("ElShellito: cd: OLDPWD not set\n");
		free(curpwd);
		ex_code(1);
		return (1);
	}
	else
	{
		printf("%s\n", dt->oldpwd);
		if (!chdir(dt->oldpwd))
			ex_code(0);
		else
			ex_code(1);
		free(dt->oldpwd);
		dt->oldpwd = curpwd;
	}
	return (0);
}

int	ft_cd(t_dt *dt, char **c_arr, int flag, char *curpwd)
{
	if (cd_errcontrol(dt, c_arr))
		return (0);
	if (!ft_strncmp(c_arr[1], "-", 2))
	{
		cdminus(dt);
		return (0);
	}
	else if (!ft_strncmp(c_arr[1], "~", 2))
	{
		cdtilda(dt);
		return (0);
	}
	curpwd = getcwd(NULL, 0);
	flag = chdir(c_arr[1]);
	if (flag == -1)
	{
		printf("ElShellito: cd: %s: %s\n", c_arr[1], strerror(errno));
		ex_code(1);
		free(curpwd);
		return (0);
	}
	free(dt->oldpwd);
	dt->oldpwd = curpwd;
	ex_code(0);
	return (0);
}
