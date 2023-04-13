/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:00:53 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 21:35:06 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*ft_create_node(t_env *split, int redir, int start, int end)
{
	t_node	*node;
	int		i;
	t_arg	*tmp;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		ft_error(split, "Error: malloc() failed");
	node->type = redir;
	if (!node->type)
	{
		node->args = ft_calloc(end - start + 1, sizeof(char *));
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
int	ft_next_redir(t_env *split, int start, int end)
{
	t_arg	*tmp;

	tmp = ft_elem(split->list, start);
	while (tmp && tmp->redir == 0 && start < end)
	{
		tmp = tmp->next;
		start++;
	}
	if (tmp && tmp->redir && start < end)
		return (start);
	return (-1);
}
void	ft_print_binary(t_node *node)
{
	int		i;

	i = 0;
	if (node->type == 0)
		while (node->args[i])
			ft_printf("%s ", node->args[i++]);
	if (node->type)
		ft_printf("%d", node->type);
	ft_printf("\n");
	if (node->left)
		ft_print_binary(node->left);
	if (node->right)
		ft_print_binary(node->right);
}

void	ft_create_tree(t_env *split, t_node **where, int start, int end)
{
	int		i;

	i = ft_next_redir(split, start, end);
	if (i == -1)
		*where = ft_create_node(split, 0, start, end);
	else
	{
		*where = ft_create_node(split, ft_elem(split->list, i)->redir, start, end);
		ft_create_tree(split, &(*where)->left, start, i);
		ft_create_tree(split, &(*where)->right, i + 1, end);
	}
}
