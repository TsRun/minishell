/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:34:58 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/17 12:42:38 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_builtin(char *cmd)
{
	static char	*funcs[4] = {"echo", "pwd", NULL};
	int			i;

	i = 0;
	while (funcs[i])
	{
		if (ft_strncmp(funcs[i], cmd, ft_strlen(funcs[i])) == 0)
			return (i + 1);
		i ++;
	}
	return (0);
}

int	ft_execute_builtin(t_env *env, char **cmd_split)
{
	int	index;

	index = ft_is_builtin(cmd_split[0]);
	if (index == 1)
		return (ft_builtin_echo(env, cmd_split), 1);
	else if (index == 2)
		return (ft_builtin_pwd(env, cmd_split), 1);
	return (0);
}
