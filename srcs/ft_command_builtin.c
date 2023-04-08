/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:30:21 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/08 09:43:31 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cmd_is_builtin(char	*cmd)
{
	int			i;
	static char	*builtin_funcs[5] = {"cd", "exit", "pwd", "echo", NULL};

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	while (builtin_funcs[i])
	{
		if (ft_strncmp(cmd, builtin_funcs[i], ft_strlen(builtin_funcs[i]) == 0))
			return (i + 1);
		i ++;
	}
	return (0);
}

void	ft_execute_builtin(t_env *split, t_arg *arg)
{
	printf("Builtin : %s", split->cmd);
	return ;
}
