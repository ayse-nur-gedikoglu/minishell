/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:49:49 by etorun            #+#    #+#             */
/*   Updated: 2025/06/05 23:43:31 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int is_builtin(t_dt *dt, char *cmd)
{
    if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
        return ft_echo(dt), 1;
    if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
        return ft_cd(dt), 1;
    if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
        return ft_pwd(), 1;
    if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
        return ft_export(dt), 1;
    if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
        return ft_unset(dt), 1;
    if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
        return ft_env(dt), 1;
    if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
        return ft_exit(dt), 1;
    return 0;
}

static int run_external(t_dt *dt, char *path, char **envp)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        execve(path, dt->com_array, envp);
        perror("execve");
        exit(127);
    }
    else if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    waitpid(pid, NULL, 0);
    f_exe(dt);
    return 0;
}

int execute(t_dt *dt, t_token *f, char **envp)
{
    char *path;

    while (f)
    {
        if (f->tpye == PIPE)
            return printf("bash: syntax error near unexpected token `|'\n"), 1;
        if (f->tpye < 3)
        {
            if (is_builtin(dt, f->con))
            {
                f = f->next;
                continue;
            }
            path = c_exist(dt, f->con, envp);
            if (!path)
                return printf("%s: command not found\n", f->con), 127;
            if (run_external(dt, path, envp))
                return 1;
        }
        f = f->next;
    }
    return 0;
}
