/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 07:18:48 by etorun            #+#    #+#             */
/*   Updated: 2025/06/03 11:55:00 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

static void free_command_array(char **arr)
{
    int i = 0;

    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void f_exe(t_dt *dt)
{
    free_command_array(dt->p_command);
    dt->p_command = NULL;

    if (dt->com_array)
    {
        free(dt->com_array);
        dt->com_array = NULL;
    }
}
