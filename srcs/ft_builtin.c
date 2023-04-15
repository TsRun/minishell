/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:34:58 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/15 14:14:32 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_builtin(char *cmd)
{
	static char	*funcs[4] = {"cd", "echo", "pwd", NULL};
	int		i;

	i = 0;
	while (funcs[i])
	{
		if (ft_strncmp(funcs[i], cmd, ft_strlen(funcs[i])) == 0)
			return (i + 1);
		i ++;
	}
	return (0);
}

int	ft_execute_builtin(char **cmd_split)
{
	return (0);
}
