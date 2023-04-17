/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:44:31 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/17 19:32:24 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_all_env_variables(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env && env[i])
	{
		ft_printf("declare -x ");
		j = 0;
		while (env[i] && env[i][j] != '=')
		{
			ft_printf("%c", env[i][j]);
			j++;
		}
		tmp = ft_strchr(env[i], '=');
		if (tmp)
			ft_printf("=\"%s\"", tmp + 1);
		ft_printf("\n");
		i ++;
	}
}

int	ft_builtin_env(t_env *env, char **cmds)
{
	int	i;

	i = 0;
	if (!cmds || !env || !*cmds)
		return (0);
	while (env->env[i])
		ft_printf("%s\n", env->env[i++]);
	return (0);
}

void	ft_builtin_unset(t_env *env, char **cmds)
{
	int	i;

	if (!env || !cmds || !*cmds)
		return ;
	if (!cmds[1])
	{
		perror("Unset : To few arguments");
		return ;
	}
	i = 1;
	while (cmds[i])
	{
		ft_remove_env(env, cmds[i]);
		i ++;
	}
}

int	ft_builtin_export(t_env *env, char **cmds)
{
	int		i;
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
			var = ft_strjoin(cmds[i], "=");
		ft_addenv(env, var);
		i ++;
	}
	return (0);
}
