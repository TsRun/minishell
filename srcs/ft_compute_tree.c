/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:11:54 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/14 02:22:33 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	printf("coucou");
	if (!tree->args || !(*(tree->args)))
		return (NULL);
	if (append)
		fd = open(tree->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(tree->args[0], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (perror("open"), NULL);
	if (write(fd, input, ft_strlen(input)) < 0)
		return (close(fd), perror("write"), NULL);
	return (close(fd),  NULL);
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
	ft_str_realloc(&out, readl);
	if (readl)
		free(readl);
	return (out);
}

char	*ft_delimit_in(t_env *env, t_node *top, char *input)
{
	char	*right_out;
	char	*left_out;

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
//	if (top->type == 6)
//	{
//		if (top->right)
//			right_out = ft_strdup(top->right->args[ft_strlen(top->right->args) - 1]);
//		if (right_out && top->left)
//			left_out = ft_execute(env, )
//	}
	return (NULL);
}

char	*ft_compute_tree(t_env *env, t_node *top, char *input)
{
	char	*right_out;
	char	*left_out;
	char	*out;

	right_out = NULL;
	left_out = NULL;
	if (!top)
		return (NULL);
	env->exe.node = top;
	if (top->type == 7 || top->type == 6)
		return (ft_delimit_in(env, top, input));


	if (top->left)
		left_out = ft_compute_tree(env, top->left, input);
	if (!top->right && top->left)
		return (left_out);


	// type &&
	if (top->type == 0)
		right_out = ft_compute_tree(env, top->right, NULL);
	// type ||
	if (top->type == 1 && env->exe.last_outcode != 0)
		right_out = ft_compute_tree(env, top->right, NULL);
	// type |, >, >>
	if (top->type == 2 || top->type == 3 || top->type == 4)
		right_out = ft_compute_tree(env, top->right, left_out);

	if (top->args && top->type == -1 && (!top->parent || (top->parent->type != 4 && top->parent->type != 3) || top == top->parent->left))
		return (ft_execute(env, top->args, input));
	else if (top->parent && top->parent->type == 3 && top->parent->right)
		return (write_to_file(top, input, 0));
	else if (top->parent && top->parent->type == 4 && top->parent->right)
		return (write_to_file(top, input, 1));

	if (top->type != 2 && top->type != 3 && top->type != 4)
	{
		out = ft_strjoin(left_out, right_out);
		rfree(left_out);
		rfree(right_out);
		return (out);
	}
	if (left_out)
		free(left_out);
	return (right_out);
}
