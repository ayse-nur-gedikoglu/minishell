/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:10:36 by etorun            #+#    #+#             */
/*   Updated: 2025/06/19 08:04:49 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

int	ft_exit(t_dt *dt)
{
	int	last_ex;

	last_ex = (ex_code(-1));
	free_command(dt);
	free_all(dt);
	freeandleave(dt);
	exit (last_ex);
}
