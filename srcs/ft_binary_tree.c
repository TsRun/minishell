/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:00:53 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 20:52:54 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*ft_create_node(t_env *split, int redir, int start, int end)
{
	t_node	*node;
	int		i;
	t_arg	*tmp;

	node = ft_calloc(sizeof(t_node), 1);
	if (!node)
		ft_error(split, "Error: malloc() failed");
	node->type = redir;
	if (end != start)
	{
		node->args = ft_calloc(sizeof(char *), end - start + 1);
		if (!node->args)
			ft_error(split, "Error: malloc() failed");
		i = 0;
		tmp = ft_elem(split->list, start);
		while (start < end)
		{
			node->args[i] = ft_strdup(tmp->str);
			tmp = tmp->next;
			start++;
			i++;
		}
	}
	return (node);
}
int	ft_next_redir(t_env *split, int start)
{
	t_arg	*tmp;

	tmp = ft_elem(split->list, start);
	while (tmp && tmp->redir == 0)
	{
		tmp = tmp->next;
		start++;
	}
	return (start);
}
void	ft_print_binary(t_node *node)
{
	int		i;

	i = 0;
	if (node->type == 0)
		while (node->args[i])
			ft_printf("%s ", node->args[i++]);
	if (node->type == 1)
		ft_printf("%d", node->type);
	ft_printf("\n");
	if (node->left)
		ft_print_binary(node->left);
	if (node->right)
		ft_print_binary(node->right);
}

void	ft_create_tree(t_env *split)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	while (tmp && tmp->redir == 0)
		tmp = tmp->next;
}
