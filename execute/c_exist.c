/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_exist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 06:26:08 by etorun            #+#    #+#             */
/*   Updated: 2025/06/03 11:49:00 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

static char **get_paths(char **envp)
{
    while (*envp)
    {
        if (ft_strnstr(*envp, "PATH=", 5))
            return ft_split(*envp + 5, ':');
        envp++;
    }
    return NULL;
}

static char *build_command(char *dir, char *cmd)
{
    char *full = ft_strpathjoin(dir, cmd, 0, 0);
    return full;
}

char *c_exist(t_dt *dt, char *cmd, char **envp)
{
    char **paths = get_paths(envp);
    int i = 0;

    if (!paths)
        return NULL;
    while (paths[i])
    {
        char *full = build_command(paths[i], cmd);
        if (!access(full, X_OK))
        {
            dt->p_command = paths;
            return full;
        }
        free(full);
        i++;
    }
    // Cleanup
    while (i--)
        free(paths[i]);
    free(paths);
    return NULL;
}
