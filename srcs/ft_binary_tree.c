/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:00:53 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/14 02:06:25 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_node(t_env *split, t_node *node, int redir, int start, int end)
{
	int		i;
	t_arg	*tmp;

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
	max = -2147483648;
	couch_max = -2147483648;
	couch = 0;
	while (start++ < end)
	{
		if (tmp->redir == 8 || tmp->redir == 9)
			couch -= 2 * (tmp->redir == 8) - 1;
		else if ((couch > couch_max && tmp->prio != -1)
			|| (couch == couch_max && tmp->prio < max && tmp->prio != -1))
		{
			max = tmp->prio;
			i = start - 1;
			couch_max = couch;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	print_tree(t_node *root, int depth, char *prefix, int is_left)
{
	char	new_prefix[20];
	int		i;

	i = 0;
	if (root == NULL)
		return ;
	printf("%s", prefix);
	if (is_left)
		printf("|-- ");
	else
		printf("`-- ");
	if (root->type != -1)
		printf("%d", root->type);
	else
		while (root->args[i])
			printf("%s ", root->args[i++]);
	printf("\n");
	if (is_left)
		sprintf(new_prefix, "%s|   ", prefix);
	else
		sprintf(new_prefix, "%s%s", prefix, "    ");
	print_tree(root->left, depth + 1, new_prefix, 1);
	print_tree(root->right, depth + 1, new_prefix, 0);
}

int	ft_isword(t_env *split, int start, int end)
{
	t_arg	*tmp;
	int		i;

	tmp = ft_elem(split->list, start);
	i = 0;
	while (start < end)
	{
		if (tmp->redir == -1)
			i++;
		tmp = tmp->next;
		start++;
	}
	return (i);
}

void	ft_add_node(t_env *split, t_node *node, int dir)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		ft_error(split, "Error: malloc() failed");
	new->in = node->in;
	new->out = node->out;
	new->parent = node;
	if (dir)
		node->left = new;
	else
		node->right = new;
}

void	ft_create_tree(t_env *split, t_node **where, int start, int end)
{
	int		i;
	t_node	*node;

	i = ft_next_redir(split, start, end);
	if (i == -1)
		ft_create_node(split, *where, -1, start, end);
	else
	{
		ft_create_node(split, *where, ft_elem(split->list, i)->redir,
				start, end);
		if ((*where)->type == 3 || (*where)->type == 4)
			(*where)->out = 1;
		if ((*where)->type == 6 || (*where)->type == 7)
			(*where)->in = 1;
		if (ft_isword(split, start, i) > 0)
		{
			ft_add_node(split, *where, 0);
			ft_create_tree(split, &(*where)->left, start, i);
		}
		if (ft_isword(split, i + 1, end) > 0)
		{
			ft_add_node(split, *where, 1);
			ft_create_tree(split, &(*where)->right, i + 1, end);
		}
	}
}
