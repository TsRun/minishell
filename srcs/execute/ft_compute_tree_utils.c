/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:39:55 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/17 18:56:01 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	free_outs(char *left, char *right)
{
	if (left)
		free(left);
	if (right)
		free(right);
}

char	*write_to_file(t_node *tree, char *input, int append)
{
	int		fd;

	if (!tree->args || !(*(tree->args)))
		return (NULL);
	if (append)
		fd = open(tree->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(tree->args[0], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (NULL);
	if (input && write(fd, input, ft_strlen(input)) < 0)
		return (close(fd), NULL);
	return (close(fd), NULL);
}

char	*read_stdin_to_delim(char *delim)
{
	char	*out;
	char	*readl;
	char	*tmp;

	if (!delim)
		return (NULL);
	out = NULL;
	tmp = readline("heredoc> ");
	readl = ft_strjoin(tmp, "\n");
	if (tmp)
		free(tmp);
	while (!ft_strnstr(readl, delim, ft_strlen(delim)))
	{
		ft_str_realloc(&out, readl);
		if (readl)
			free(readl);
		tmp = readline("heredoc>");
		readl = ft_strjoin(tmp, "\n");
		if (tmp)
			free(tmp);
	}
	if (readl)
		free(readl);
	return (out);
}
