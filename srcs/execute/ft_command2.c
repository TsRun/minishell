/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:01:47 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 19:47:00 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_env *env, char *path)
{
	char	*tmp;

	tmp = NULL;
	if (path == NULL)
		env->ret = chdir(get_env(env, "HOME"));
	else if (path[0] == '~')
	{
		tmp = ft_strjoin(get_env(env, "HOME"), path + 1);
		env->ret = chdir(tmp);
		rfree(tmp);
	}
	else
		env->ret = chdir(path);
	if (env->ret == -1)
		perror(path);
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
	else if (ft_strcmp(split->list->str, "cd") == 0)
	{
		if (split->list->next)
			ft_cd(split, split->list->next->str);
		else
			ft_cd(split, NULL);
	}
	else
		return (0);
	return (1);
}
