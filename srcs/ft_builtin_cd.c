/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:09:24 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/15 14:17:00 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	normal_cd(t_env *env, char **cmds)
{
	char	*tmp;
	char	*tmp2;

	if (!cmds[1] || cmds[1][0] == '~')
	{
		if (cmds[1])
			tmp = ft_strjoin(getenv("HOME"), cmds[1] + 1);
		else
			tmp = ft_strdup(getenv("HOME"));
		if (tmp[0] && tmp[ft_strlen(tmp) - 1] != '/')
			tmp2 = ft_strjoin(tmp, "/");
		else
			tmp2 = ft_strdup(tmp);
		if (access(tmp2, F_OK))
			return (free(tmp), free(tmp2), 1);
		return (chdir(tmp2), free(tmp2), free(tmp), 0);
	}
	if (cmds[1][0] && cmds[1][ft_strlen(cmds[1]) - 1] != '/')
		tmp = ft_strjoin(cmds[1], "/");
	else
		tmp = ft_strdup(cmds[1]);
	if (!access(tmp, F_OK))
		return (chdir(tmp), free(tmp), 0);
	return (1);
}

int	ft_builtin_cd(t_env *env, char **cmds)
{
	if (normal_cd(env, cmds))
		perror("cd");
	return (0);
}
