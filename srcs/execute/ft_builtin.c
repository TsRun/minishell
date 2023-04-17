/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:34:58 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/17 18:17:03 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_all_env_variables(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		ft_printf("%s\n", env[i]);
		i ++;
	}
}

int	ft_builtin_export(t_env *env, char **cmds)
{
	int	i;
	char	*var;

	if (!cmds || !env || !*cmds)
		return (0);
	if (!cmds[1])
		return (print_all_env_variables(env->env), 0);
	i = 1;
	while (cmds[i])
	{
		var = cmds[i];
		if (!ft_strchr(cmds[i], '='))
			var = ft_strjoin(cmds[i], "=''");
		ft_addenv(env, var);
		i ++;
	}
	return (0);
}

void	ft_builtin_unset(t_env *env, char **cmds)
{
	(void)env;
	(void)cmds;
}

int	ft_builtin_env(t_env *env, char **cmds)
{
	if (!cmds || !env || !*cmds)
		return (0);
	return (print_all_env_variables(env->env), 0);
}

int	ft_is_builtin(char *cmd)
{
	static char	*funcs[6] = {"echo", "pwd", "export", "unset", "env", NULL};
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
	else if (index == 3)
		return (ft_builtin_export(env, cmd_split), 1);
	else if (index == 4)
		return (ft_builtin_unset(env, cmd_split), 1);
	else if (index == 5)
		return (ft_builtin_env(env, cmd_split), 1);
	return (0);
}
