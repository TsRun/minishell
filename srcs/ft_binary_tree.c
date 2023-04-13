/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:00:53 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/14 00:03:13 by maserrie         ###   ########.fr       */
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
	if (node->type == -1)
	{
		node->args = ft_calloc(end - start + 1, sizeof(char *));
		if (!node->args)
			ft_error(split, "Error: malloc() failed");
		i = 0;
		tmp = ft_elem(split->list, start);
		while (start < end)
		{
			if (tmp->redir == -1)
				node->args[i++] = ft_strdup(tmp->str);
			tmp = tmp->next;
			start++;
		}
	}
	return (node);
}

int	ft_next_redir(t_env *split, int start, int end)
{
	t_arg	*tmp;
	int		max;
	int		i;
	int		couch_max;
	int		couch;

	tmp = ft_elem(split->list, start);
	i = -1;
	max = 0;
	couch_max = -2147483648;
	couch = 0;
	while (start < end)
	{
		if (tmp->redir == 6)
			couch--;
		else if (tmp->redir == 7)
			couch++;
		else if ((couch > couch_max && tmp->prio != -1)
			|| (couch == couch_max && tmp->prio < max && tmp->prio != -1))
		{
			max = tmp->prio;
			i = start;
			couch_max = couch;
		}
		tmp = tmp->next;
		start++;
	}
	return (i);
}

void print_tree(t_node *root, int depth, char* prefix, int is_left)
{
	if (root == NULL) {
		return;
	}

	printf("%s", prefix);
	printf(is_left ? "|-- " : "`-- ");
	int	i = 0;
	if (root->type != -1)
		printf("%d", root->type);
	else
		while (root->args[i])
			printf("%s ", root->args[i++]);
	printf("\n");
	char new_prefix[20];
	sprintf(new_prefix, "%s%s", prefix, is_left ? "|   " : "    ");
	print_tree(root->left, depth+1, new_prefix, 1);
	print_tree(root->right, depth+1, new_prefix, 0);
}

void	ft_create_tree(t_env *split, t_node **where, int start, int end)
{
	int		i;

	i = ft_next_redir(split, start, end);
	if (i == -1)
		*where = ft_create_node(split, -1, start, end);
	else
	{
		*where = ft_create_node(split, ft_elem(split->list, i)->redir, start, end);
		ft_create_tree(split, &(*where)->left, start, i);
		ft_create_tree(split, &(*where)->right, i + 1, end);
	}
}
