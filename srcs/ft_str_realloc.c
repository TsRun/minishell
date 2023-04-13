/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:04:42 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/14 00:18:22 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_str_realloc(char **str, char *str2)
{
	int		len;
	int		i;
	int		j;
	char	*out;

	if (str && *str)
		len = ft_strlen(*str) + ft_strlen(str2);
	else
		len = ft_strlen(str2);
	out = (char *)ft_calloc(sizeof(char), (len + 2));
	i = 0;
	while (str && *str && (*str)[i])
	{
		out[i] = (*str)[i];
		i ++;
	}
	j = 0;
	while (str2 && str2[j])
		out[i++] = str2[j++];
	out[i] = 0;
	if (str && *str)
		free(*str);
	*str = out;
}
