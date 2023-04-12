/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:01:47 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/12 22:54:41 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (env->args[1] == NULL)
	{
		if (chdir(get_env(env, "HOME")) == -1)
			ft_printf("cd: HOME not set\n");
	}
	else if (env->args[1][0] == '~')
	{
		tmp = ft_strjoin(get_env(env, "HOME"), env->args[1] + 1);
		if (chdir(tmp) == -1)
			ft_printf("cd: HOME not set\n");
		rfree(tmp);
	}
	else if (chdir(env->args[1]) == -1)
		ft_printf("cd: no such file or directory: %s\n", env->args[1]);
}

int	ft_chose_command(t_env *split)
{
	if (ft_strcmp(split->list->str, "env") == 0)
		ft_print_env(split);
	else if (ft_strcmp(split->list->str, "unset") == 0)
		ft_unset(split);
	else if (ft_strcmp(split->list->str, "exit") == 0)
		ft_end(split);
	else if (ft_strcmp(split->list->str, "export") == 0)
		ft_add_env(split);
	else
		return (0);
	return (1);
}
