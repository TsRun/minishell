/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:11:54 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/17 13:01:15 by adrienmori       ###   ########.fr       */
/*   Updated: 2023/04/16 19:47:07 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_outs(char *left, char *right)
{
	if (left)
		free(left);
	if (right)
		free(right);
}

static char	*write_to_file(t_node *tree, char *input, int append)
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
	tmp = readline("heredoc>");
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

static char	*read_from_file(char *file)
{
	int		fd;
	char	*out;
	char	buffer[129];
	int		size;

	out = NULL;
	fd = open(file, O_RDONLY);
	size = 1;
	if (fd < 0)
		return (NULL);
	while (size > 0)
	{
		size = read(fd, buffer, 128);
		buffer[size] = 0;
		if (size > 0)
			ft_str_realloc(&out, buffer);
	}
	return (close(fd), out);
}

char	*ft_delimit_in(t_env *env, t_node *top, char *input)
{
	char	*right_out;
	char	*left_out;

	(void) input;
	right_out = NULL;
	left_out = NULL;
	if (top->type == 7)
	{
		if (top->right)
			right_out = read_stdin_to_delim(top->right->args[0]);
		if (top->left)
			left_out = ft_compute_tree(env, top->left, right_out);
		return (free_outs(right_out, NULL), left_out);
	}
	if (top->type == 6)
	{
		if (top->right)
			right_out = read_from_file(top->right->args[0]);
		if (right_out && top->left)
			left_out = ft_compute_tree(env, top->left, right_out);
		return (free_outs(right_out, NULL), left_out);
	}
	return (NULL);
}

char	*get_left_out(t_env *env, t_node *top, char *input)
{
	char	*left;

	left = NULL;
	if (top->left)
		left = ft_compute_tree(env, top->left, input);
	return (left);
}

char	*ft_compute_tree(t_env *env, t_node *node, char *input);

char	*get_right_out(t_env *env, t_node *top, char *left_out)
{
	char	*right_out;

	right_out = NULL;
	if (top->type == 0)
		right_out = ft_compute_tree(env, top->right, NULL);
	if (top->type == 1 && env->exe.last_outcode != 0)
		right_out = ft_compute_tree(env, top->right, NULL);
	if (top->type == 2 || top->type == 3 || top->type == 4)
		right_out = ft_compute_tree(env, top->right, left_out);
	return (right_out);
}

char	*ft_compute_tree(t_env *env, t_node *top, char *input)
{
	char	*right_out;
	char	*left_out;
	char	*out;

	if (!top)
		return (NULL);
	env->exe.node = top;
	if (top->type == 7 || top->type == 6)
		return (ft_delimit_in(env, top, input));
	left_out = get_left_out(env, top, input);
	if (!top->right && left_out)
		return (left_out);
	right_out = get_right_out(env, top, left_out);
	if (top->args && top->type == -1 && (!top->parent || (top->parent->type != 4
				&& top->parent->type != 3) || top == top->parent->left))
		return (ft_execute(env, top->args, input));
	else if (top->parent && (top->parent->type == 4 || top->parent->type == 3)
		&& top == top->parent->right)
		return (write_to_file(top, input, top->parent->type == 4));
	if (top->type != 2 && top->type != 3 && top->type != 4)
	{
		out = ft_strjoin(left_out, right_out);
		return (free_outs(left_out, right_out), out);
	}
	return (free_outs(left_out, NULL), right_out);
}
