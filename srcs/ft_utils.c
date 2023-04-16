/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:09:11 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 18:46:31 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	**ft_add_tab(void **tab, void *new)
{
	int		i;
	void	**new_tab;

	i = 0;
	if (!tab)
	{
		new_tab = ft_calloc(sizeof(void *), 2);
		if (!new_tab)
			return (NULL);
		new_tab[0] = new;
		return (new_tab);
	}
	while (tab[i])
		i++;
	new_tab = ft_calloc(sizeof(void *), (i + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = new;
	return (new_tab);
}

int	ft_what_redir(t_arg *tmp, t_env *split)
{
	if (!tmp->redir)
		return (0);
	if (ft_strncmp(tmp->str, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(tmp->str, ">>", 3) == 0)
		return (2);
	else if (ft_strncmp(tmp->str, "<", 3) == 0)
		return (3);
	else if (ft_strcmp(tmp->str, "<<") == 0)
		return (4);
	else if (ft_strcmp(tmp->str, "|") == 0)
		return (5);
	else if (tmp->str[0] == '~')
		ft_home(tmp, split);
	return (0);
}

void	ft_home(t_arg *tmp, t_env *split)
{
	char	*home;

	home = get_env(split, "HOME");
	if (!tmp->str[1] && home)
	{
		rfree(tmp->str);
		tmp->str = ft_strdup(home);
		rfree(home);
	}
}

void	print_tree(t_node *root, int depth, char *prefix, int is_left)
{
	char	new_prefix[20];
	int		i;

	i = 0;
	if (root == NULL)
		return ;
	ft_printf("%s", prefix);
	if (is_left)
		ft_printf("|-- ");
	else
		ft_printf("`-- ");
	if (root->type != -1)
		ft_printf("%d", root->type);
	else
		while (root->args[i])
			ft_printf("%s ", root->args[i++]);
	ft_printf("\n");
	if (is_left)
		sprintf(new_prefix, "%s|   ", prefix);
	else
		sprintf(new_prefix, "%s%s", prefix, "    ");
	print_tree(root->left, depth + 1, new_prefix, 1);
	print_tree(root->right, depth + 1, new_prefix, 0);
}
