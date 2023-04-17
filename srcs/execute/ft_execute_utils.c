/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:57:07 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/17 20:06:17 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	replace_str_outcode(t_env *env, char **str)
{
	char	*tmp;
	char	*num;
	int		i;
	int		j;

	num = ft_itoa(env->exe.last_outcode);
	tmp = (char *)ft_calloc(sizeof(char), ft_strlen(num) + ft_strlen(*str));
	if (!tmp)
		return (free(num), 0);
	i = -1;
	j = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == -2)
		{
			ft_memcpy(tmp + j, (void *)num, ft_strlen(num));
			j += ft_strlen(num);
		}
		else
			tmp[j++] = (*str)[i];
	}
	if (*str)
		free(*str);
	*str = tmp;
	return (free(num), 0);
}

int	replace_outcode(t_env *env, char ***cmd_split)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd_split)
		return (0);
	while ((*cmd_split)[i])
	{
		j = 0;
		while ((*cmd_split)[i][j])
		{
			if ((*cmd_split)[i][j] == -2)
				replace_str_outcode(env, &((*cmd_split)[i]));
			j ++;
		}
		i ++;
	}
	return (0);
}

int	sout(t_env *env)
{
	env->exe.last_outcode = 127;
	return (1);
}
