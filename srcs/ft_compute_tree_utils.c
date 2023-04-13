/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:39:55 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/13 22:53:27 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_executable_from_path(char *cmd, char **paths)
{
	int		i;
	char	*exe;
	char	*path;

	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (NULL);
		exe = ft_strjoin(path, cmd);
		free(path);
		if (!exe)
			return (NULL);
		if (!access(exe, 0))
			return (exe);
		free(exe);
	}
	if (!access(cmd, 0))
		return (ft_strdup(cmd));
	return (NULL);
}
