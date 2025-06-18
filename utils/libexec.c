/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 06:32:20 by etorun            #+#    #+#             */
/*   Updated: 2025/06/14 22:15:01 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str && !len)
		return (0);
	if (to_find[0] == '\0' || to_find == str)
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j) < len)
		{
			if (str[i + j] == '\0' && to_find[j] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return (0);
}

static size_t	ft_cnt_wds(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static int	ft_null_control(char **strs, int i)
{
	if (!strs[i])
	{
		while (i--)
			free(strs[i]);
		free(strs);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;

	i = 0;
	strs = (char **)malloc(sizeof(char *) * (ft_cnt_wds(s, c) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			strs[i] = ft_substr(s, 0, ft_strchr(s, c) - s);
			if (ft_null_control(strs, i))
				return (NULL);
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
